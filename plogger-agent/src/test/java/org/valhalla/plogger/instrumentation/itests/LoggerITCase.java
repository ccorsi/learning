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

import org.junit.jupiter.api.Test;
import org.valhalla.plogger.instrumentation.utils.PrintStreamThread;
import org.valhalla.plogger.instrumentation.utils.Utils;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class LoggerITCase {

    @Test
    public void itestLoggerWrite() throws IOException, InterruptedException {
        // This test will just start a java process and determine if it failed or not.
        System.out.println("Executing an integration test");
        System.out.println("plogger agent jar: " +
                System.getProperty("plogger.agent.jar"));
//        System.out.println("Test Application Class Path for jdk 7: " +
//                System.getProperty("test.app7.classpath"));
//        System.out.println("Test Application Class Path for jdk 9: " +
//                System.getProperty("test.app9.classpath"));
//        System.out.println("Test Class Path: " + System.getProperty("java.class.path"));
//        System.out.println("Java Home: " + System.getProperty("java.home"));
        String mainClassName = "org.valhalla.plogger.test.Main";
        String[] paths = new String[] {
                System.getProperty("test.app7.classpath")
        };
        List<String> jvmOptions =  new ArrayList<String>(2);
//        jvmOptions.add("-verbose");
        jvmOptions.add("-Xshare:off"); // insure that class sharing is not enabled.
        jvmOptions.add(String.format("-javaagent:%s", System.getProperty("plogger.agent.jar")));
        Process process = Utils.createJavaProcess(mainClassName, paths, jvmOptions.toArray(Utils.EMPTY_STRING_ARRAY),
                Utils.EMPTY_STRING_ARRAY);
        new PrintStreamThread("out: ", process.getInputStream()).start();
        new PrintStreamThread("err: ", process.getErrorStream()).start();
        System.out.println("Exit code: " + process.waitFor());
        process = Utils.createJavaProcess("--version", paths);
        new PrintStreamThread("out: ", process.getInputStream()).start();
        new PrintStreamThread("err: ", process.getErrorStream()).start();
        System.out.println("Exit code: " + process.waitFor());
    }

}
