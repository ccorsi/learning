package org.valhalla.plogger.instrumentation.bytecode.constantpool;


import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public abstract class AbstractConstantRef implements ConstantPoolEntry {
    protected final int classIndex;
    protected final int nameAndTypeIndex;
    protected final ClassFile classFile;

    protected AbstractConstantRef(ClassFile classFile, int classIndex, int nameAndTypeIndex) {
        this.classFile = classFile;
        this.classIndex = classIndex;
        this.nameAndTypeIndex = nameAndTypeIndex;
    }

    @Override
    public void validate() throws ConstantPoolEntryException {
        ConstantPoolEntry[] cpool = classFile.getConstantPool();
        if (classIndex < 1 || classIndex >= cpool.length) {
            throw new ConstantPoolEntryException("Invalid class index range, has to be between [0," + (cpool.length - 1)
                    + "].");
        }
        if ( !(cpool[classIndex] instanceof ConstantClass) ) {
            throw new ConstantPoolEntryException("Referencing Invalid Constant Pool Entry at index: " + classIndex
                    + " should be a Constant Class Entry.");
        }
        if (nameAndTypeIndex < 1 || nameAndTypeIndex >= cpool.length) {
            throw new ConstantPoolEntryException("Invalid name and type index range, has to be between [0.,"
                    + (cpool.length - 1) + "].");
        }
        if ( !(cpool[nameAndTypeIndex] instanceof ConstantNameAndType) ) {
            throw new ConstantPoolEntryException("Referencing Invalid Constant Pool Entry at index: " + nameAndTypeIndex
                    + " should be a Constant Name And Type Entry.");
        }
    }

    @Override
    public int entries() {
        return 1;
    }

    public ConstantClass getClass(ConstantPoolEntry[] cpool) {
        return (ConstantClass) cpool[classIndex];
    }

    public ConstantNameAndType getNameAndType(ConstantPoolEntry[] cpool) {
        return (ConstantNameAndType) cpool[nameAndTypeIndex];
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeShort(classIndex);
        os.writeShort(nameAndTypeIndex);
    }
}
