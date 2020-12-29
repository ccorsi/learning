package org.valhalla.plogger.instrumentation;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileFilter;
import java.io.FileReader;
import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.List;

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

class LoggerTests {

    private boolean calledShutdown;

    @BeforeEach
    void setUp() {
        System.setErr(System.out);
        LoggerDebug.initialize("");
        calledShutdown = false;
    }

    @AfterEach
    void tearDown() {
        // Insure that the LoggerManager has been reset properly.
        if ( ! calledShutdown )
            LoggerManager.shutdown();
        LoggerDebug.reset();
        if (debug) System.out.println(String.format("Completed Test %s", testName));
        System.setErr(System.err);
    }

    private String testName = "unknown";
    private boolean debug = false;

    private void start(String name) {
        testName = name;
        if (debug) System.out.println(String.format("Started Test %s", testName));
    }

    interface Executor {
        void execute() throws Throwable;
    }

    class ClassExecutor implements Executor {

        private final Class<?> clz;
        private final String methodName;
        private final Object[] parameterValues;

        ClassExecutor(Class<?> clz, String methodName) {
            this(clz, methodName, null);
        }

        ClassExecutor(Class<?> clz, String methodName, Object[] parameterValues) {
            this.clz = clz;
            this.methodName = methodName;
            this.parameterValues = parameterValues;
        }

        @Override
        public void execute() throws Throwable {
            if (parameterValues != null) {
                Logger.write(clz, methodName, parameterValues);
            } else {
                Logger.write(clz, methodName);
            }
        }
    }

    class InstanceExecutor implements Executor {

        private final Object instance;
        private final String methodName;
        private final Object[] parameterValues;

        InstanceExecutor(Object instance, String methodName) {
            this(instance, methodName, null);
        }

        InstanceExecutor(Object instance, String methodName, Object[] parameterValues) {
            this.instance = instance;
            this.methodName = methodName;
            this.parameterValues = parameterValues;
        }

        @Override
        public void execute() throws Throwable {
            if (parameterValues != null) {
                Logger.write(instance, methodName, parameterValues);
            } else {
                Logger.write(instance, methodName);
            }
        }
    }

    @Test
    public void testClassNoArgLog() throws Throwable {
        start("testClassNoArgLog");
        final String prefix = "LoggerManagerTest-ClassNoArgLog";
        Executor executor = new Executor() {
            @Override
            public void execute() {
                Logger.write(LoggerTests.class, "staticPrint");
            }
        };
        List<String> lines = executeTest(prefix, executor);
        Assertions.assertTrue(lines.get(0).contains("staticPrint"));
    }

    @Test
    public void testClassWithSingleArg() throws Throwable {
        start("testClassWithSingleArg");
        String prefix = "LoggerManagerTest-ClassWithSingleArg";
        final String methodName = "staticWithSingleArg";
        Executor executor = new ClassExecutor(LoggerTests.class, methodName, new Object[] { "Simple Arg"});
        List<String> lines = executeTest(prefix, executor);
        String entry = lines.get(0);
        Assertions.assertTrue(entry.contains(methodName), "Method entry is missing");
        Assertions.assertTrue(entry.contains("String[Simple Arg]"), "Method entry parameter is missing");
    }

    @Test
    public void testObjectNoArgLog() throws Throwable {
        start("testObjectNoArgLog");
        final String prefix = "LoggerManagerTest-ObjectNoArgLog";
        Executor executor = new InstanceExecutor(this, "instancePrint");
        List<String> lines = executeTest(prefix, executor);
        String entry = lines.get(0);
        Assertions.assertTrue(entry.contains("instancePrint"), "Method entry is missing");
        String hashCode = String.valueOf(System.identityHashCode(this));
        Assertions.assertTrue(entry.contains(hashCode), "Object entry hash code is missing");
    }

    @Test
    public void testObjectWithSingleArg() throws Throwable {
        start("testObjectWithSingleArg");
        String prefix = "LoggerManagerTest-ObjectWithSingleArg";
        final String methodName = "instanceWithSingleArg";
        final int value = 101;
        Executor executor = new InstanceExecutor(this, methodName, new Object[] { 101 });
        List<String> lines = executeTest(prefix, executor);
        String entry = lines.get(0);
//        System.out.println("Entry: " + entry);
        Assertions.assertTrue(entry.contains(methodName), "Method entry is missing");
        String hashCode = String.valueOf(System.identityHashCode(this));
        Assertions.assertTrue(entry.contains(hashCode), "Object entry hash code is missing");
        Assertions.assertTrue(entry.contains(String.format("Integer[%d]", value)),
                "Method entry parameter is missing");
    }

