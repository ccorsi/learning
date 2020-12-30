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

public class AgentJars {

    private static String agentJarFileName = null;
    private static String agentLoggerJarFileName = null;
    private static String[] classPaths = null;

    public static String getAgentLoggerJar() {
        if (agentLoggerJarFileName != null)
            return agentLoggerJarFileName;

        String[] classPaths = getJavaClassPath();
        String name;
        name = System.getProperty("plogger.agent.logger.jar");

        for(String path : classPaths) {
            if (path.contains(name)) {
                agentLoggerJarFileName = path;
                return path;
            }
        }

        Assertions.fail(String.format("Unable to fine the Agent jar file: %s", name));
        return null;
    }

    public static String getAgentJar() {
        if (agentJarFileName != null)
            return agentJarFileName;

        String[] classPaths = getJavaClassPath();
        String name = System.getProperty("plogger.agent.jar");

        for(String path : classPaths) {
            if (path.contains(name)) {
                agentJarFileName = path;
                return path;
            }
        }

        Assertions.fail(String.format("Unable to find the Agent Logger jar file: %s", name));
        return null;
    }

    public static String getJarName(String propertyName) {

        String[] classPaths = getJavaClassPath();

        String name = System.getProperty(propertyName);
        Assertions.assertNotNull(name, String.format("Property %s was not defined", propertyName));

        for(String path : classPaths) {
            if (path.contains(name)) {
                return path;
            }
        }

        Assertions.fail(String.format("No jar file %s found"));
        return null;
    }

    private static String[] getJavaClassPath() {
        if (classPaths != null)
            return classPaths;

        String classPath = System.getProperty("java.class.path");
        classPaths = classPath.split(File.pathSeparator);
        return classPaths;
    }
}
