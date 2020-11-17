package org.valhalla.plogger.instrumentation;

import java.util.ArrayList;
import java.util.List;

public class LoggerManager {

    private static final ThreadLocal<List<String>> buffers = new ThreadLocal<List<String>>() {

        @Override
        protected List<String> initialValue() {
            return new ArrayList<>();
        }
    };

    public static List<String> getEntriesBuffer() {
        return buffers.get();
    }

    public static void remove() {
        buffers.remove();
    }

}
