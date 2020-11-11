package org.valhalla.instrumentation.plogger.agent.bytecode.attributes;

import org.valhalla.instrumentation.plogger.agent.bytecode.classes.ClassFile;
import org.valhalla.instrumentation.plogger.agent.bytecode.constantpool.ConstantPoolEntry;
import org.valhalla.instrumentation.plogger.agent.bytecode.constantpool.ConstantUtf8;

import java.io.DataInputStream;
import java.io.IOException;

public class ClassAttributeFactory {
    public static ClassAttribute load(ClassFile classFile, DataInputStream dis) throws IOException {
        // Extract the attribute index into the constant pool
        int nameIndex = dis.readUnsignedShort();
        // validate that the referencing attribute index is a ConstantUtf8 constant pool entry
        ConstantPoolEntry cp = classFile.getConstantPool()[nameIndex];
        // this will through a ClassCastException if it can't sub class the instance to ConstantUtf8
        ConstantUtf8 utf8 = ConstantUtf8.class.cast(cp);
        String name = utf8.getString();
        ClassAttribute attribute = null;
        switch(name) {
            default:
                int length = dis.readInt();
                byte[] data = new byte[length];
                int copiedCount = dis.read(data);
                if (copiedCount != length) {
                    // TODO: raise an exception
                }
                attribute = new DefaultAttribute(nameIndex, data);
        }
        return attribute;
    }
}
