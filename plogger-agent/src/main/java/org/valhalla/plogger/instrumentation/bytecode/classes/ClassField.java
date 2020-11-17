package org.valhalla.plogger.instrumentation.bytecode.classes;

import org.valhalla.plogger.instrumentation.bytecode.attributes.ClassAttribute;
import org.valhalla.plogger.instrumentation.bytecode.attributes.ClassAttributeException;
import org.valhalla.plogger.instrumentation.bytecode.attributes.ClassAttributeFactory;

import java.io.DataInputStream;
import java.io.IOException;
import java.util.Arrays;

public class ClassField {

    private final ClassFile classFile;
    private int accessFlags;
    private int nameIndex;
    private int descriptionIndex;
    private ClassAttribute[] attributes;

    private ClassField(ClassFile classFile) { this.classFile = classFile; }

    public static ClassField load(ClassFile classFile, DataInputStream dis) throws IOException, ClassAttributeException, ClassFileException {
        ClassField field = new ClassField(classFile);
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

    @Override
    public String toString() {
        return "ClassField{" +
                "accessFlags=" + accessFlags +
                ", nameIndex=" + nameIndex +
                ", descriptionIndex=" + descriptionIndex +
                ", attributes=" + Arrays.toString(attributes) +
                '}';
    }
}
