package org.valhalla.plogger.instrumentation.bytecode.constantpool;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.DataOutput;
import java.io.IOException;
import java.util.Arrays;

public class ConstantLong implements ConstantPoolEntry {
    private final byte[] highBytes;
    private final byte[] lowBytes;

    public ConstantLong(byte[] highBytes, byte[] lowBytes) {
        this.highBytes = highBytes;
        this.lowBytes = lowBytes;
    }

    @Override
    public void validate() throws ConstantPoolEntryException {
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
    public String toString() {
        return "ConstantLong{" +
                "highBytes=" + Arrays.toString(highBytes) +
                ", lowBytes=" + Arrays.toString(lowBytes) +
                '}';
    }

    @Override
    public int entries() {
        return 2;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(LONG);
        os.write(highBytes);
        os.write(lowBytes);
    }
}
