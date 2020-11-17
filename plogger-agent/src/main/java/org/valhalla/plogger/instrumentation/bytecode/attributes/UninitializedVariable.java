package org.valhalla.plogger.instrumentation.bytecode.attributes;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class UninitializedVariable implements VerificationType {
    private final int offset;
    private final ClassFile classFile;

    public UninitializedVariable(ClassFile classFile, int offset) {
        this.classFile = classFile;
        this.offset = offset;
    }

    @Override
    public int tag() {
        return VerificationTypeTag.UNINITIALIZED;
    }

    @Override
    public int size() {
        return 1;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.write(VerificationTypeTag.UNINITIALIZED);
        os.writeShort(offset);
    }

    @Override
    public String toString() {
        return "UninitializedVariable{" +
                "offset=" + offset +
                '}';
    }
}
