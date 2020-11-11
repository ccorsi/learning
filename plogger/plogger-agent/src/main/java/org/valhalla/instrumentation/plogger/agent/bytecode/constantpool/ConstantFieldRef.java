package org.valhalla.instrumentation.plogger.agent.bytecode.constantpool;

import org.valhalla.instrumentation.plogger.agent.bytecode.classes.ClassFile;

public class ConstantFieldRef extends AbstractConstantRef {

    public ConstantFieldRef(int classIndex, int nameAndTypeIndex) {
        super(classIndex, nameAndTypeIndex);
    }

    @Override
    public void validate(ClassFile classFile) throws ConstantPoolEntryException {
        super.validate(classFile);
        ConstantPoolEntry[] cpool = classFile.getConstantPool();
        if (classIndex >= cpool.length) {
            throw new ConstantPoolEntryException("Out of range class index: " + classIndex);
        }
        if (nameAndTypeIndex >= cpool.length) {
            throw new ConstantPoolEntryException("Out of range name and type index: " + nameAndTypeIndex);
        }
    }
}
