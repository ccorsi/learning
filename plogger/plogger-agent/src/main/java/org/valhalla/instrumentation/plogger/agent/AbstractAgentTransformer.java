package org.valhalla.instrumentation.plogger.agent;

import org.valhalla.instrumentation.plogger.agent.bytecode.classes.ClassFile;

import java.lang.instrument.ClassFileTransformer;
import java.lang.instrument.IllegalClassFormatException;
import java.security.ProtectionDomain;

public abstract class AbstractAgentTransformer implements ClassFileTransformer {
    @Override
    public byte[] transform(ClassLoader loader, String className, Class<?> classBeingRedefined,
                            ProtectionDomain protectionDomain, byte[] classfileBuffer)
            throws IllegalClassFormatException {
        System.out.println("Loading class name: " + className);
        try {
            ClassFile.load(className, classfileBuffer);
        } catch(Throwable t) {
            System.out.println("An exception was raised when loading class: " + className);
            t.printStackTrace(System.out);
        }
        return null;
    }

    @Override
    public byte[] transform(Module module, ClassLoader loader, String className, Class<?> classBeingRedefined,
                            ProtectionDomain protectionDomain, byte[] classfileBuffer)
            throws IllegalClassFormatException {
        System.out.println("Loading class name: " + className + " for module: " + module.getName());
        try {
            ClassFile.load(className, classfileBuffer);
        } catch(Throwable t) {
            System.out.println("An exception was raised when loading class: " + className);
            t.printStackTrace(System.out);
        }
        return null;
    }
}
