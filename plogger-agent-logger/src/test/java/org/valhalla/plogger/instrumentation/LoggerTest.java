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

import org.junit.jupiter.api.AfterAll;
import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;

import java.io.File;
import java.io.FileFilter;
import java.util.List;

class LoggerTest {

    @AfterAll
    public static void deleteFiles() {
        File[] files = new File(".").listFiles(new FileFilter() {
            @Override
            public boolean accept(File file) {
                return file.getName().startsWith("PLogger");
            }
        });

        for(File file : files) {
            file.delete();
        }

    }

    @BeforeEach
    void before() {
        // Initialize the entries buffer
        LoggerManager.init(new String[0]);
    }

    @AfterEach
    void after() {
        // Remove the generated entries buffer
        LoggerManager.shutdown();
        LoggerDebug.reset();
    }

    @Test
    void testWriteClassSingleParameter() throws InterruptedException {
        LoggerWriterParameter[] parameters  = new LoggerWriterParameter[] {
                new LoggerWriterClassParameter(Integer.class, "parseInt", new Object[] {"101"}),
        };
        List<String> entries = executeLoggerWriterParameters(parameters);
        String message = entries.get(0);
        Assertions.assertTrue(message.contains(Integer.class.getName()), "Missing Integer class");
    }

    @Test
    void testWriteObjectSingleParameter() throws InterruptedException {
        final Integer i = Integer.valueOf(1003);
        final Integer o = Integer.valueOf(1001);


        LoggerWriterParameter[] parameters  = new LoggerWriterParameter[] {
                new LoggerWriterInstanceParameter(i, "compareTo", new Object[] {o}),
        };
        List<String> entries = executeLoggerWriterParameters(parameters);
        String message = entries.get(0);
        String string = i.getClass().getName() + "@" + System.identityHashCode(i);
        Assertions.assertTrue(message.contains(string), "Missing Integer instance");
    }

    @Test
    void testWriteClassMultipleParameters() throws InterruptedException {
        LoggerWriterParameter[] parameters  = new LoggerWriterParameter[] {
                new LoggerWriterClassParameter(Integer.class, "getInteger", new Object[] {"101", 10}),
        };
        List<String> entries = executeLoggerWriterParameters(parameters);
        String message = entries.get(0);
        Assertions.assertTrue(message.contains(Integer.class.getName()), "Missing Integer class");
    }

    @Test
    void testWriteObjectMultipleParameters() throws InterruptedException {
        final Integer i = Integer.valueOf(1003);
        final Integer o = Integer.valueOf(1001);

        LoggerWriterParameter[] parameters  = new LoggerWriterParameter[] {
                new LoggerWriterInstanceParameter(i, "compareTo", new Object[] {o, 101}),
        };
        List<String> entries = executeLoggerWriterParameters(parameters);
        String message = entries.get(0);
        String string = i.getClass().getName() + "@" + System.identityHashCode(i);
        Assertions.assertTrue(message.contains(string), "Missing Integer instance");
    }

    @Test
    void testWriteObjectMultipleEntries() throws InterruptedException {
        final Integer i = Integer.valueOf(1003);
        final Integer o = Integer.valueOf(1001);

        LoggerWriterParameter[] parameters  = new LoggerWriterParameter[] {
                new LoggerWriterInstanceParameter(i, "compareTo", new Object[] {o, 101}),
                new LoggerWriterInstanceParameter(i, "compareTo", new Object[] {o, 102}),
        };
        List<String> entries = executeLoggerWriterParameters(parameters);
        String message = entries.get(0);
        String string = i.getClass().getName() + "@" + System.identityHashCode(i);
        Assertions.assertTrue(message.contains(string), "Missing Integer instance");
    }

    @Test
    public void testBooleanArray() throws InterruptedException {
        final boolean[] values = new boolean[] {true, false, true, true, true};
        LoggerWriterParameter[] parameters  = new LoggerWriterParameter[] {
                new LoggerWriterInstanceParameter(this, "run", new Object[] { values }),
        };
        List<String> entries = executeLoggerWriterParameters(parameters);
        String message = entries.get(0);
        StringBuilder sb = new StringBuilder("Array[type=boolean,values=[");
        sb.append(values[0]);
        for(int idx = 1 ; idx < values.length ; idx++) {
            sb.append(',').append(values[idx]);
        }
        sb.append(']');
        String string = sb.toString();
        Assertions.assertTrue(message.contains(string), "Missing boolean array instance");
    }

