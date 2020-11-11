package org.valhalla.instrumentation.plogger.agent.bytecode.constantpool;

import org.valhalla.instrumentation.plogger.agent.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class ConstantInterfaceMethodRef extends AbstractConstantRef {
    public ConstantInterfaceMethodRef(int classIndex, int nameAndTypeIndex) {
        super(classIndex, nameAndTypeIndex);
    }

    @Override
    public void validate(ClassFile classFile) throws ConstantPoolEntryException {
        super.validate(classFile);
        // TODO: complete check
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(INTERFACE_METHOD);
        super.write(os);
    }
}