    @Test
    public void testByteParameter() throws Throwable {
        start("testByteParameter");
        String prefix = "LoggerManagerTest-ByteParameter";
        final String methodName = "instanceByteParameter";
        final byte value = 'a';
        Executor executor = new InstanceExecutor(this, methodName, new Object[] { value });
        List<String> lines = executeTest(prefix, executor);
        String entry = lines.get(0);
//        System.out.println("Entry: " + entry);
        Assertions.assertTrue(entry.contains(methodName), "Method entry is missing");
        String hashCode = String.valueOf(System.identityHashCode(this));
        Assertions.assertTrue(entry.contains(hashCode), "Object entry hash code is missing");
        Assertions.assertTrue(entry.contains(String.format("Byte[%d]", value)),
                "Method entry parameter is missing");
    }

    @Test
    public void testBooleanParameter() throws Throwable {
        start("testBooleanParameter");
        String prefix = "LoggerManagerTest-BooleanParameter";
        final String methodName = "instanceBooleanParameter";
        final boolean value = true;
        Executor executor = new InstanceExecutor(this, methodName, new Object[] { value });
        List<String> lines = executeTest(prefix, executor);
        String entry = lines.get(0);
//        System.out.println("Entry: " + entry);
        Assertions.assertTrue(entry.contains(methodName), "Method entry is missing");
        String hashCode = String.valueOf(System.identityHashCode(this));
        Assertions.assertTrue(entry.contains(hashCode), "Object entry hash code is missing");
        Assertions.assertTrue(entry.contains(String.format("Boolean[%s]", String.valueOf(value))),
                "Method entry parameter is missing");
    }

    @Test
    public void testCharacterParameter() throws Throwable {
        start("testCharacterParameter");
        String prefix = "LoggerManagerTest-CharacterParameter";
        final String methodName = "instanceCharacterParameter";
        final char value = 'b';
        Executor executor = new InstanceExecutor(this, methodName, new Object[] { value });
        List<String> lines = executeTest(prefix, executor);
        String entry = lines.get(0);
//        System.out.println("Entry: " + entry);
        Assertions.assertTrue(entry.contains(methodName), "Method entry is missing");
        String hashCode = String.valueOf(System.identityHashCode(this));
        Assertions.assertTrue(entry.contains(hashCode), "Object entry hash code is missing");
        Assertions.assertTrue(entry.contains(String.format("Character[%s]", String.valueOf(value))),
                "Method entry parameter is missing");
    }

    @Test
    public void testShortParameter() throws Throwable {
        start("testShortParameter");
        String prefix = "LoggerManagerTest-ShortParameter";
        final String methodName = "instanceShortParameter";
        final short value = 1003;
        Executor executor = new InstanceExecutor(this, methodName, new Object[] { value });
        List<String> lines = executeTest(prefix, executor);
        String entry = lines.get(0);
//        System.out.println("Entry: " + entry);
        Assertions.assertTrue(entry.contains(methodName), "Method entry is missing");
        String hashCode = String.valueOf(System.identityHashCode(this));
        Assertions.assertTrue(entry.contains(hashCode), "Object entry hash code is missing");
        Assertions.assertTrue(entry.contains(String.format("Short[%s]", String.valueOf(value))),
                "Method entry parameter is missing");
    }

    @Test
    public void testIntegerParameter() throws Throwable {
        start("testByteParameter");
        String prefix = "LoggerManagerTest-ByteParameter";
        final String methodName = "instanceByteParameter";
        final byte value = 'a';
        Executor executor = new InstanceExecutor(this, methodName, new Object[] { value });
        List<String> lines = executeTest(prefix, executor);
        String entry = lines.get(0);
//        System.out.println("Entry: " + entry);
        Assertions.assertTrue(entry.contains(methodName), "Method entry is missing");
        String hashCode = String.valueOf(System.identityHashCode(this));
        Assertions.assertTrue(entry.contains(hashCode), "Object entry hash code is missing");
        Assertions.assertTrue(entry.contains(String.format("Byte[%d]", value)),
                "Method entry parameter is missing");
    }

