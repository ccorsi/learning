package org.valhalla.instrumentation.plogger.agent.bytecode.constantpool;

import org.valhalla.instrumentation.plogger.agent.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class ConstantClass implements ConstantPoolEntry {

    private int nameIndex;

    public ConstantClass(int nameIndex) throws ConstantPoolEntryException {
        if (nameIndex < 1) {
            throw new ConstantPoolEntryException("Invalid name index: " + nameIndex + " must be greater than 0");
        }
        this.nameIndex = nameIndex;
    }

    @Override
    public void validate(ClassFile classFile) throws ConstantPoolEntryException {
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
    public void write(DataOutput os) throws IOException {
        os.writeByte(CLASS);
        os.writeShort(nameIndex);
    }
}
