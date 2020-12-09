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

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileException;
import org.valhalla.plogger.instrumentation.bytecode.manager.ClassManager;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.lang.instrument.ClassFileTransformer;
import java.lang.instrument.IllegalClassFormatException;
import java.security.ProtectionDomain;

public class AgentClassFileTransformer implements ClassFileTransformer {
    public byte[] transform(ClassLoader loader, String className, Class<?> classBeingRedefined, ProtectionDomain protectionDomain, byte[] classfileBuffer) throws IllegalClassFormatException {
        if (! className.startsWith("org/valhalla/plogger/instrumentation") && ! className.startsWith("java/lang")) {
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
            }
        }
        return null;
    }

    public byte[] transform(Module module, ClassLoader loader, String className, Class<?> classBeingRedefined, ProtectionDomain protectionDomain, byte[] classfileBuffer) throws IllegalClassFormatException {
        System.out.println("Calling transform method for class: " + className);
        // TODO: We need to include the use of the Module parameter.
        if (! className.startsWith("org/valhalla/plogger/instrumentation") && ! className.startsWith("java/lang")) {
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
            }
        }
        return null;
    }

    @Override
    public String toString() {
        return "AgentClassFileTransformer(JDK 9)";
    }
}
