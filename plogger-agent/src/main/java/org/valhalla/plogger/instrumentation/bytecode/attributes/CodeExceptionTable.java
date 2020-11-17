package org.valhalla.plogger.instrumentation.bytecode.attributes;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class CodeExceptionTable {
    private final int startPc;
    private final int endPc;
    private final int handlerPc;
    private final int catchType;
    private final ClassFile classFile;
    private final CodeAttribute code;

    public CodeExceptionTable(ClassFile classFile, CodeAttribute code, int startPc, int endPc, int handlerPc, int catchType) {
        this.classFile = classFile;
        this.code = code;
        this.startPc = startPc;
        this.endPc = endPc;
        this.handlerPc = handlerPc;
        this.catchType = catchType;
    }

    @Override
    public String toString() {
        return "CodeExceptionTable{" +
                "startPc=" + startPc +
                ", endPc=" + endPc +
                ", handlerPc=" + handlerPc +
                ", catchType=" + catchType +
                '}';
    }

    public void write(DataOutput dos) throws IOException {
        dos.writeShort(startPc);
        dos.writeShort(endPc);
        dos.writeShort(handlerPc);
        dos.writeShort(catchType);
    }
}
