package org.valhalla.plogger.instrumentation.itests;

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

import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.valhalla.plogger.instrumentation.utils.Utils;

import java.io.IOException;

public class LoggerITCase {

    private static String testType;
    private static String mainClassName;
    private static String[] classPaths;

    @BeforeAll
    public static void setStaticFields() {
        testType = "Executing an integration test for jdk 7";
        mainClassName = "org.valhalla.plogger.test.Main";
        classPaths = new String[] {
                System.getProperty("test.app7.classpath")
        };
    }

    @BeforeEach
    public void typeTest() {
        System.out.println(testType);
        System.out.println("Using plogger agent jar: " + System.getProperty("plogger.agent.jar"));
    }

    @Test
    public void simpleLoggerWrite() throws IOException, InterruptedException {
        // This test will just start a java process and determine if it failed or not.
        String mainClassName = "org.valhalla.plogger.test.Main";
        String[] jvmOptions = {
                "-Xverify:all",
                "-Xshare:off", // insure that class sharing is not enabled.
                String.format("-javaagent:%s=debug=exception", System.getProperty("plogger.agent.jar")),
        };
        String[] args = new String[] {
                "simple"
        };
        Utils.executeTest(mainClassName, classPaths, jvmOptions, args);
    }

    @Test
    public void testLoggerWriteFlushForJava7() throws Throwable {
        String[] jvmOptions = {
                "-Xverify:all",
                "-Xshare:off", // insure that class sharing is not enabled.
                String.format("-javaagent:%s=debug=exception", System.getProperty("plogger.agent.jar"))
        };
        String[] args = {
                "count",
                "150"
        };
        Utils.executeTest(mainClassName, classPaths, jvmOptions, args);
    }

    @Test
    public void testLoggerWriteRolloverLogFileForJava7() throws Throwable {
        String[] jvmOptions = {
                "-Xverify:all",
                "-Xshare:off", // insure that class sharing is not enabled.
                String.format("-javaagent:%s=appender=prefix=Rollover;debug=exception",
                        System.getProperty("plogger.agent.jar"))
        };
        String[] args = {
                "count",
                "1100"
        };
        Utils.executeTest(mainClassName, classPaths, jvmOptions, args);
    }

    @Test
    public void testLoggerInstrumentationOfJdk4Class() throws Throwable {
        String[] jvmOptions = {
                "-Xverify:all",
//                "-Xshare:off", // insure that class sharing is not enabled.
                String.format("-javaagent:%s=debug=exception", System.getProperty("plogger.agent.jar"))
        };
        String[] args = {
                "log4j",
        };
        Utils.executeTest(mainClassName, classPaths, jvmOptions, args);
    }

    @Test
    public void testRecursiveCalls() throws Throwable {
        String[] jvmOptions = {
                "-Xverify:all",
//                "-Xshare:off", // insure that class sharing is not enabled.
                String.format("-javaagent:%s=debug=exception", System.getProperty("plogger.agent.jar"))
        };
        String[] args = {
                "recursive",
        };
        Utils.executeTest(mainClassName, classPaths, jvmOptions, args);
    }

    @Test
    public void testDeepRecursiveCalls() throws Throwable {
        String[] jvmOptions = {
                "-Xverify:all",
//                "-Xshare:off", // insure that class sharing is not enabled.
                String.format("-javaagent:%s=debug=exception", System.getProperty("plogger.agent.jar"))
        };
        String[] args = {
                "recursive",
                "50"
        };
        Utils.executeTest(mainClassName, classPaths, jvmOptions, args);
    }
}
