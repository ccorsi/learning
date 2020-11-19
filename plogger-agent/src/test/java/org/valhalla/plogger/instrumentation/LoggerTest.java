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

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.List;

class LoggerTest {

    @BeforeEach
    void before() {
        // Initialize the entries buffer
        LoggerManager.getEntriesBuffer();
    }

    @AfterEach
    void after() {
        // Remove the generated entries buffer
        LoggerManager.remove();
    }

    @Test
    void testWriteClassSingleParameter() throws InterruptedException {
        LoggerThreadTest thread = new LoggerThreadTest(new Runnable() {
            @Override
            public void run() {
                Logger.write(Integer.class, "parseInt", new Object[] { "101" });
                for(String entry : LoggerManager.getEntriesBuffer()) {
                    System.out.println(entry);
                }
            }
        });
        thread.start();
        thread.join();
        List<String> entries = thread.getEntries();
        Assertions.assertNotNull(entries);
        Assertions.assertEquals(1, entries.size());
        String message = entries.get(0);
        Assertions.assertTrue(message.contains(Integer.class.getName()), "Missing Integer class");
    }

    @Test
    void testWriteObjectSingleParameter() throws InterruptedException {
        final Integer i = Integer.valueOf(1003);
        final Integer o = Integer.valueOf(1001);

        LoggerThreadTest thread = new LoggerThreadTest(new Runnable() {
            @Override
            public void run() {
                Logger.write(i, "compareTo", new Object[] {o});
                for(String entry : LoggerManager.getEntriesBuffer()) {
                    System.out.println(entry);
                }
            }
        });
        thread.start();
        thread.join();
        List<String> entries = thread.getEntries();
        Assertions.assertNotNull(entries);
        Assertions.assertEquals(1, entries.size());
        String message = entries.get(0);
        String string = i.getClass().getName() + "@" + System.identityHashCode(i);
        Assertions.assertTrue(message.contains(string), "Missing Integer instance");
    }

    @Test
    void testWriteClassMultipleParameters() throws InterruptedException {
        LoggerThreadTest thread = new LoggerThreadTest(new Runnable() {
            @Override
            public void run() {
                Logger.write(Integer.class, "getInteger", new Object[] { "101", 10 });
                for(String entry : LoggerManager.getEntriesBuffer()) {
                    System.out.println(entry);
                }
            }
        });
        thread.start();
        thread.join();
        List<String> entries = thread.getEntries();
        Assertions.assertNotNull(entries);
        Assertions.assertEquals(1, entries.size());
        String message = entries.get(0);
        Assertions.assertTrue(message.contains(Integer.class.getName()), "Missing Integer class");
    }

    @Test
    void testWriteObjectMultipleParameters() throws InterruptedException {
        final Integer i = Integer.valueOf(1003);
        final Integer o = Integer.valueOf(1001);

        LoggerThreadTest thread = new LoggerThreadTest(new Runnable() {
            @Override
            public void run() {
                Logger.write(i, "compareTo", new Object[] {o, 101});
                for(String entry : LoggerManager.getEntriesBuffer()) {
                    System.out.println(entry);
                }
            }
        });
        thread.start();
        thread.join();
        List<String> entries = thread.getEntries();
        Assertions.assertNotNull(entries);
        Assertions.assertEquals(1, entries.size());
        String message = entries.get(0);
        String string = i.getClass().getName() + "@" + System.identityHashCode(i);
        Assertions.assertTrue(message.contains(string), "Missing Integer instance");
    }

    @Test
    void testWriteObjectMultipleEntries() throws InterruptedException {
        final Integer i = Integer.valueOf(1003);
        final Integer o = Integer.valueOf(1001);

        LoggerThreadTest thread = new LoggerThreadTest(new Runnable() {
            @Override
            public void run() {
                Logger.write(i, "compareTo", new Object[] {o, 101});
                Logger.write(i, "compareTo", new Object[] {o, 102});
                for(String entry : LoggerManager.getEntriesBuffer()) {
                    System.out.println(entry);
                }
            }
        });
        thread.start();
        thread.join();
        List<String> entries = thread.getEntries();
        Assertions.assertNotNull(entries);
        Assertions.assertEquals(2, entries.size());
        String message = entries.get(0);
        String string = i.getClass().getName() + "@" + System.identityHashCode(i);
        Assertions.assertTrue(message.contains(string), "Missing Integer instance");
    }

    static class LoggerThreadTest extends Thread {

        public List<String> getEntries() {
            return entries;
        }

        private List<String> entries;

        LoggerThreadTest(Runnable runnable) {
            super(runnable);
        }

        @Override
        public void run() {
            // Initialize the entries list
            entries = LoggerManager.getEntriesBuffer();
            try {
                super.run();
            } finally {
                // Clear the created entries buffer
                LoggerManager.remove();
            }
        }

    }
}