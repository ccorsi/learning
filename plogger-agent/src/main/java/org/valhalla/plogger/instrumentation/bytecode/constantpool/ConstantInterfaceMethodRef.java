package org.valhalla.plogger.instrumentation.bytecode.constantpool;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class ConstantInterfaceMethodRef extends AbstractConstantRef {
    public ConstantInterfaceMethodRef(ClassFile classFile, int classIndex, int nameAndTypeIndex) {
        super(classFile, classIndex, nameAndTypeIndex);
    }

    @Override
    public void validate() throws ConstantPoolEntryException {
        super.validate();
        // TODO: complete check
    }

    @Override
    public String toString() {
        return "ConstantInterfaceMethodRef{" +
                "classIndex=" + classIndex +
                ", nameAndTypeIndex=" + nameAndTypeIndex +
                '}';
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(INTERFACE_METHOD);
        super.write(os);
    }
}
