package org.valhalla.plogger.instrumentation;

import java.io.IOException;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.LinkedBlockingQueue;

public class LoggerStorageManager {
    private static final LinkedBlockingQueue<List<String>> store = new LinkedBlockingQueue<List<String>>();
    private static final LinkedBlockingQueue<List<String>> active = new LinkedBlockingQueue<List<String>>();
    private static LoggerStorageManagerThread storageManagerThread = null;
    private static final LoggerStorageManagerCreator activeCreator = new ActiveCreator();
    private static final LoggerStorageManagerCreator storageCreator = new StorageCreator();
    private static LoggerStorageManagerCreator creator = activeCreator;

    public static List<String> createEntriesBuffer() {
        return creator.get();
    }

    public static void store(List<String> buffer) {
        creator.add(buffer);
    }

    public synchronized static void startLoggerStorageManagerThread() {
        if (storageManagerThread == null) {
            storageManagerThread = new LoggerStorageManagerThread("LoggerStorageManagerThread");
            storageManagerThread.start();
        }
    }

    public synchronized static void addShutdownHookThread() {
        Runtime.getRuntime().addShutdownHook(new LoggerStorageManagerShutdownHookThread());
    }

    private static class LoggerStorageManagerThread extends Thread {

        private boolean active;

        public LoggerStorageManagerThread(String name) {
            super(name);
            active = true;
        }

        @Override
        public void run() {
            // Process active entries when processing log entries
            while(active) {
                try {
                    // Get the next entries list and store it
                    List<String> entries = store.take();
                    // store entries
                    for (String entry : entries) {
                        // TODO: Really Store the Entry
                        System.out.println(entry);
                    }
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
            // Process the remaining entries
            for(List<String> entries : store) {
                // store entries
                for (String entry : entries) {
                    // TODO: Really Store the Entry
                    System.out.println(entry);
                }
            }
            // Process the remaining entries
            for(List<String> entries : LoggerStorageManager.active) {
                // store entries
                for(String entry : entries) {
                    // TODO: Really Store the Entry.
                    System.out.println(entry);
                }
            }
        }

        public void done() { this.active = false; }

    }

    private static class LoggerStorageManagerShutdownHookThread extends Thread {
        @Override
        public void run() {
            // Update the mechanism that stores the entries
            creator = storageCreator;
            // Inform the thread to start to drain all entries.
        }
    }

    private static interface LoggerStorageManagerCreator {
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

    /**
     * TODO: Implement class
     *
     * It should create files with the PLogger-[DATE]-[COUNT].txt?
     *
     * It should just store the written data to a file and determine if it needs to
     * close and open a new file....
     *
     */
    private static class LoggerStorageManagerOutputStream extends OutputStream {

        public LoggerStorageManagerOutputStream() {

        }

        @Override
        public void write(int b) throws IOException {

        }
    }
}
