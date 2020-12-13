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

import org.valhalla.plogger.instrumentation.bytecode.manager.ClassManager;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.lang.instrument.ClassFileTransformer;
import java.security.ProtectionDomain;

public class AgentClassFileTransformer implements ClassFileTransformer {

    public byte[] transform(ClassLoader loader, String className, Class<?> classBeingRedefined, ProtectionDomain protectionDomain, byte[] classfileBuffer) {
        if (! className.startsWith("org/valhalla/plogger/instrumentation")
                && ! className.contains("sun/launcher/LauncherHelper") && ! className.startsWith("java/lang")) {
            try {
                ClassManager classManager = new ClassManager(className, classfileBuffer);
                if (classManager.instrument()) {
                    ByteArrayOutputStream bos = new ByteArrayOutputStream();
                    try (DataOutputStream dos = new DataOutputStream(bos)) {
                        classManager.write(dos);
                    }
                    System.out.println("Instrumented class: " + className);
                    return bos.toByteArray();
                }
            } catch (Throwable e) {
                System.out.println("An exception was thrown when transforming class: " + className);
                e.printStackTrace(System.out);
                decompileJavaClass(className);
            }
        }
        return null;
    }

    private void decompileJavaClass(String className) {
        try {
            System.out.println("Printing out decompiled class");
            className = className.replace('/', '.');
            ProcessBuilder processBuilder = new ProcessBuilder("javap", "-s", "-c", "-l", "-verbose",
                    "-p", className);
            processBuilder = processBuilder.redirectErrorStream(true);
            String fileName = className + ".javap";
            File file = new File(fileName);
            processBuilder = processBuilder.redirectOutput(file);
            Process process = processBuilder.start();
            process.waitFor();
            FileReader fr = new FileReader(fileName);
            try (BufferedReader br = new BufferedReader(fr)) {
                for(String line = br.readLine() ; line != null ; line = br.readLine()) {
                    System.out.println(String.format("%s: %s", className, line));
                }
            }
            file.delete();
        } catch (IOException | InterruptedException ie) {
            ie.printStackTrace();
        }
    }

//    public byte[] transform(Module module, ClassLoader loader, String className, Class<?> classBeingRedefined, ProtectionDomain protectionDomain, byte[] classfileBuffer)
//            throws IllegalClassFormatException {
//        System.out.println("Calling transform method with module for class: " + className);
//        try {
//            ClassFile classFile = ClassFile.load(className, classfileBuffer);
//        } catch (ClassFileException e) {
//            e.printStackTrace(System.out);
//        }
//        return null;
//    }

    @Override
    public String toString() {
        return "AgentClassFileTransformer(JDK 7)";
    }
}
