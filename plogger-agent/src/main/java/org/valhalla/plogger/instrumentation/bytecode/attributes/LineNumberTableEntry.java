package org.valhalla.plogger.instrumentation.bytecode.attributes;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileWriter;

import java.io.DataOutput;
import java.io.IOException;

public class LineNumberTableEntry implements ClassFileWriter {
    private final int startPc;
    private final int lineNumber;
    private final CodeAttribute code;
    private final ClassFile classFile;

    public LineNumberTableEntry(ClassFile classFile, CodeAttribute code, int startPc, int lineNumber) {
        this.classFile = classFile;
        this.code = code;
        this.startPc = startPc;
        this.lineNumber = lineNumber;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeShort(startPc);
        os.writeShort(lineNumber);
    }

    @Override
    public String toString() {
        return "LineNumberTableEntry{" +
                "startPc=" + startPc +
                ", lineNumber=" + lineNumber +
                '}';
    }
}
