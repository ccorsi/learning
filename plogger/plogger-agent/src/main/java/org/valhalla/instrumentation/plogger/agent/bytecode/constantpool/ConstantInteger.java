package org.valhalla.instrumentation.plogger.agent.bytecode.constantpool;

import org.valhalla.instrumentation.plogger.agent.bytecode.classes.ClassFile;

import java.io.*;

public class ConstantInteger implements ConstantPoolEntry {
    private final byte[] bytes;

    public ConstantInteger(byte[] bytes) {
        this.bytes = bytes;
    }

    @Override
    public void validate(ClassFile classFile) throws ConstantPoolEntryException {
        try {
            new DataInputStream(new ByteArrayInputStream(bytes)).readInt();
        } catch (Throwable t) {
            throw new ConstantPoolEntryException(t);
        }
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(INTEGER);
        os.write(bytes);
    }
}
