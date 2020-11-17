package org.valhalla.plogger.instrumentation.bytecode.constantpool;


import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class ConstantClass implements ConstantPoolEntry {

    private final ClassFile classFile;
    private int nameIndex;

    public ConstantClass(ClassFile classFile, int nameIndex) throws ConstantPoolEntryException {
        if (nameIndex < 1) {
            throw new ConstantPoolEntryException("Invalid name index: " + nameIndex + " must be greater than 0");
        }
        this.nameIndex = nameIndex;
        this.classFile = classFile;
    }

    @Override
    public void validate() throws ConstantPoolEntryException {
        ConstantPoolEntry[] cpool = classFile.getConstantPool();
        if (nameIndex >= cpool.length || nameIndex < 1) {
            throw new ConstantPoolEntryException("Name Index out of range: " + nameIndex + " should be between: [1,"
            + (cpool.length - 1) + "]");
        }
        if ( ! (cpool[nameIndex] instanceof ConstantUtf8) ) {
            throw new ConstantPoolEntryException("The name index " + nameIndex + " is not referencing a ConstantUtf8");
        }
    }

    @Override
    public int entries() {
        return 1;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(CLASS);
        os.writeShort(nameIndex);
    }

    @Override
    public String toString() {
        return "ConstantClass{" +
                "nameIndex=" + nameIndex +
                '}';
    }

    public String getClassName(ConstantPoolEntry[] cpools) {
        ConstantUtf8 utf8 = (ConstantUtf8) cpools[nameIndex];
        return utf8.getString();
    }
}