    @Test
    public void testLongParameter() throws Throwable {
        start("testLongParameter");
        String prefix = "LoggerManagerTest-LongParameter";
        final String methodName = "instanceLongParameter";
        final long value = 1001001;
        Executor executor = new InstanceExecutor(this, methodName, new Object[] { value });
        List<String> lines = executeTest(prefix, executor);
        String entry = lines.get(0);
//        System.out.println("Entry: " + entry);
        Assertions.assertTrue(entry.contains(methodName), "Method entry is missing");
        String hashCode = String.valueOf(System.identityHashCode(this));
        Assertions.assertTrue(entry.contains(hashCode), "Object entry hash code is missing");
        Assertions.assertTrue(entry.contains(String.format("Long[%s]", String.valueOf(value))),
                "Method entry parameter is missing");
    }

    @Test
    public void testFloatParameter() throws Throwable {
        start("testFloatParameter");
        String prefix = "LoggerManagerTest-FloatParameter";
        final String methodName = "instanceFloatParameter";
        final float value = 3.145f;
        Executor executor = new Executor() {
            @Override
            public void execute() {
                Logger.write(this, methodName, new Object[] { value });
            }
        };
        List<String> lines = executeTest(prefix, executor);
        String entry = lines.get(0);
//        System.out.println("Entry: " + entry);
        Assertions.assertTrue(entry.contains(methodName), "Method entry is missing");
        String hashCode = String.valueOf(System.identityHashCode(executor));
        Assertions.assertTrue(entry.contains(hashCode), "Object entry hash code is missing");
        Assertions.assertTrue(entry.contains(String.format("Float[%s]", String.valueOf(value))),
                "Method entry parameter is missing");
    }

    @Test
    public void testDoubleParameter() throws Throwable {
        start("testDoubleParameter");
        String prefix = "LoggerManagerTest-DoubleParameter";
        final String methodName = "instanceDoubleParameter";
        final double value = 101.56;
        Executor executor = new Executor() {
            @Override
            public void execute() {
                Logger.write(this, methodName, new Object[] { value });
            }
        };
        List<String> lines = executeTest(prefix, executor);
        String entry = lines.get(0);
//        System.out.println("Entry: " + entry);
        Assertions.assertTrue(entry.contains(methodName), "Method entry is missing");
        String hashCode = String.valueOf(System.identityHashCode(executor));
        Assertions.assertTrue(entry.contains(hashCode), "Object entry hash code is missing");
        Assertions.assertTrue(entry.contains(String.format("Double[%s]", String.valueOf(value))),
                "Method entry parameter is missing");
    }

    @Test
    public void testEnumParameter() throws Throwable {
        start("testEnumParameter");
        String prefix = "LoggerManagerTest-EnumParameter";
        final String methodName = "instanceEnumParameter";
        final Thread.State value = Thread.State.RUNNABLE;
        Executor executor = new InstanceExecutor(this, methodName, new Object[] { value });
        List<String> lines = executeTest(prefix, executor);
        String entry = lines.get(0);
//        System.out.println("Entry: " + entry);
        Assertions.assertTrue(entry.contains(methodName), "Method entry is missing");
        String hashCode = String.valueOf(System.identityHashCode(this));
        Assertions.assertTrue(entry.contains(hashCode), "Object entry hash code is missing");
        Assertions.assertTrue(entry.contains(String.format("Enum[%s]", String.valueOf(value))),
                "Method entry parameter is missing");
    }

    @Test
    public void testByteArrayParameter() throws Throwable {
        start("testByteArrayParameter");
        String prefix = "LoggerManagerTest-ByteArrayParameter";
        final String methodName = "instanceByteArrayParameter";
        final byte[] value = new byte[] { 'a', 'b' };
        String valueType = "byte";
        StringBuilder sb = new StringBuilder(String.valueOf(value[0]));
        for(int idx = 1 ; idx < value.length ; idx++)
            sb.append(',').append(value[idx]);
        String expected = String.format("Array[type=%s,values=[%s]]", valueType, sb.toString());
        createAndRunExecutor(prefix, methodName, new Object[] { value }, expected);
    }

