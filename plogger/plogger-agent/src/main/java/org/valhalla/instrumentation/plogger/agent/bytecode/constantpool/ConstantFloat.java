package org.valhalla.instrumentation.plogger.agent.bytecode.constantpool;

import org.valhalla.instrumentation.plogger.agent.bytecode.classes.ClassFile;

import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.DataOutput;
import java.io.IOException;

public class ConstantFloat implements ConstantPoolEntry {
    private final byte[] bytes;

    public ConstantFloat(byte[] bytes) {
        this.bytes = bytes;
    }

    @Override
    public void validate(ClassFile classFile) throws ConstantPoolEntryException {
        try {
            new DataInputStream(new ByteArrayInputStream(bytes)).readFloat();
        } catch (Throwable t) {
            throw new ConstantPoolEntryException(t);
        }
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(FLOAT);
        os.write(bytes);
    }
}
