package org.valhalla.instrumentation.plogger.agent.bytecode.constantpool;

import org.valhalla.instrumentation.plogger.agent.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class ConstantString implements ConstantPoolEntry {
    private final int stringIndex;

    public ConstantString(int stringIndex) {
        this.stringIndex = stringIndex;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(STRING);
        os.writeShort(stringIndex);
    }

    @Override
    public void validate(ClassFile classFile) throws ConstantPoolEntryException {
        ConstantPoolEntry[] cpool = classFile.getConstantPool();
        if (stringIndex < 1 || stringIndex >= cpool.length) {
            throw new ConstantPoolEntryException("Invalid String Index range: " + stringIndex + " should be between [0,"
                    + (cpool.length - 1) + "].");
        }
        if ( ! (cpool[stringIndex] instanceof ConstantUtf8) ) {
            throw new ConstantPoolEntryException("Invalid string index reference, not referencing a constant utf8 entry.");
        }
    }
}
