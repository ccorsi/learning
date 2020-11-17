package org.valhalla.plogger.instrumentation.bytecode.constantpool;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

public class ConstantFieldRef extends AbstractConstantRef {

    public ConstantFieldRef(ClassFile classFile, int classIndex, int nameAndTypeIndex) {
        super(classFile, classIndex, nameAndTypeIndex);
    }

    @Override
    public void validate() throws ConstantPoolEntryException {
        super.validate();
        ConstantPoolEntry[] cpool = classFile.getConstantPool();
        if (classIndex >= cpool.length) {
            throw new ConstantPoolEntryException("Out of range class index: " + classIndex);
        }
        if (nameAndTypeIndex >= cpool.length) {
            throw new ConstantPoolEntryException("Out of range name and type index: " + nameAndTypeIndex);
        }
    }

    @Override
    public String toString() {
        return "ConstantFieldRef{" +
                "classIndex=" + classIndex +
                ", nameAndTypeIndex=" + nameAndTypeIndex +
                '}';
    }
}