    @Test
    public void testBooleanArrayParameter() throws Throwable {
        start("testBooleanArrayParameter");
        String prefix = "LoggerManagerTest-BooleanArrayParameter";
        final String methodName = "instanceBooleanArrayParameter";
        final boolean[] value = new boolean[] { true, false, false, true };
        String valueType = "boolean";
        StringBuilder sb = new StringBuilder(String.valueOf(value[0]));
        for(int idx = 1 ; idx < value.length ; idx++)
            sb.append(',').append(value[idx]);
        String expected = String.format("Array[type=%s,values=[%s]]", valueType, sb.toString());
        createAndRunExecutor(prefix, methodName, new Object[] { value }, expected);
    }

    @Test
    public void testCharacterArrayParameter() throws Throwable {
        start("testCharacterArrayParameter");
        String prefix = "LoggerManagerTest-CharacterArrayParameter";
        final String methodName = "instanceCharacterArrayParameter";
        final char[] value = new char[] { 'a', 'b', 'c', 'd' };
        String valueType = "char";
        StringBuilder sb = new StringBuilder(String.valueOf(value[0]));
        for(int idx = 1 ; idx < value.length ; idx++)
            sb.append(',').append(value[idx]);
        String expected = String.format("Array[type=%s,values=[%s]]", valueType, sb.toString());
        createAndRunExecutor(prefix, methodName, new Object[] { value }, expected);
    }

    @Test
    public void testShortArrayParameter() throws Throwable {
        start("testShortArrayParameter");
        String prefix = "LoggerManagerTest-ShortArrayParameter";
        final String methodName = "instanceShortArrayParameter";
        final short[] value = new short[] { 10, 11, 12, 13 };
        String valueType = "short";
        StringBuilder sb = new StringBuilder(String.valueOf(value[0]));
        for(int idx = 1 ; idx < value.length ; idx++)
            sb.append(',').append(value[idx]);
        String expected = String.format("Array[type=%s,values=[%s]]", valueType, sb.toString());
        createAndRunExecutor(prefix, methodName, new Object[] { value }, expected);
    }

    @Test
    public void testIntegerArrayParameter() throws Throwable {
        start("testIntegerArrayParameter");
        String prefix = "LoggerManagerTest-IntegerArrayParameter";
        final String methodName = "instanceIntegerArrayParameter";
        final int[] value = new int[] { 110, 111, 112, 113 };
        String valueType = "int";
        StringBuilder sb = new StringBuilder(String.valueOf(value[0]));
        for(int idx = 1 ; idx < value.length ; idx++)
            sb.append(',').append(value[idx]);
        String expected = String.format("Array[type=%s,values=[%s]]", valueType, sb.toString());
        createAndRunExecutor(prefix, methodName, new Object[] { value }, expected);
    }

    @Test
    public void testLongArrayParameter() throws Throwable {
        start("testLongArrayParameter");
        String prefix = "LoggerManagerTest-LongArrayParameter";
        final String methodName = "instanceLongArrayParameter";
        final long[] value = new long[] { 1110, 1111, 1112, 1113 };
        String valueType = "long";
        StringBuilder sb = new StringBuilder(String.valueOf(value[0]));
        for(int idx = 1 ; idx < value.length ; idx++)
            sb.append(',').append(value[idx]);
        String expected = String.format("Array[type=%s,values=[%s]]", valueType, sb.toString());
        createAndRunExecutor(prefix, methodName, new Object[] { value }, expected);
    }

    @Test
    public void testFloatArrayParameter() throws Throwable {
        start("testFloatArrayParameter");
        String prefix = "LoggerManagerTest-FloatArrayParameter";
        final String methodName = "instanceFloatArrayParameter";
        final float[] value = new float[] { 1110.12f, 1111.34f, 1112.56f, 1113.78f };
        String valueType = "float";
        StringBuilder sb = new StringBuilder(String.valueOf(value[0]));
        for(int idx = 1 ; idx < value.length ; idx++)
            sb.append(',').append(value[idx]);
        String expected = String.format("Array[type=%s,values=[%s]]", valueType, sb.toString());
        createAndRunExecutor(prefix, methodName, new Object[] { value }, expected);
    }

