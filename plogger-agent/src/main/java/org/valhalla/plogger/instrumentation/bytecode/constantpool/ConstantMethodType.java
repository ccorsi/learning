package org.valhalla.plogger.instrumentation.bytecode.constantpool;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class ConstantMethodType implements ConstantPoolEntry {
    private final int descriptorIndex;
    private final ClassFile classFile;

    public ConstantMethodType(ClassFile classFile, int descriptorIndex) {
        this.classFile = classFile;
        this.descriptorIndex = descriptorIndex;
    }

    @Override
    public void validate() throws ConstantPoolEntryException {
        ConstantPoolEntry[] cpool = classFile.getConstantPool();
        if ( descriptorIndex < 1 || descriptorIndex >= cpool.length) {
            throw new ConstantPoolEntryException("Invalid descriptor index: " + descriptorIndex
                    + " it is supposed to be between [0," + cpool.length + "].");
        }
        if (! (cpool[descriptorIndex] instanceof ConstantUtf8)) {
            throw new ConstantPoolEntryException("The descriptor index is not a Constant Utf8 entry.");
        }
    }

    @Override
    public int entries() {
        return 1;
    }

    @Override
    public String toString() {
        return "ConstantMethodType{" +
                "descriptorIndex=" + descriptorIndex +
                '}';
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(METHOD_TYPE);
        os.writeShort(descriptorIndex);
    }
}
