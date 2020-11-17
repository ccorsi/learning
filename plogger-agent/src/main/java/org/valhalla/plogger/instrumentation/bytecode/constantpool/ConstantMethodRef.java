package org.valhalla.plogger.instrumentation.bytecode.constantpool;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class ConstantMethodRef extends AbstractConstantRef {
    public ConstantMethodRef(ClassFile classFile, int classIndex, int nameAndTypeIndex) {
        super(classFile, classIndex, nameAndTypeIndex);
    }

    @Override
    public String toString() {
        return "ConstantMethodRef{" +
                "classIndex=" + classIndex +
                ", nameAndTypeIndex=" + nameAndTypeIndex +
                '}';
    }

    @Override
    public void validate() throws ConstantPoolEntryException {
        super.validate();
        // TODO: complete checks.
        ConstantPoolEntry[] cpool = classFile.getConstantPool();
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(METHOD);
        super.write(os);
    }
}
