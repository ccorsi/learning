package org.valhalla.instrumentation.plogger.agent.bytecode.constantpool;

import org.valhalla.instrumentation.plogger.agent.bytecode.classes.ClassFile;

import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.DataOutput;
import java.io.IOException;

public class ConstantLong implements ConstantPoolEntry {
    private final byte[] highBytes;
    private final byte[] lowBytes;

    public ConstantLong(byte[] highBytes, byte[] lowBytes) {
        this.highBytes = highBytes;
        this.lowBytes = lowBytes;
    }

    @Override
    public void validate(ClassFile classFile) throws ConstantPoolEntryException {
        try {
            byte bytes[] = new byte[highBytes.length + lowBytes.length];
            System.arraycopy(highBytes,0, bytes, 0, highBytes.length);
            System.arraycopy(lowBytes, 0, bytes, highBytes.length, lowBytes.length);
            new DataInputStream(new ByteArrayInputStream(bytes)).readLong();
        } catch (Throwable t) {
            throw new ConstantPoolEntryException(t);
        }
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(LONG);
        os.write(highBytes);
        os.write(lowBytes);
    }
}
