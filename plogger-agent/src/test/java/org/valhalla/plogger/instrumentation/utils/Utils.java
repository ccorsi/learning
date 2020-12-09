package org.valhalla.plogger.instrumentation.utils;

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

import org.junit.jupiter.api.Assertions;

import java.io.File;
import java.io.FileFilter;
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

    public static Process createJavaProcess(String mainClassName, String[] paths, String[] jvmOptions, String[] args) throws IOException {
        ProcessBuilder builder = new ProcessBuilder();
        String javaCmd = getJavaCommand();
        StringBuilder classPaths = new StringBuilder(System.getProperty("java.class.path"));
        for(String path : paths) {
            classPaths.append(File.pathSeparator).append(path);
        }
        String classPath =  classPaths.toString();
        List<String> commands = new LinkedList<String>();
        commands.add(javaCmd);
        for(String jvmOption : jvmOptions) {
            commands.add(jvmOption);
        }
        commands.add("-cp");
        commands.add(classPath);
        commands.add(mainClassName);
        for(String arg : args) {
            commands.add(arg);
        }
        System.out.println(String.format("Starting process: %s", commands));
        Process process = builder.command(commands).start();
        return process;
    }
}