    @Test
    public void testBooleanTrimArray() throws InterruptedException {
        final boolean[] values = new boolean[] {true, false, true, true, true, false, true, true, true};
        LoggerWriterParameter[] parameters  = new LoggerWriterParameter[] {
                new LoggerWriterInstanceParameter(this, "run", new Object[] { values }),
        };
        List<String> entries = executeLoggerWriterParameters(parameters);
        String message = entries.get(0);
        StringBuilder sb = new StringBuilder("Array[type=boolean,values=[");
        sb.append(values[0]);
        for(int idx = 1; idx < Logger.DEFAULT_MAX_SIZE; idx++) {
            sb.append(',').append(values[idx]);
        }
        sb.append(",...]");
        String string = sb.toString();
        Assertions.assertTrue(message.contains(string), "Missing trimmed boolean array instance");
    }

    @Test
    @Disabled("Need to fix issue with logging multi-dimensional parameters")
    public void testBooleanMultiArray() throws InterruptedException {
        final boolean[][] values = new boolean[][] {
                new boolean[] {true, false, true, true, true},
                new boolean[] {true, false, true, true},
                new boolean[] {true, false, true},
                new boolean[] {true, false},
        };
        LoggerWriterParameter[] parameters  = new LoggerWriterParameter[] {
                new LoggerWriterInstanceParameter(this, "run", new Object[] { values }),
        };
        List<String> entries = executeLoggerWriterParameters(parameters);
        String message = entries.get(0);
        StringBuilder sb = new StringBuilder("Array[type=boolean,values=[");
        sb.append(values[0]);
        for(int idx = 1 ; idx < values.length ; idx++) {
            sb.append(',').append(values[idx]);
        }
        sb.append(']');
        String string = sb.toString();
        System.out.println("MESSAGE = " + message);
        System.out.println("STRING  = " + string);
        // TODO: uncomment assertion since this test is failing
        Assertions.assertTrue(message.contains(string), "Missing boolean array instance");
    }

    private List<String> executeLoggerWriterParameters(LoggerWriterParameter[] parameters) throws InterruptedException {
        LoggerThreadTest thread = new LoggerThreadTest(parameters);
        thread.start();
        thread.join();
        List<String> entries = thread.getEntries();
        Assertions.assertNotNull(entries);
        Assertions.assertEquals(parameters.length, entries.size());
        return entries;
    }

    interface LoggerWriterParameter {
        void execute();
    }

    static class LoggerWriterInstanceParameter implements LoggerWriterParameter {

        private final Object object;
        private final String methodName;
        private final Object[] parameters;

        LoggerWriterInstanceParameter(Object object, String methodName, Object[] parameters) {
            this.object = object;
            this.methodName = methodName;
            this.parameters = parameters;
        }

        @Override
        public void execute() {
            Logger.write(object, methodName, parameters);
        }
    }

    static class LoggerWriterClassParameter implements LoggerWriterParameter {

        private final Class<?> object;
        private final String methodName;
        private final Object[] parameters;

        LoggerWriterClassParameter(Class<?> object, String methodName, Object[] parameters) {
            this.object = object;
            this.methodName = methodName;
            this.parameters = parameters;
        }

        @Override
        public void execute() {
            Logger.write(object, methodName, parameters);
        }
    }

    static class LoggerThreadTest extends Thread {

        private final LoggerWriterParameter[] parameters;
        private List<String> entries;

        LoggerThreadTest(LoggerWriterParameter[] parameters) {
            super();
            this.parameters = parameters;
        }

        public List<String> getEntries() {
            return entries;
        }

        @Override
        public void run() {
            // Get a reference to the entries list
            entries = LoggerManager.getEntriesBuffer();
            for (LoggerWriterParameter parameter : parameters) {
                parameter.execute();
            }
        }

    }
}
