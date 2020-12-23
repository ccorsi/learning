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

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.condition.DisabledForJreRange;
import org.junit.jupiter.api.condition.JRE;
import org.valhalla.plogger.instrumentation.utils.Utils;

import java.io.IOException;

public class LoggerForJdk9ITCase {

    private static final String testType = "Executing an integration test for jdk 9";

    @BeforeEach
    public void typeTest() {
        System.out.println(testType);
        System.out.println("Using plogger agent jar: " + System.getProperty("plogger.agent.jar"));
    }

    @Test
    @DisabledForJreRange(disabledReason = "JDK 9 is required to run these integration test",
            max= JRE.JAVA_8)
    public void testLoggerWrite() throws IOException, InterruptedException {
        String mainClassName = "org.valhalla.plogger/org.valhalla.plogger.test.Main";
        String[] classPaths = new String[] {
                System.getProperty("test.app9.classpath")
        };
        String[] jvmOptions = {
                "-Xverify:all",
                "-Xshare:off", // insure that class sharing is not enabled.
                String.format("-javaagent:%s=debug=exception;bytecode=java/io/RandomAccessFile,java/util/concurrent/TimeUnit",
                        System.getProperty("plogger.agent.jar")),
        };
        String[] args = {
                "1"
        };
        String[] modulePaths = {
                System.getProperty("test.app9.modulepath")
        };
        Utils.executeTest(mainClassName, classPaths, jvmOptions, args, modulePaths);
    }

}
