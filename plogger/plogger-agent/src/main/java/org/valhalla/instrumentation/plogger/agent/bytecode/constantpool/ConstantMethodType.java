package org.valhalla.instrumentation.plogger.agent.bytecode.constantpool;

import org.valhalla.instrumentation.plogger.agent.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class ConstantMethodType implements ConstantPoolEntry {
    private final int descriptorIndex;

    public ConstantMethodType(int descriptorIndex) {
        this.descriptorIndex = descriptorIndex;
    }

    @Override
    public void validate(ClassFile classFile) throws ConstantPoolEntryException {
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
    public void write(DataOutput os) throws IOException {
        os.writeByte(METHOD_TYPE);
        os.writeShort(descriptorIndex);
    }
}