    @Test
    public void testDoubleArrayParameter() throws Throwable {
        start("testDoubleArrayParameter");
        String prefix = "LoggerManagerTest-DoubleArrayParameter";
        final String methodName = "instanceDoubleArrayParameter";
        final double[] value = new double[] { 21110.12, 21111.34, 21112.56, 21113.78 };
        String valueType = "double";
        StringBuilder sb = new StringBuilder(String.valueOf(value[0]));
        for(int idx = 1 ; idx < value.length ; idx++)
            sb.append(',').append(value[idx]);
        String expected = String.format("Array[type=%s,values=[%s]]", valueType, sb.toString());
        createAndRunExecutor(prefix, methodName, new Object[] { value }, expected);
    }

    @Test
    public void testByteInstanceArrayParameter() throws Throwable {
        start("testByteInstanceArrayParameter");
        String prefix = "LoggerManagerTest-ByteInstanceArrayParameter";
        final String methodName = "instanceByteInstanceArrayParameter";
        final Byte[] value = new Byte[] { 'a', 'b' };
        String valueType = "Byte";
        StringBuilder sb = new StringBuilder(String.valueOf(value[0]));
        for(int idx = 1 ; idx < value.length ; idx++)
            sb.append(',').append(value[idx]);
        String expected = String.format("Array[type=%s,values=[%s]]", valueType, sb.toString());
        createAndRunExecutor(prefix, methodName, new Object[] { value }, expected);
    }

    @Test
    public void testBooleanInstanceArrayParameter() throws Throwable {
        start("testBooleanInstanceArrayParameter");
        String prefix = "LoggerManagerTest-BooleanInstanceArrayParameter";
        final String methodName = "instanceBooleanInstanceArrayParameter";
        final Boolean[] value = new Boolean[] { true, false, false, true };
        String valueType = "Boolean";
        StringBuilder sb = new StringBuilder(String.valueOf(value[0]));
        for(int idx = 1 ; idx < value.length ; idx++)
            sb.append(',').append(value[idx]);
        String expected = String.format("Array[type=%s,values=[%s]]", valueType, sb.toString());
        createAndRunExecutor(prefix, methodName, new Object[] { value }, expected);
    }

    @Test
    public void testCharacterInstanceArrayParameter() throws Throwable {
        start("testCharacterInstanceArrayParameter");
        String prefix = "LoggerManagerTest-CharacterInstanceArrayParameter";
        final String methodName = "instanceCharacterInstanceArrayParameter";
        final Character[] value = new Character[] { 'a', 'b', 'c', 'd' };
        String valueType = "Character";
        StringBuilder sb = new StringBuilder(String.valueOf(value[0]));
        for(int idx = 1 ; idx < value.length ; idx++)
            sb.append(',').append(value[idx]);
        String expected = String.format("Array[type=%s,values=[%s]]", valueType, sb.toString());
        createAndRunExecutor(prefix, methodName, new Object[] { value }, expected);
    }

    @Test
    public void testShortInstanceArrayParameter() throws Throwable {
        start("testShortInstanceArrayParameter");
        String prefix = "LoggerManagerTest-ShortInstanceArrayParameter";
        final String methodName = "instanceShortInstanceArrayParameter";
        final Short[] value = new Short[] { Short.valueOf((short) 10), Short.valueOf((short) 11),
                Short.valueOf((short) 12), Short.valueOf((short) 13) };
        String valueType = "Short";
        StringBuilder sb = new StringBuilder(String.valueOf(value[0]));
        for(int idx = 1 ; idx < value.length ; idx++)
            sb.append(',').append(value[idx]);
        String expected = String.format("Array[type=%s,values=[%s]]", valueType, sb.toString());
        createAndRunExecutor(prefix, methodName, new Object[] { value }, expected);
    }

