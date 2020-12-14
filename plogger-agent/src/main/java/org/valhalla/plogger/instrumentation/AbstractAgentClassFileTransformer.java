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

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.FileOutputStream;
import java.lang.instrument.ClassFileTransformer;
import java.security.ProtectionDomain;

public abstract class AbstractAgentClassFileTransformer implements ClassFileTransformer {

    public byte[] transform(ClassLoader loader, String className, Class<?> classBeingRedefined,
                            ProtectionDomain protectionDomain, byte[] classfileBuffer) {
        byte[] classBytes = instrumentClass(className, classfileBuffer);
        if (classBytes != null) {
            return classBytes;
        }
        return null;
    }

    protected final byte[] instrumentClass(String className, byte[] classfileBuffer) {
        // TODO: Add an option check
        if (! className.startsWith("org/valhalla/plogger/instrumentation")) {
            try {
                ClassManager classManager = new ClassManager(className, classfileBuffer);
                if (classManager.instrument()) {
                    ByteArrayOutputStream bos = new ByteArrayOutputStream();
                    try (DataOutputStream dos = new DataOutputStream(bos)) {
                        classManager.write(dos);
                    }
                    byte[] classBytes = bos.toByteArray();
                    // TODO: Add an option check
                    if (className.equals("org/valhalla/plogger/test/Main") ||
                            className.equals("java/lang/String") || className.equals("sun/launcher/LauncherHelper")
                            || className.equals("java/text/SimpleDateFormat")
                            || className.startsWith("java/util/concurrent/LinkedBlockingQueue"))
                    {
                        String fileName = String.format("%s.class", className.replace('/','.'));
                        try (FileOutputStream fos = new FileOutputStream(fileName)) {
                            fos.write(classBytes);
                        } catch (Throwable t) {
                            // do nothing since it is possible that we don't have any rights here
                        }
                    }
                    return classBytes;
                }
            } catch (Throwable e) {
                System.out.println("An exception was thrown when transforming class: " + className);
                e.printStackTrace(System.out);
            }
        }
        return null;
    }

}
