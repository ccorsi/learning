package org.valhalla.instrumentation.plogger.agent.bytecode.classes;

import org.valhalla.instrumentation.plogger.agent.bytecode.attributes.ClassAttribute;
import org.valhalla.instrumentation.plogger.agent.bytecode.attributes.ClassAttributeFactory;

import java.io.DataInputStream;
import java.io.IOException;

public class ClassField {

    private int accessFlags;
    private int nameIndex;
    private int descriptionIndex;
    private ClassAttribute[] attributes;

    private ClassField() {}

    public static ClassField load(ClassFile classFile, DataInputStream dis) throws IOException {
        ClassField field = new ClassField();
        field.accessFlags = dis.readUnsignedShort();
        field.nameIndex = dis.readUnsignedShort();
        field.descriptionIndex = dis.readUnsignedShort();
        int count = dis.readUnsignedShort();
        field.attributes = new ClassAttribute[count];
        for(int idx = 0 ;  idx < count ; idx++) {
            field.attributes[idx] = ClassAttributeFactory.load(classFile, dis);
        }
        return field;
    }
}