    @Test
    public void testIntegerInstanceArrayParameter() throws Throwable {
        start("testIntegerInstanceArrayParameter");
        String prefix = "LoggerManagerTest-IntegerInstanceArrayParameter";
        final String methodName = "instanceIntegerInstanceArrayParameter";
        final Integer[] value = new Integer[] { 110, 111, 112, 113 };
        String valueType = "Integer";
        StringBuilder sb = new StringBuilder(String.valueOf(value[0]));
        for(int idx = 1 ; idx < value.length ; idx++)
            sb.append(',').append(value[idx]);
        String expected = String.format("Array[type=%s,values=[%s]]", valueType, sb.toString());
        createAndRunExecutor(prefix, methodName, new Object[] { value }, expected);
    }

    @Test
    public void testLongInstanceArrayParameter() throws Throwable {
        start("testLongInstanceArrayParameter");
        String prefix = "LoggerManagerTest-LongInstanceArrayParameter";
        final String methodName = "instanceLongInstanceArrayParameter";
        final Long[] value = new Long[] { 1110l, 1111l, 1112l, 1113l };
        String valueType = "Long";
        StringBuilder sb = new StringBuilder(String.valueOf(value[0]));
        for(int idx = 1 ; idx < value.length ; idx++)
            sb.append(',').append(value[idx]);
        String expected = String.format("Array[type=%s,values=[%s]]", valueType, sb.toString());
        createAndRunExecutor(prefix, methodName, new Object[] { value }, expected);
    }

    @Test
    public void testFloatInstanceArrayParameter() throws Throwable {
        start("testFloatInstanceArrayParameter");
        String prefix = "LoggerManagerTest-FloatInstanceArrayParameter";
        final String methodName = "instanceFloatInstanceArrayParameter";
        final Float[] value = new Float[] { 1110.12f, 1111.34f, 1112.56f, 1113.78f };
        String valueType = "Float";
        StringBuilder sb = new StringBuilder(String.valueOf(value[0]));
        for(int idx = 1 ; idx < value.length ; idx++)
            sb.append(',').append(value[idx]);
        String expected = String.format("Array[type=%s,values=[%s]]", valueType, sb.toString());
        createAndRunExecutor(prefix, methodName, new Object[] { value }, expected);
    }

    @Test
    public void testDoubleInstanceArrayParameter() throws Throwable {
        start("testDoubleInstanceArrayParameter");
        String prefix = "LoggerManagerTest-DoubleInstanceArrayParameter";
        final String methodName = "instanceDoubleInstanceArrayParameter";
        final Double[] value = new Double[] { 21110.12, 21111.34, 21112.56, 21113.78 };
        String valueType = "Double";
        StringBuilder sb = new StringBuilder(String.valueOf(value[0]));
        for(int idx = 1 ; idx < value.length ; idx++)
            sb.append(',').append(value[idx]);
        String expected = String.format("Array[type=%s,values=[%s]]", valueType, sb.toString());
        createAndRunExecutor(prefix, methodName, new Object[] { value }, expected);
    }

    @Test
    public void testBigIntegerArrayParameter() throws Throwable {
        start("testBigIntegerArrayParameter");
        String prefix = "LoggerManagerTest-BigIntegerArrayParameter";
        final String methodName = "instanceBigIntegerArrayParameter";
        final BigInteger[] value = new BigInteger[] { new BigInteger("2111012"), new BigInteger("2111134"),
                new BigInteger("2111256"), new BigInteger("2111378") };
        String valueType = "BigInteger";
        StringBuilder sb = new StringBuilder(String.valueOf(value[0]));
        for(int idx = 1 ; idx < value.length ; idx++)
            sb.append(',').append(value[idx]);
        String expected = String.format("Array[type=%s,values=[%s]]", valueType, sb.toString());
        createAndRunExecutor(prefix, methodName, new Object[] { value }, expected);
    }

    @Test
    public void testBigDecimalArrayParameter() throws Throwable {
        start("testBigIntegerArrayParameter");
        String prefix = "LoggerManagerTest-BigIntegerArrayParameter";
        final String methodName = "instanceBigIntegerArrayParameter";
        final BigDecimal[] value = new BigDecimal[] { new BigDecimal("2111012.12"), new BigDecimal("2111134.34"),
                new BigDecimal("2111256.56"), new BigDecimal("2111378.78") };
        String valueType = "BigDecimal";
        StringBuilder sb = new StringBuilder(String.valueOf(value[0]));
        for(int idx = 1 ; idx < value.length ; idx++)
            sb.append(',').append(value[idx]);
        String expected = String.format("Array[type=%s,values=[%s]]", valueType, sb.toString());
        createAndRunExecutor(prefix, methodName, new Object[] { value }, expected);
    }

