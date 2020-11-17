package org.valhalla.plogger.instrumentation;

import java.util.ArrayList;
import java.util.List;

public class LoggerManager {
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
            }
            return buffer;
        }
    };

    public static List<String> getEntriesBuffer() {
        return buffers.get();
    }
}
