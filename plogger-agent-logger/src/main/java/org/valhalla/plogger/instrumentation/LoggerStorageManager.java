package org.valhalla.plogger.instrumentation;

/*
MIT License

Copyright (c) 2020 Claudio Corsi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

import java.io.Closeable;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.PrintWriter;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Date;
import java.util.List;
import java.util.concurrent.LinkedBlockingQueue;

public class LoggerStorageManager {

    private static LoggerStorageManagerCreator activeCreator;
    private static LoggerStorageManagerCreator storageCreator;
    private static LoggerStorageManagerCreator creator;
    private static final LoggerDebug debug;
    private static final LoggerDebug debugException;

    static {
        boolean entered = LoggerManager.enter();
        try {
            debug = LoggerDebug.getDebug("loggerstoragemanager");
            debugException = LoggerDebug.getDebug("loggerstoragemanager.exception");
        } finally {
            if (entered)
                LoggerManager.exit();
        }
    }

    private static LoggerStorageManagerThread storageManagerThread = null;

    public static List<String> createEntriesBuffer() {
        return creator.get();
    }

    public static void store(List<String> buffer) {
        if (buffer != null)
            creator.add(buffer);
    }

    public synchronized static void startLoggerStorageManagerThread(String[] appenderSettings) {
        if (storageManagerThread == null) {
            boolean entered = LoggerManager.enter();
            if (debug.isDebug()) {
                debug.debug("Creating the LoggerStorageMangerThread");
            }
            try {
                LinkedBlockingQueue<List<String>> store = new LinkedBlockingQueue<List<String>>();
                LinkedBlockingQueue<List<String>> active = new LinkedBlockingQueue<List<String>>();
                activeCreator = new ActiveCreator(store, active);
                storageCreator = new StorageCreator(store);
                creator = activeCreator;
                creator = activeCreator;
                storageManagerThread = new LoggerStorageManagerThread( store, active,
                        "LoggerStorageManagerThread", appenderSettings);
                storageManagerThread.setDaemon(true);
                storageManagerThread.start();
            } finally {
                if (entered)
                    LoggerManager.exit();
            }
        }
    }

    public synchronized static LoggerStorageManagerShutdownHookThread addShutdownHookThread() {
        LoggerStorageManagerShutdownHookThread loggerStorageManagerShutdownHookThread =
                new LoggerStorageManagerShutdownHookThread();
        Runtime.getRuntime().addShutdownHook(loggerStorageManagerShutdownHookThread);
        return loggerStorageManagerShutdownHookThread;
    }

    private static class LoggerStorageManagerThread extends Thread {

        private final LoggerStorageManagerAppend appender;
        private boolean isActive;
        private final LinkedBlockingQueue<List<String>> store;
        private final LinkedBlockingQueue<List<String>> active;

        public LoggerStorageManagerThread(LinkedBlockingQueue<List<String>> store,
                                          LinkedBlockingQueue<List<String>> active, String name,
                                          String[] appenderSettings) {
            super(name);
            this.store = store;
            this.active = active;
            isActive = true;
            appender = LoggerStorageManager.createAppender(appenderSettings);
        }

        @Override
        public void run() {
            // Insure nothing is logged from this thread
            LoggerManager.enter();
            if (debug.isDebug()) {
                debug.debug("Started LoggerStorageManagerThread thread");
            }
            // Process active entries when processing log entries
            while (isActive) {
                try {
                    // Get the next entries list and store it
                    List<String> entries = store.take();
                    if (debug.isDebug()) {
                        debug.debug(String.format("Storing %d entries from %d", entries.size(),
                                System.identityHashCode(entries)));
                    }
                    // store entries
                    for (String entry : entries) {
                        if (debug.isDebug()) {
                            debug.debug(String.format("Storing entry: %s", entry));
                        }
                        appender.write(entry);
                    }
                } catch (InterruptedException ie) {
                    if (debugException.isDebug()) {
                        debug.debug("An interrupted exception was caught");
                    }
                } catch (Throwable e) {
                    if (debugException.isDebug())
                        debugException.debug(e);
                }
            }

            if (debug.isDebug()) {
                debug.debug("Processed all store entries");
            }

            // Process the remaining entries
            while (!store.isEmpty()) {
                try {
                    List<String> entries = store.take();
                    if (debug.isDebug()) {
                        debug.debug(String.format("Storing %d entries from %d", entries.size(),
                                System.identityHashCode(entries)));
                    }
                    // store entries
                    for (String entry : entries) {
                        try {
                            if (debug.isDebug()) {
                                debug.debug(String.format("Storing missed entry: %s", entry));
                            }
                            appender.write(entry);
                        } catch (FileNotFoundException e) {
                            if (debugException.isDebug())
                                debugException.debug(e);
                        }
                    }
                } catch (Throwable t) {
                    if (debugException.isDebug())
                        debugException.debug(t);
                    // do nothing for now.
                }
            }

            if (debug.isDebug()) {
                debug.debug("Processed all remaining active entries");
            }

            // TODO: Active entries can still be accessed and we need to
            //  deal with the possibility of a concurrent modification exception.
            // Process the remaining entries
            while (!active.isEmpty()) {
                try {
                    List<String> entries = active.take();
                    if (debug.isDebug()) {
                        debug.debug(String.format("Storing %d entries from %d", entries.size(),
                                System.identityHashCode(entries)));
                    }
                    // store entries
                    for (String entry : entries) {
                        try {
                            if (debug.isDebug()) {
                                debug.debug(String.format("Storing active entry: %s", entry));
                            }
                            appender.write(entry);
                        } catch (Throwable t) {
                            if (debugException.isDebug())
                                debugException.debug(t);
                        }
                    }
                } catch (Throwable t) {
                    if (debugException.isDebug())
                        debugException.debug(t);
                    // do nothing
                }
            }

            if (debug.isDebug()) {
                debug.debug("Closing appender");
            }

            try {
                appender.close();
            } catch (IOException e) {
                if (debugException.isDebug())
                    debugException.debug(e);
            }

            if (debug.isDebug())
                debug.debug("Exiting LoggerStorageManagerThread thread");
        }

        public void done() {
            this.isActive = false;
        }

    }

    private static LoggerStorageManagerAppend createAppender(String[] appenderSettings) {
        LoggerStorageManagerAppend appender;
        appender = new LoggerStorageManagerFileAppend();
        appender.initialize(appenderSettings);
        if (debug.isDebug()) {
            debug.debug("Created appender");
        }
        return appender;
    }

    static class LoggerStorageManagerShutdownHookThread extends Thread {
        @Override
        public void run() {
            LoggerManager.enter();
            // Update the mechanism that stores the entries
            creator = storageCreator;
            // Inform the thread to start to drain all entries.
            storageManagerThread.done();
            // interrupt the thread
            storageManagerThread.interrupt();
            try {
                storageManagerThread.join();
            } catch (InterruptedException e) {
                if (debugException.isDebug())
                    debugException.debug(e);
                e.printStackTrace(System.out);
            } finally {
                storageManagerThread = null;
            }
        }
    }

    private interface LoggerStorageManagerCreator {
        List<String> get();

        void add(List<String> buffer);
    }

    private static class StorageCreator implements LoggerStorageManagerCreator {

        private final LinkedBlockingQueue<List<String>> store;

        public StorageCreator(LinkedBlockingQueue<List<String>> store) {
            this.store = store;
        }

        @Override
        public List<String> get() {
            List<String> buffer = new ArrayList<String>();
            store.add(buffer);
            if (debug.isDebug())
                debug.debug(String.format("Created new store buffer %d", System.identityHashCode(buffer)));
            return buffer;
        }

        @Override
        public void add(List<String> buffer) {
            if (debug.isDebug())
                debug.debug(String.format("Added store buffer %d", System.identityHashCode(buffer)));
            store.add(buffer);
        }
    }

    private static class ActiveCreator implements LoggerStorageManagerCreator {

        private final LinkedBlockingQueue<List<String>> store;
        private final LinkedBlockingQueue<List<String>> active;

        public ActiveCreator(LinkedBlockingQueue<List<String>> store, LinkedBlockingQueue<List<String>> active) {
            this.store = store;
            this.active = active;
        }

        @Override
        public List<String> get() {
            List<String> buffer = new ArrayList<String>();
            active.add(buffer);
            if (debug.isDebug())
                debug.debug(String.format("Created new active buffer %d", System.identityHashCode(buffer)));
            return buffer;
        }

        @Override
        public void add(List<String> buffer) {
            active.remove(buffer);
            if (debug.isDebug())
                debug.debug(String.format("Removed active buffer %d", System.identityHashCode(buffer)));
            store.add(buffer);
            if (debug.isDebug())
                debug.debug(String.format("Added store buffer %d", System.identityHashCode(buffer)));
        }
    }

    private interface LoggerStorageManagerAppend extends Closeable {
        void initialize(String[] settings);
        void write(String message) throws FileNotFoundException;
    }

    /**
     * TODO: Implement class
     *
     * It should create files with the PLogger-[DATE]-[COUNT].txt?
     *
     * It should just store the written data to a file and determine if it needs to
     * close and open a new file....
     *
     */
    private static class LoggerStorageManagerFileAppend implements LoggerStorageManagerAppend {

        private String fileNamePrefix;
        private FileOutputStream fos;
        private PrintWriter writer;
        private int count;
        private int messages;

        LoggerStorageManagerFileAppend() {
            count = 1;
            messages = 0;
        }

        @Override
        public void initialize(String[] settings) {
            String prefix = "PLogger";

            for (String setting : settings) {
                if (setting.startsWith("prefix=")) {
                    prefix = setting.substring("prefix=".length());
                }
            }

            Date time = Calendar.getInstance().getTime();

            fileNamePrefix = String.format("%s-%s", prefix,
                    new SimpleDateFormat("yyyy-MM-dd-HH-mm-ssSSSZ").format(time));

            try {
                fos = new FileOutputStream(String.format("%s-%d.txt", fileNamePrefix, count));
                if (debug.isDebug()) {
                    debug.debug(String.format("Created file: %s-%d.txt", fileNamePrefix, count));
                }
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }

            writer = new PrintWriter(fos);
        }

        @Override
        public void write(String message) throws FileNotFoundException {
            if (messages > 1000) {
                if (debug.isDebug()) {
                    debug.debug(String.format("Closing file: %s-%d.txt", fileNamePrefix, count));
                }
                messages = 0;
                count++;
                writer.close();
                fos = new FileOutputStream(String.format("%s-%d.txt", fileNamePrefix, count));
                if (debug.isDebug()) {
                    debug.debug(String.format("Created file: %s-%d.txt", fileNamePrefix, count));
                }
                writer = new PrintWriter(fos);
            }
            writer.println(message);
            messages++;
            try {
                fos.getFD().sync();
            } catch (IOException e) {
            }
        }

        @Override
        public void close() throws IOException {
            if (debug.isDebug()) {
                debug.debug(String.format("Closing file: %s-%d.txt", fileNamePrefix, count));
            }
            writer.close();
        }
    }
}