    @Test
    public void testEnumArrayParameter() throws Throwable {
        start("testEnumArrayParameter");
        String prefix = "LoggerManagerTest-EnumArrayParameter";
        final String methodName = "instanceEnumArrayParameter";
        final Thread.State[] value = new Thread.State[] { Thread.State.NEW, Thread.State.RUNNABLE,
                Thread.State.BLOCKED, Thread.State.TERMINATED };
        String valueType = "State";
        StringBuilder sb = new StringBuilder(String.valueOf(value[0]));
        for(int idx = 1 ; idx < value.length ; idx++)
            sb.append(',').append(value[idx]);
        String expected = String.format("Array[type=%s,values=[%s]]", valueType, sb.toString());
        createAndRunExecutor(prefix, methodName, new Object[] { value }, expected);
    }

    private void createAndRunExecutor(String prefix, final String methodName, final Object[] value, String expected) throws Throwable {
        Executor executor = new Executor() {
            @Override
            public void execute() {
                Logger.write(this, methodName, value);
            }
        };
        List<String> lines = executeTest(prefix, executor);
        String entry = lines.get(0);
        if (debug) System.out.println("Entry: " + entry);
        Assertions.assertTrue(entry.contains(methodName), "Method entry is missing");
        String hashCode = String.valueOf(System.identityHashCode(executor));
        Assertions.assertTrue(entry.contains(hashCode), "Object entry hash code is missing");
        if (debug) System.out.println("Expected: " + expected);
        Assertions.assertTrue(entry.contains(expected),
                "Method entry parameter is missing");
    }

    @Test
    public void testMultipleEntries() throws Throwable {
        start("testMultipleEntries");
        final String prefix = "LoggerManagerTest-MultipleEntries";
        final List<String> methodNames =  new ArrayList<>();
        Executor executor = new Executor() {
            @Override
            public void execute() {
                for (int idx = 1 ; idx < 11 ; idx++) {
                    String methodName = String.format("%03d", idx);
                    methodNames.add(methodName);
                    Logger.write(this, methodName);
                }
            }
        };
        List<String> lines = executeTest(prefix, executor);
        Assertions.assertEquals(methodNames.size(), lines.size(), "Missing some log entries");
        Assertions.assertTrue(lines.get(0).contains(methodNames.get(0)));
    }

    private List<String> executeTest(String prefix, Executor executor) throws Throwable {
        return executeTests(prefix, new Executor[] { executor });
    }

    private List<String> executeTests(final String prefix, Executor[] executors) throws Throwable {
//        System.out.println("Initializing LoggerManager");
        // Initialize the Logger Manager
        LoggerManager.init(new String[] { "prefix=" + prefix});
//        System.out.println("Calling executor");
        // Execute the Logger calls
        for(Executor executor : executors) {
            executor.execute();
        }
//        System.out.println("Shutting down LoggerManager");
        // Shutdown/clean up the Logger Manager
        LoggerManager.shutdown();
        calledShutdown = true;
//        System.out.println("LoggerManager has been shutdown");
        // Find the created Parameter Logger File with the passed prefix
        File[] files = new File(".").listFiles(new FileFilter() {
            @Override
            public boolean accept(File file) {
                return file.getName().startsWith(prefix);
            }
        });
        // Insure that it is non-null
        Assertions.assertNotNull(files, "No files were found");
        // Insure that only one Parameter Log file was found
        Assertions.assertEquals(1, files.length);
        try {
            // Determine that something was written to the log file
            Assertions.assertTrue(files[0].length() > 0, "Nothing was store in the log file");
            List<String> lines = new ArrayList<>();
            // Read each written line and store it within a list.
            try (FileReader fr = new FileReader(files[0])) {
                BufferedReader br = new BufferedReader(fr);
                for (String line = br.readLine() ; line != null ;  line = br.readLine()) {
//                    System.out.println(line);
                    lines.add(line);
                }
            }
            // return the list of parameter log entries
            return lines;
        } finally {
            // Delete the created parameter log file.
            files[0].delete();
        }
    }
}