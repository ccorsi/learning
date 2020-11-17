package org.valhalla.plogger.instrumentation.bytecode.constantpool;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class ConstantString implements ConstantPoolEntry {
    private final int stringIndex;
    private final ClassFile classFile;

    public ConstantString(ClassFile classFile, int stringIndex) {
        this.classFile = classFile;
        this.stringIndex = stringIndex;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(STRING);
        os.writeShort(stringIndex);
    }

    @Override
    public int entries() {
        return 1;
    }

    @Override
    public String toString() {
        return "ConstantString{" +
                "stringIndex=" + stringIndex +
                '}';
    }

    @Override
    public void validate() throws ConstantPoolEntryException {
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
