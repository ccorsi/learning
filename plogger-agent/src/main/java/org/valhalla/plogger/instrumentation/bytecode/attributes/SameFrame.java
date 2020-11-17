package org.valhalla.plogger.instrumentation.bytecode.attributes;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class SameFrame extends AbstractStackMapFrame {
    public SameFrame(ClassFile classFile, CodeAttribute code, int frameType) {
        super(classFile, code, frameType);
    }

    @Override
    public void write(DataOutput os) throws IOException {
        super.write(os);
    }

    @Override
    public String toString() {
        return "SameFrame{" +
                "frameType=" + frameType +
                '}';
    }
}
