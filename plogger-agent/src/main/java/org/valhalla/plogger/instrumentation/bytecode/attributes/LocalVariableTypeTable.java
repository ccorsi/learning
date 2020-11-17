package org.valhalla.plogger.instrumentation.bytecode.attributes;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.ByteArrayOutputStream;
import java.io.DataOutput;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.Arrays;

public class LocalVariableTypeTable implements ClassAttribute {
    private final int nameIndex;
    private final LocalVariableTypeTableEntry[] types;
    private final ClassFile classFile;
    private final CodeAttribute code;

    public LocalVariableTypeTable(ClassFile classFile, CodeAttribute code, int nameIndex, LocalVariableTypeTableEntry[] types) {
        this.classFile = classFile;
        this.code = code;
        this.nameIndex = nameIndex;
        this.types = types;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        DataOutputStream dos = new DataOutputStream(bos);

    }

    @Override
    public String toString() {
        return "LocalVariableTypeTable{" +
                "nameIndex=" + nameIndex +
                ", types=" + Arrays.toString(types) +
                '}';
    }
}
