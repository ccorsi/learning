package org.valhalla.plogger.instrumentation.bytecode.attributes;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class ChopFrame extends AbstractStackMapFrame {
    private final int offset;

    public ChopFrame(ClassFile classFile, CodeAttribute code, int frameType, int offset) {
        super(classFile, code, frameType);
        this.offset = offset;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        super.write(os);
        os.writeShort(offset);
    }

    @Override
    public String toString() {
        return "ChopFrame{" +
                "offset=" + offset +
                ", frameType=" + frameType +
                '}';
    }
}
