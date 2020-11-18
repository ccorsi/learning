package org.valhalla.plogger.instrumentation.itests;

import org.junit.jupiter.api.Test;
import org.valhalla.plogger.instrumentation.utils.PrintStreamThread;
import org.valhalla.plogger.instrumentation.utils.Utils;

import java.io.*;

public class LoggerITCase {

    @Test
    public void itestLoggerWrite() throws IOException, InterruptedException {
        // This test will just start a java process and determine if it failed or not.
        System.out.println("Executing an integration test");
//        System.out.println("Test Application Class Path for jdk 7: " +
//                System.getProperty("test.app7.classpath"));
//        System.out.println("Test Application Class Path for jdk 9: " +
//                System.getProperty("test.app9.classpath"));
//        System.out.println("Test Class Path: " + System.getProperty("java.class.path"));
//        System.out.println("Java Home: " + System.getProperty("java.home"));
        ProcessBuilder builder = new ProcessBuilder();
        String javaCmd = Utils.getJavaCommand();
        String classPath = System.getProperty("java.class.path") + File.pathSeparator + System.getProperty("test.app7.classpath");
        Process process = builder.command(javaCmd, "-cp", classPath, "org.valhalla.plogger.test.Main").start();
        new PrintStreamThread("out: ", process.getInputStream()).start();
        new PrintStreamThread("err: ", process.getErrorStream()).start();
        System.out.println("Exit code: " + process.waitFor());
    }

}
