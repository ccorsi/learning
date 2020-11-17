package org.valhalla.plogger.instrumentation.bytecode.attributes;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileWriter;

import java.io.DataOutput;
import java.io.IOException;

public class LocalVariableTableEntry implements ClassFileWriter {
    private final int startPc;
    private final int length;
    private final int nameIndex;
    private final int descriptorIndex;
    private final int index;
    private final ClassFile classFile;
    private final CodeAttribute code;

    public LocalVariableTableEntry(ClassFile classFile, CodeAttribute code, int startPc, int length, int nameIndex, int descriptorIndex, int index) {
        this.classFile = classFile;
        this.code = code;
        this.startPc = startPc;
        this.length = length;
        this.nameIndex = nameIndex;
        this.descriptorIndex = descriptorIndex;
        this.index = index;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeShort(startPc);
        os.writeShort(length);
        os.writeShort(nameIndex);
        os.writeShort(descriptorIndex);
        os.writeShort(index);
    }

    @Override
    public String toString() {
        return "LocalVariableTableEntry{" +
                "startPc=" + startPc +
                ", length=" + length +
                ", nameIndex=" + nameIndex +
                ", descriptorIndex=" + descriptorIndex +
                ", index=" + index +
                '}';
    }
}
