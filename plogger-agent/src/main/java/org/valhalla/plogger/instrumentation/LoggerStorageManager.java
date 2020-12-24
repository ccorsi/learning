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

    private static final LinkedBlockingQueue<List<String>> store;
    private static final LinkedBlockingQueue<List<String>> active;
    private static final LoggerStorageManagerCreator activeCreator;
    private static final LoggerStorageManagerCreator storageCreator;
    private static LoggerStorageManagerCreator creator;
    private static final LoggerDebug debug;

    static {
        boolean entered = LoggerManager.enter();
        try {
            debug = LoggerDebug.getDebug("loggerstoragemanager");
            store = new LinkedBlockingQueue<List<String>>();
            active = new LinkedBlockingQueue<List<String>>();
            activeCreator = new ActiveCreator();
            storageCreator = new StorageCreator();
            creator = activeCreator;
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
        creator.add(buffer);
    }

    public synchronized static void startLoggerStorageManagerThread(String[] appenderSettings) {
        if (storageManagerThread == null) {
            boolean entered = LoggerManager.enter();
            try {
                storageManagerThread = new LoggerStorageManagerThread("LoggerStorageManagerThread",
                        appenderSettings);
                storageManagerThread.setDaemon(true);
                storageManagerThread.start();
            } finally {
                if (entered)
                    LoggerManager.exit();
            }
        }
    }

    public synchronized static void addShutdownHookThread() {
        Runtime.getRuntime().addShutdownHook(new LoggerStorageManagerShutdownHookThread());
    }

    private static class LoggerStorageManagerThread extends Thread {

        private final LoggerStorageManagerAppend appender;
        private boolean active;

        public LoggerStorageManagerThread(String name, String[] appenderSettings) {
            super(name);
            active = true;
            appender = LoggerStorageManager.createAppender(appenderSettings);
        }

        @Override
        public void run() {
            // Insure nothing is logged from this thread
            LoggerManager.enter();
            // Process active entries when processing log entries
            while(active) {
                try {
                    // Get the next entries list and store it
                    List<String> entries = store.take();
                    // store entries
                    for (String entry : entries) {
                        appender.write(entry);
                    }
                } catch (InterruptedException e) {
                } catch (FileNotFoundException e) {
//                    e.printStackTrace();
                }
            }

            // Process the remaining entries
            for(List<String> entries : store) {
                // store entries
                for (String entry : entries) {
                    try {
                        appender.write(entry);
                    } catch (FileNotFoundException e) {
//                        e.printStackTrace();
                    }
                }
            }

            // TODO: Active entries can still be accessed and we need to
            //  deal with the possibility of a concurrent modification exception.
            // Process the remaining entries
            for(List<String> entries : LoggerStorageManager.active) {
                // store entries
                for(String entry : entries) {
                    try {
                        appender.write(entry);
                    } catch (FileNotFoundException e) {
//                        e.printStackTrace();
                    } catch (Throwable t) {
                        t.printStackTrace();
                    }
                }
            }
            try {
                appender.close();
            } catch (IOException e) {
//                e.printStackTrace();
            }

            if (debug.isDebug())
                debug.debug("Exiting LoggerStorageManagerThread thread");
        }

        public void done() {
            this.active = false;
        }

    }

    private static LoggerStorageManagerAppend createAppender(String[] appenderSettings) {
        LoggerStorageManagerAppend appender;
        appender = new LoggerStorageManagerFileAppend();
        appender.initialize(appenderSettings);
        return appender;
    }

    private static class LoggerStorageManagerShutdownHookThread extends Thread {
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
                e.printStackTrace(System.out);
            }
        }
    }

    private interface LoggerStorageManagerCreator {
        List<String> get();

        void add(List<String> buffer);
    }

    private static class StorageCreator implements LoggerStorageManagerCreator {
        @Override
        public List<String> get() {
            List<String> buffer = new ArrayList<String>();
            store.add(buffer);
            return buffer;
        }

        @Override
        public void add(List<String> buffer) {
            store.add(buffer);
        }
    }

    private static class ActiveCreator implements LoggerStorageManagerCreator {
        @Override
        public List<String> get() {
            List<String> buffer = new ArrayList<String>();
            active.add(buffer);
            return buffer;
        }

        @Override
        public void add(List<String> buffer) {
            active.remove(buffer);
            store.add(buffer);
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
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }

            writer = new PrintWriter(fos);
        }

        @Override
        public void write(String message) throws FileNotFoundException {
            if (messages > 1000) {
                messages = 0;
                count++;
                writer.close();
                fos = new FileOutputStream(String.format("%s-%d.txt", fileNamePrefix, count));
                writer = new PrintWriter(fos);
            }
            writer.println(message);
            messages++;
            try {
                fos.getFD().sync();
            } catch (IOException e) {
//                e.printStackTrace();
            }
        }

        @Override
        public void close() throws IOException {
            writer.close();
        }
    }
}
