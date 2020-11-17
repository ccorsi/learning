package org.valhalla.plogger.instrumentation.bytecode.attributes;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public abstract class AbstractStackMapFrame implements StackMapFrame {
    protected final int frameType;
    protected final ClassFile classFile;
    protected final CodeAttribute code;

    public AbstractStackMapFrame(ClassFile classFile, CodeAttribute code, int frameType) {
        this.classFile = classFile;
        this.code = code;
        this.frameType = frameType;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.write(frameType);
    }
}
