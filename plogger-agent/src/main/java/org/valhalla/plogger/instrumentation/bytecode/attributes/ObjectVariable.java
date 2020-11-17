package org.valhalla.plogger.instrumentation.bytecode.attributes;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class ObjectVariable implements VerificationType {
    private final int cpIndex;
    private final ClassFile classFile;

    public ObjectVariable(ClassFile classFile, int cpIndex) {
        this.classFile = classFile;
        this.cpIndex = cpIndex;
    }

    @Override
    public String toString() {
        return "ObjectVariable{" +
                "cpIndex=" + cpIndex +
                '}';
    }

    @Override
    public int tag() {
        return VerificationTypeTag.OBJECT;
    }

    @Override
    public int size() {
        return 1;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.write(VerificationTypeTag.OBJECT);
        os.writeShort(cpIndex);
    }
}
