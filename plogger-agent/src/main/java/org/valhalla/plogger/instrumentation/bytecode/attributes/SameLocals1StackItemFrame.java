package org.valhalla.plogger.instrumentation.bytecode.attributes;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class SameLocals1StackItemFrame extends AbstractStackMapFrame {
    private final VerificationType verificationType;

    public SameLocals1StackItemFrame(ClassFile classFile, CodeAttribute code, int frameType, VerificationType verificationType) {
        super(classFile, code, frameType);
        this.verificationType = verificationType;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        super.write(os);
        verificationType.write(os);
    }

    @Override
    public String toString() {
        return "SameLocals1StackItemFrame{" +
                "verificationType=" + verificationType +
                ", frameType=" + frameType +
                '}';
    }
}
