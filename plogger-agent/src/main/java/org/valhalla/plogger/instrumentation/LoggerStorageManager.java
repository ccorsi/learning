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
import java.util.List;
import java.util.concurrent.LinkedBlockingQueue;

public class LoggerStorageManager {

    private static final LinkedBlockingQueue<List<String>> store;
    private static final LinkedBlockingQueue<List<String>> active;
    private static final LoggerStorageManagerCreator activeCreator;
    private static final LoggerStorageManagerCreator storageCreator;
    private static LoggerStorageManagerCreator creator;

    static {
//        System.out.println("ENTERED LOGGER STORE MANAGER STATIC METHOD");
        LoggerManager.enter();
        try {
//            System.out.println("BEFORE CREATING STORE");
            store = new LinkedBlockingQueue<List<String>>();
//            System.out.println("BEFORE CREATING ACTIVE");
            active = new LinkedBlockingQueue<List<String>>();
//            System.out.println("BEFORE CREATING ACTIVE CREATOR");
            activeCreator = new ActiveCreator();
//            System.out.println("BEFORE CREATING STORAGE CREATOR");
            storageCreator = new StorageCreator();
//            System.out.println("BEFORE CREATING CREATOR");
            creator = activeCreator;
        } finally {
            LoggerManager.exit();
//            System.out.println("EXITING LOGGER STORE MANAGER STATIC METHOD");
        }
    }

    private static LoggerStorageManagerThread storageManagerThread = null;

    public static List<String> createEntriesBuffer() {
        return creator.get();
    }

    public static void store(List<String> buffer) {
        creator.add(buffer);
    }

    public synchronized static void startLoggerStorageManagerThread() {
        if (storageManagerThread == null) {
            LoggerManager.enter();
            try {
//                System.out.println("Starting LoggerStoreManagerThread");
                storageManagerThread = new LoggerStorageManagerThread("LoggerStorageManagerThread");
                storageManagerThread.setDaemon(true);
                storageManagerThread.start();
//                System.out.println("Started LoggerStoreManagerThread");
            } finally {
                LoggerManager.exit();
            }
        }
    }

    public synchronized static void addShutdownHookThread() {
//        System.out.println("Adding shutdown hook");
        Runtime.getRuntime().addShutdownHook(new LoggerStorageManagerShutdownHookThread());
//        System.out.println("Added shutdown hook");
    }

    private static class LoggerStorageManagerThread extends Thread {

        private final LoggerStorageManagerAppend appender;
        private boolean active;

        public LoggerStorageManagerThread(String name) {
            super(name);
            active = true;
            appender = new LoggerStorageManagerAppendImpl();
        }

        @Override
        public void run() {
//            System.out.println("LoggerStorageManagerThread started");
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
//            System.out.println("LoggerStorageManagerThread purging remaining store entries");
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
//            System.out.println("LoggerStorageManagerThread purging remaining active entries");
            // Process the remaining entries
            for(List<String> entries : LoggerStorageManager.active) {
                // store entries
                for(String entry : entries) {
                    try {
                        appender.write(entry);
                    } catch (FileNotFoundException e) {
//                        e.printStackTrace();
                    }
                }
            }
            try {
                appender.close();
            } catch (IOException e) {
//                e.printStackTrace();
            }
//            System.out.println("LoggerStorageManagerThread ended");
        }

        public void done() { this.active = false; }

    }

    private static class LoggerStorageManagerShutdownHookThread extends Thread {
        @Override
        public void run() {
            LoggerManager.enter();
            try {
//            System.out.println("INSIDE SHUTDOWN HOOK");
                // Update the mechanism that stores the entries
                creator = storageCreator;
                // Inform the thread to start to drain all entries.
                storageManagerThread.done();
                // interrupt the thread
                storageManagerThread.interrupt();
                try {
//                System.out.println("INSIDE SHUTDOWN HOOK: WAITING FOR STORAGE THREAD TO COMPLETE");
                    storageManagerThread.join();
                } catch (InterruptedException e) {
                    e.printStackTrace(System.out);
                }
//            System.out.println("INSIDE SHUTDOWN HOOK: STORAGE THREAD COMPLETED");
            } finally {
                LoggerManager.exit();
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
    private static class LoggerStorageManagerAppendImpl implements LoggerStorageManagerAppend {

        private final String fileNamePrefix;
        private FileOutputStream fos;
        private PrintWriter writer;
        private int count;
        private int messages;

        LoggerStorageManagerAppendImpl() {
            // TODO: synchronize the different counters.
            count = 1;
            fileNamePrefix = String.format("Plogger-%s",
                    new SimpleDateFormat("yyyy-MM-dd-HH-mm-ssSSSZ").format(Calendar.getInstance().getTime()));
            try {
                fos = new FileOutputStream(String.format("%s-%d.txt", fileNamePrefix, count));
            } catch (FileNotFoundException e) {
                e.printStackTrace();
            }
            writer = new PrintWriter(fos);
            messages = 0;
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
