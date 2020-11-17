package org.valhalla.plogger.instrumentation.itests;

import org.junit.jupiter.api.Test;

import java.util.Map;

public class LoggerITCase {

    @Test
    public void itestLoggerWrite() {
        for(Map.Entry<Object,Object> entry : System.getProperties().entrySet()) {
            System.out.println(entry.getKey() + " = " + entry.getValue());
        }
        System.out.println("Executing an integration test");
    }
}
