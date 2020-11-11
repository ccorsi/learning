package org.valhalla.instrumentation.plogger.agent.bytecode.classes;

import org.valhalla.instrumentation.plogger.agent.bytecode.attributes.ClassAttribute;
import org.valhalla.instrumentation.plogger.agent.bytecode.attributes.ClassAttributeFactory;

import java.io.DataInputStream;
import java.io.IOException;

public class ClassMethod {
    private int accessFlags;
    private int nameIndex;
    private int descriptorIndex;
    private ClassAttribute[] attributes;

    private ClassMethod() {}

    public static ClassMethod load(ClassFile classFile, DataInputStream dis) throws IOException {
        ClassMethod method =  new ClassMethod();
        method.accessFlags = dis.readUnsignedShort();
        method.nameIndex = dis.readUnsignedShort();
        method.descriptorIndex = dis.readUnsignedShort();
        int count = dis.readUnsignedShort();
        method.attributes = new ClassAttribute[count];
        for (int idx = 0 ; idx < count ; idx++) {
            method.attributes[idx] = ClassAttributeFactory.load(classFile, dis);
        }
        return method;
    }
}
