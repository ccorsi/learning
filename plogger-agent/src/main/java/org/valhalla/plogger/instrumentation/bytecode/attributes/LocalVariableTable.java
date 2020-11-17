package org.valhalla.plogger.instrumentation.bytecode.attributes;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.ByteArrayOutputStream;
import java.io.DataOutput;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.Arrays;

public class LocalVariableTable implements ClassAttribute {
    private final int nameIndex;
    private final LocalVariableTableEntry[] entries;
    private final ClassFile classFile;
    private final CodeAttribute code;

    public LocalVariableTable(ClassFile classFile, CodeAttribute code, int nameIndex, LocalVariableTableEntry[] entries) {
        this.classFile = classFile;
        this.code = code;
        this.nameIndex = nameIndex;
        this.entries = entries;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        DataOutputStream dos = new DataOutputStream(bos);
        // TODO: properly manage the IOException
        for (LocalVariableTableEntry entry : entries) {
            entry.write(dos);
        }
        dos.close();
        byte[] data = bos.toByteArray();

        os.writeShort(nameIndex);
        os.writeInt(data.length);
        os.write(data);
    }

    @Override
    public String toString() {
        return "LocalVariableTable{" +
                "nameIndex=" + nameIndex +
                ", entries=" + Arrays.toString(entries) +
                '}';
    }
}
