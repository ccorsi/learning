package org.valhalla.plogger.instrumentation.utils;/*
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

import org.junit.jupiter.api.Assertions;

import java.io.File;
import java.io.FileFilter;
import java.io.FilenameFilter;
import java.io.IOException;
import java.util.LinkedList;
import java.util.List;

public class Utils {

    public static final String JAVA_EXECUTABLE = "java" + ((File.separatorChar == '\\') ? ".exe" : "");
    public static final String[] EMPTY_STRING_ARRAY = new String[0];

    public static String getJavaCommand() {
        String javaHome = System.getProperty("java.home");
        File dir = new File(javaHome);
        File[] dirs = dir.listFiles(new FileFilter() {
            @Override
            public boolean accept(File file) {
                return "bin".equals(file.getName());
            }
        });

        Assertions.assertNotNull(dirs, "No bin directories were found");

        for (File file : dirs) {
            File[] javas = file.listFiles(
                    new FileFilter() {
                        @Override
                        public boolean accept(File file) {
                            return JAVA_EXECUTABLE.equals(file.getName());
                        }
                    }
            );
            if (javas != null && javas.length > 0) {
                return javas[0].getAbsolutePath();
            }
        }

        return Assertions.fail("No Java Command found for java.home: " + javaHome);
    }

    public static Process createJavaProcess(String mainClassName, String[] paths) throws IOException {
        return createJavaProcess(mainClassName, paths, EMPTY_STRING_ARRAY, EMPTY_STRING_ARRAY);
    }

    public static Process createJavaProcess(String mainClassName, String[] paths, String[] jvmOptions, String[] args)
            throws IOException {
        return createJavaProcess(mainClassName, paths, jvmOptions, args, EMPTY_STRING_ARRAY);
    }

    public static Process createJavaProcess(String mainClassName, String[] classPaths, String[] jvmOptions,
                                            String[] args, String[] modulePaths)
            throws IOException {
        ProcessBuilder builder = new ProcessBuilder();
        String javaCmd = getJavaCommand();
        List<String> commands = new LinkedList<String>();
        commands.add(javaCmd);
        for(String jvmOption : jvmOptions) {
            commands.add(jvmOption);
        }

        if (classPaths.length > 0) {
            // Add a class path only if it is defined.
            StringBuilder sb = new StringBuilder();
            for(String path : classPaths) {
                sb.append(File.pathSeparator).append(path);
            }
            String classPath =  sb.toString();
            commands.add("-cp");
            commands.add(classPath);
        }

        // NOTE: This has to be process before adding the main class name.  All other configurations need to be
        // added prior to this check.
        if (modulePaths.length > 0) {
            // Add a module path only if it is defined.
            commands.add("-p");
            StringBuilder sb = new StringBuilder();
            for(String modulePath : modulePaths) {
                sb.append(modulePath).append(File.pathSeparator);
            }
            commands.add(sb.toString());

            commands.add("-m");
        }

        commands.add(mainClassName);

        for(String arg : args) {
            commands.add(arg);
        }
        System.out.println(String.format("Starting process: %s", commands));
        Process process = builder.command(commands).start();
        return process;
    }

    public static PrintStreamThread[] executeTest(String mainClassName, String[] classPaths, String[] jvmOptions, String[] args)
            throws IOException, InterruptedException {
        return executeTest(mainClassName, classPaths, jvmOptions, args, EMPTY_STRING_ARRAY);
    }

    public static PrintStreamThread[] executeTest(String mainClassName, String[] classPaths, String[] jvmOptions, String[] args,
                                   String[] modulePaths) throws IOException, InterruptedException {
        Process process = createJavaProcess(mainClassName, classPaths, jvmOptions, args, modulePaths);
        PrintStreamThread[] streams = {
                new PrintStreamThread("out: ", process.getInputStream()),
                new PrintStreamThread("err: ", process.getErrorStream()),
        };
        for (PrintStreamThread stream : streams) {
            stream.start();
        }
        for (PrintStreamThread stream : streams) {
            stream.join();
        }
        int exitCode = process.waitFor();
        System.out.println("Exit code: " + exitCode);
        Assertions.assertEquals(0, exitCode, "Test exited with an error");
        Assertions.assertFalse(streams[1].isOutput(), "Test generated error messages");
        return streams;
    }

    public static void deleteLogFiles(final String logFilePrefix) {
        File root = new File(System.getProperty("user.dir", "."));

        // Find all files that has the passed prefix
        File[] logFiles = root.listFiles(new FilenameFilter() {
            @Override
            public boolean accept(File file, String name) {
                return name.startsWith(logFilePrefix);
            }
        });

        if (logFiles != null) {
            // Delete all found files
            for (File logFile : logFiles) {
                logFile.delete();
            }
        }

    }
}
