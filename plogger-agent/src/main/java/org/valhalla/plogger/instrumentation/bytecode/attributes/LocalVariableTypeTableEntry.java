package org.valhalla.plogger.instrumentation.bytecode.attributes;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileWriter;

import java.io.DataOutput;
import java.io.IOException;

public class LocalVariableTypeTableEntry implements ClassFileWriter {
    private final int startPc;
    private final int length;
    private final int nameIndex;
    private final int signatureIndex;
    private final int index;
    private final ClassFile classFile;
    private final CodeAttribute code;

    @Override
    public String toString() {
        return "LocalVariableTypeTableEntry{" +
                "startPc=" + startPc +
                ", length=" + length +
                ", nameIndex=" + nameIndex +
                ", signatureIndex=" + signatureIndex +
                ", index=" + index +
                '}';
    }

    public LocalVariableTypeTableEntry(ClassFile classFile, CodeAttribute code, int startPc, int length, int nameIndex, int signatureIndex, int index) {
        this.classFile = classFile;
        this.code = code;
        this.startPc = startPc;
        this.length = length;
        this.nameIndex = nameIndex;
        this.signatureIndex = signatureIndex;
        this.index = index;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeShort(startPc);
        os.writeShort(length);
        os.writeShort(nameIndex);
        os.writeShort(signatureIndex);
        os.writeShort(index);
    }
}
