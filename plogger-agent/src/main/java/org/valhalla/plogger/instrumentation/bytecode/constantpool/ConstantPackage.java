package org.valhalla.plogger.instrumentation.bytecode.constantpool;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class ConstantPackage implements ConstantPoolEntry {
    private final int nameIndex;
    private final ClassFile classFile;

    public ConstantPackage(ClassFile classFile, int nameIndex) {
        this.classFile = classFile;
        this.nameIndex = nameIndex;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(PACKAGE);
        os.writeShort(nameIndex);
    }

    @Override
    public int entries() {
        return 1;
    }

    @Override
    public String toString() {
        return "ConstantPackage{" +
                "nameIndex=" + nameIndex +
                '}';
    }

    @Override
    public void validate() throws ConstantPoolEntryException {
        ConstantPoolEntry[] cpool = classFile.getConstantPool();
        if (nameIndex < 1 || nameIndex >= cpool.length) {
            throw new ConstantPoolEntryException("Invalid name index: " + nameIndex + " should be between [0,"
                    + cpool.length + "].");
        }
        if ( ! (cpool[nameIndex] instanceof  ConstantUtf8) ) {
            throw new ConstantPoolEntryException("Invalid name index reference it is supposed to be referencing a constant utf8 entry.");
        }
    }
}
