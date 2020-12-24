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

    private static final ThreadLocal<Boolean> state = new BooleanThreadLocal();

    private static class BooleanThreadLocal extends ThreadLocal<Boolean> {
        @Override
        protected Boolean initialValue() {
            return Boolean.FALSE;
        }
    }

    public static void init(String[] appenderSettings) {
        enter();
        try {
            LoggerStorageManager.addShutdownHookThread();
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

    private static ThreadLocal<List<String>> buffers = new ThreadLocal<List<String>>() {

        @Override
        protected List<String> initialValue() {
            List<String> buffer = LoggerStorageManager.createEntriesBuffer();
            return buffer;
        }

        @Override
        public List<String> get() {
            List<String> buffer = super.get();
            if (buffer.size() > 99) {
                LoggerStorageManager.store(buffer);
                buffer = LoggerStorageManager.createEntriesBuffer();
                set(buffer);
            }
            return buffer;
        }
    };

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
