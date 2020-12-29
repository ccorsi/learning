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

import java.util.List;

public class LoggerManager {

    private static final LoggerDebug debug = LoggerDebug.getDebug("loggermanager");

    private static ThreadLocal<Boolean> state;
    private static LoggerStorageManager.LoggerStorageManagerShutdownHookThread shutdownHook;

    private static class BooleanThreadLocal extends ThreadLocal<Boolean> {
        @Override
        protected Boolean initialValue() {
            return Boolean.FALSE;
        }
    }

    public static void init(String[] appenderSettings) {
        enter();
        state = new BooleanThreadLocal();
        buffers = createBufferThreadLocal();
        maxEntries = 99;
        try {
            for(String setting : appenderSettings) {
                if (setting.startsWith("maxentries=")) {
                    try {
                        maxEntries = Integer.parseInt(setting.substring("maxentries=".length()));
                        if (debug.isDebug()) {
                            debug.debug(String.format("Set maxEntries to %d", maxEntries));
                        }
                    } catch (NumberFormatException nfe) {
                        // do nothing
                    }
                }
            }
            shutdownHook = LoggerStorageManager.addShutdownHookThread();
            LoggerStorageManager.startLoggerStorageManagerThread(appenderSettings);
        } catch (RuntimeException e) {
            if (debug.isDebug()) {
                debug.debug("An exception was generated when initializing the LoggerManager", e);
            }
            throw e;
        } catch (Throwable t) {
            if (debug.isDebug()) {
                debug.debug("An exception was generated when initializing the LoggerManager", t);
            }
            throw new RuntimeException(t);
        } finally {
            exit();
        }
    }

    public static void shutdown() {
        if (shutdownHook != null) {
            // Only process this if it is non-null.
            Runtime.getRuntime().removeShutdownHook(shutdownHook);
            shutdownHook.setDaemon(true);
            shutdownHook.start();
            try {
                shutdownHook.join();
            } catch (InterruptedException e) {
                // do nothing
            }
            shutdownHook = null;
        }
    }

    private static int maxEntries;

    private static ThreadLocal<List<String>> buffers;

    private static ThreadLocal<List<String>> createBufferThreadLocal() {
        return new ThreadLocal<List<String>>() {

            @Override
            protected List<String> initialValue() {
                return LoggerStorageManager.createEntriesBuffer();
            }

            @Override
            public List<String> get() {
                List<String> buffer = super.get();
                if (buffer == null  || buffer.size() > maxEntries) {
                    LoggerStorageManager.store(buffer);
                    buffer = LoggerStorageManager.createEntriesBuffer();
                    set(buffer);
                    if (debug.isDebug()) {
                        debug.debug("Created a new entries buffer");
                    }
                }
                return buffer;
            }
        };
    }

    public static List<String> getEntriesBuffer() {
        return buffers.get();
    }

    public static boolean enter() {
        if (state != null && state.get() == Boolean.FALSE) {
            state.set(Boolean.TRUE);
            return true;
        }
        return false;
    }

    public static void exit() {
        if (state != null && state.get() == Boolean.TRUE) {
            state.set(Boolean.FALSE);
        }
    }

}
