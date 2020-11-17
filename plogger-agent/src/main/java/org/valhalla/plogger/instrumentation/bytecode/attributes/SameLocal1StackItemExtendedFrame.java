package org.valhalla.plogger.instrumentation.bytecode.attributes;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class SameLocal1StackItemExtendedFrame extends AbstractStackMapFrame {
    private final int offset;
    private final VerificationType verificationType;

    public SameLocal1StackItemExtendedFrame(ClassFile classFile, CodeAttribute code, int frameType, int offset, VerificationType verificationType) {
        super(classFile, code, frameType);
        this.offset = offset;
        this.verificationType = verificationType;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        super.write(os);
        os.writeShort(offset);
        verificationType.write(os);
    }

    @Override
    public String toString() {
        return "SameLocal1StackItemExtendedFrame{" +
                "offset=" + offset +
                ", verificationType=" + verificationType +
                ", frameType=" + frameType +
                '}';
    }
}
