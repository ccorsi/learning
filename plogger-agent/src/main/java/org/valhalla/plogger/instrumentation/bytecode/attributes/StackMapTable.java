package org.valhalla.plogger.instrumentation.bytecode.attributes;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.ByteArrayOutputStream;
import java.io.DataOutput;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.Arrays;

public class StackMapTable implements ClassAttribute {
    private final int nameIndex;
    private final StackMapFrame[] entries;
    private final ClassFile classFile;

    public StackMapTable(ClassFile classFile, int nameIndex, StackMapFrame[] entries) {
        this.classFile = classFile;
        this.nameIndex = nameIndex;
        this.entries = entries;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        DataOutputStream dos = new DataOutputStream(bos);

        try {
            for (StackMapFrame frame : entries) {
                frame.write(dos);
            }
        } finally {
            dos.close();
        }

        byte[] bytes = bos.toByteArray();
        os.writeShort(nameIndex);
        os.writeInt(bytes.length);
        os.write(bytes);
    }

    @Override
    public String toString() {
        return "StackMapTable{" +
                "nameIndex=" + nameIndex +
                ", entries=" + Arrays.toString(entries) +
                '}';
    }
}
