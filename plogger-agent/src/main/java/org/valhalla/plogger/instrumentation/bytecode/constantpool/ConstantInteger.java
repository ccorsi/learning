package org.valhalla.plogger.instrumentation.bytecode.constantpool;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.*;
import java.util.Arrays;

public class ConstantInteger implements ConstantPoolEntry {
    private final byte[] bytes;

    public ConstantInteger(byte[] bytes) {
        this.bytes = bytes;
    }

    @Override
    public void validate() throws ConstantPoolEntryException {
        try {
            new DataInputStream(new ByteArrayInputStream(bytes)).readInt();
        } catch (Throwable t) {
            throw new ConstantPoolEntryException(t);
        }
    }

    @Override
    public String toString() {
        return "ConstantInteger{" +
                "bytes=" + Arrays.toString(bytes) +
                '}';
    }

    @Override
    public int entries() {
        return 1;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(INTEGER);
        os.write(bytes);
    }
}
