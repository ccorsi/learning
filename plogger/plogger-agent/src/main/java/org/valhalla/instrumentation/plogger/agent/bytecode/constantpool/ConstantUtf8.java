package org.valhalla.instrumentation.plogger.agent.bytecode.constantpool;

import org.valhalla.instrumentation.plogger.agent.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class ConstantUtf8 implements ConstantPoolEntry {
    private final int length;
    private final byte[] bytes;

    public ConstantUtf8(int length, byte[] bytes) {
        this.length = length;
        this.bytes = bytes;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(UTF8);
        os.write(bytes);
    }

    @Override
    public void validate(ClassFile classFile) throws ConstantPoolEntryException {
        try {
            new String(bytes);
        } catch (Throwable t) {
            throw new ConstantPoolEntryException(t);
        }
    }

    public String getString() {
        return new String(bytes);
    }
}
