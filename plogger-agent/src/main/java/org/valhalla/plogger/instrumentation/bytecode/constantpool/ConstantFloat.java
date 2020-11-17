package org.valhalla.plogger.instrumentation.bytecode.constantpool;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.DataOutput;
import java.io.IOException;
import java.util.Arrays;

public class ConstantFloat implements ConstantPoolEntry {
    private final byte[] bytes;

    public ConstantFloat(byte[] bytes) {
        this.bytes = bytes;
    }

    @Override
    public void validate() throws ConstantPoolEntryException {
        try {
            new DataInputStream(new ByteArrayInputStream(bytes)).readFloat();
        } catch (Throwable t) {
            throw new ConstantPoolEntryException(t);
        }
    }

    @Override
    public int entries() {
        return 1;
    }

    @Override
    public String toString() {
        return "ConstantFloat{" +
                "bytes=" + Arrays.toString(bytes) +
                '}';
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(FLOAT);
        os.write(bytes);
    }
}
