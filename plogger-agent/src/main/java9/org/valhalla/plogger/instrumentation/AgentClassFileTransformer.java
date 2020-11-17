package org.valhalla.plogger.instrumentation;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileException;

import java.lang.instrument.ClassFileTransformer;
import java.lang.instrument.IllegalClassFormatException;
import java.security.ProtectionDomain;

public class AgentClassFileTransformer implements ClassFileTransformer {
    public byte[] transform(ClassLoader loader, String className, Class<?> classBeingRedefined, ProtectionDomain protectionDomain, byte[] classfileBuffer) throws IllegalClassFormatException {
        System.out.println("Calling transform method for class: " + className);
        try {
            ClassFile classFile = ClassFile.load(className, classfileBuffer);
        } catch (ClassFileException e) {
            e.printStackTrace(System.out);
        }
        return null;
    }

    public byte[] transform(Module module, ClassLoader loader, String className, Class<?> classBeingRedefined, ProtectionDomain protectionDomain, byte[] classfileBuffer) throws IllegalClassFormatException {
        System.out.println("Calling transform method with module for class: " + className);
        try {
            ClassFile classFile = ClassFile.load(className, classfileBuffer);
        } catch (ClassFileException e) {
            e.printStackTrace(System.out);
        }
        return null;
    }

    @Override
    public String toString() {
        return "AgentClassFileTransformer(JDK 9)";
    }
}
