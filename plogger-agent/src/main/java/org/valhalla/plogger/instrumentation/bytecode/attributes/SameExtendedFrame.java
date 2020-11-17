package org.valhalla.plogger.instrumentation.bytecode.attributes;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

public class SameExtendedFrame extends AbstractStackMapFrame {
    private final int offset;

    @Override
    public String toString() {
        return "SameExtendedFrame{" +
                "offset=" + offset +
                ", frameType=" + frameType +
                '}';
    }

    public SameExtendedFrame(ClassFile classFile, CodeAttribute code, int frameType, int offset) {
        super(classFile, code, frameType);
        this.offset = offset;
    }
}
