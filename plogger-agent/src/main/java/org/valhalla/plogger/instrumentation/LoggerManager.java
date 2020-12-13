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

import java.io.FileNotFoundException;
import java.util.List;

public class LoggerManager {

    private static final ThreadLocal<Boolean> state = new BooleanThreadLocal();

    private static class BooleanThreadLocal extends ThreadLocal<Boolean> {
        @Override
        protected Boolean initialValue() {
            return Boolean.FALSE;
        }
    }

    public static void init() {
//        System.out.println("ENTERED LOGGER MANAGER INIT");
        enter();
        try {
//            System.out.println("BEFORE CALLING LOGGER STORAGE MANAGER");
            LoggerStorageManager.addShutdownHookThread();
//            System.out.println("NEXT CALLING LOGGER STORAGE MANAGER");
            LoggerStorageManager.startLoggerStorageManagerThread();
//            System.out.println("AFTER CALLING LOGGER STORAGE MANAGER");
            // Allow static initialization to be loaded and avoid core dumps.
//            System.out.println("CALLING LOGGER WRITE");
            Logger.write(LoggerManager.class, "init");
//            System.out.println("CALLED LOGGER WRITE");
            exit();
        } catch (RuntimeException e) {
            e.printStackTrace();
            throw e;
        } catch (Throwable t) {
            t.printStackTrace();
            throw new RuntimeException(t);
        } finally {
//            System.out.println("EXITING LOGGER MANAGER INIT");
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
//                System.out.println("BUFFER FULL");
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
