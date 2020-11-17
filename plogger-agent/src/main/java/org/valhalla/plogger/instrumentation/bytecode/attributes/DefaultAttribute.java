package org.valhalla.plogger.instrumentation.bytecode.attributes;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;
import java.util.Arrays;

public class DefaultAttribute implements ClassAttribute {
    private final byte[] data;
    private final int nameIndex;
    private final ClassFile classFile;

    public DefaultAttribute(ClassFile classFile, int nameIndex, byte[] data) {
        this.classFile = classFile;
        this.nameIndex = nameIndex;
        this.data = data;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeShort(nameIndex);
        os.writeLong(data.length);
        os.write(data);
    }

    @Override
    public String toString() {
        return "DefaultAttribute{" +
                "data=" + Arrays.toString(data) +
                ", nameIndex=" + nameIndex +
                '}';
    }
}
