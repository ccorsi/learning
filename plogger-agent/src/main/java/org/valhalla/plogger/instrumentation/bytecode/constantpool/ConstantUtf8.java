package org.valhalla.plogger.instrumentation.bytecode.constantpool;

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
    public int entries() {
        return 1;
    }

    @Override
    public String toString() {
        return "ConstantUtf8{" +
                "length=" + length +
                // ", bytes=" + Arrays.toString(bytes) +
                ", string=" + new String(bytes) +
                '}';
    }

    @Override
    public void validate() throws ConstantPoolEntryException {
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
