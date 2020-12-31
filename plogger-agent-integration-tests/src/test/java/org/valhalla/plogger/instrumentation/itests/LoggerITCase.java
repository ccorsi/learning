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

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.valhalla.plogger.instrumentation.utils.AgentJars;
import org.valhalla.plogger.instrumentation.utils.Utils;

public class LoggerITCase {

    private static String testType;
    private static String mainClassName;
    private static String[] classPaths;
    private static String agentFileName;
    private static String agentLoggerFileName;
    private String logFilePrefix = "PLogger";
    private String agentParameters = "debug=exception";


    @BeforeAll
    public static void setStaticFields() {
        testType = "Executing an integration test for jdk 7";
        mainClassName = "org.valhalla.plogger.test.Main";
        classPaths = new String[] {
                System.getProperty("test.app7.classpath"),
        };
        agentFileName = AgentJars.getAgentJar();
        agentLoggerFileName = AgentJars.getAgentLoggerJar();
    }

    @BeforeEach
    public void typeTest() {
        System.out.println(testType);
        System.out.println("Using plogger agent jar: " + agentFileName);
        System.out.println("Using plogger agent logger jar: " + agentLoggerFileName);
    }

    @AfterEach
    public void deleteLogFiles() {
        Utils.deleteLogFiles(logFilePrefix);
    }

    @Test
    public void simpleLoggerWrite() throws Throwable {
        String[] args = new String[] {
                "simple"
        };

        execute(args, false);
    }

    @Test
    public void testLoggerWriteFlushForJava7() throws Throwable {
        String[] args = {
                "count",
                "150"
        };

        execute(args, false);
    }

    @Test
    public void testLoggerWriteRolloverLogFileForJava7() throws Throwable {
        logFilePrefix = "Rollover";
        String[] args = {
                "count",
                "1100"
        };

        agentParameters = String.format("%s;appender=prefix=%s", agentParameters, logFilePrefix);
        execute(args, false);
    }

    @Test
    public void testLoggerInstrumentationOfJdk4Class() throws Throwable {
        String[] args = {
                "log4j",
        };

        execute(args, false);
    }

    @Test
    public void testRecursiveCalls() throws Throwable {
        String[] args = {
                "recursive",
        };

        execute(args, true);
    }

    @Test
    public void testDeepRecursiveCalls() throws Throwable {
        String[] args = {
                "recursive",
                "debug=false",
                "depth=50",
        };

        execute(args, true);
    }

    @Test
    public void testMultiThreadedLogging() throws Throwable {
        String[] args = {
                "threaded",
        };

        execute(args, true);
    }

    public void execute(String[] args, boolean useClassSharing) throws Throwable {
        String[] jvmOptions = {
                String.format("-Xbootclasspath/a:%s", agentLoggerFileName),
                "-Xverify:all",
                String.format("-Xshare:%s", (useClassSharing ? "on" : "off")),
                String.format("-javaagent:%s=%s", agentFileName, agentParameters),
        };
        Utils.executeTest(mainClassName, classPaths, jvmOptions, args);
    }
}
