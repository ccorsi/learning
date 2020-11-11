package org.valhalla.instrumentation.plogger.agent.bytecode.constantpool;

import org.valhalla.instrumentation.plogger.agent.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class ConstantPackage implements ConstantPoolEntry {
    private final int nameIndex;

    public ConstantPackage(int nameIndex) {
        this.nameIndex = nameIndex;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(PACKAGE);
        os.writeShort(nameIndex);
    }

    @Override
    public void validate(ClassFile classFile) throws ConstantPoolEntryException {
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
