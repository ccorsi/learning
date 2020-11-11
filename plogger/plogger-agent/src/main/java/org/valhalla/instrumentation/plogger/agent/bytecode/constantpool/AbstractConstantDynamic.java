package org.valhalla.instrumentation.plogger.agent.bytecode.constantpool;

import org.valhalla.instrumentation.plogger.agent.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public abstract class AbstractConstantDynamic implements ConstantPoolEntry {

    protected final int bootstrapMethodAttributeIndex;
    protected final int nameAndTypeIndex;

    protected AbstractConstantDynamic(int bootstrapMethodAttributeIndex, int nameAndTypeIndex) {
        this.bootstrapMethodAttributeIndex = bootstrapMethodAttributeIndex;
        this.nameAndTypeIndex = nameAndTypeIndex;
    }

    @Override
    public void validate(ClassFile classFile) throws ConstantPoolEntryException {
        ConstantPoolEntry[] cpool = classFile.getConstantPool();
        // TODO: Update the ConstantEntry check to include the class file to be able to
        //       correctly validate that the bootstrap method attribute index is referencing
        //       a valid entry within the class file boot strap method table.
        if ( ! (cpool[nameAndTypeIndex] instanceof ConstantNameAndType)) {
            throw new ConstantPoolEntryException("Invalid name index type.");
        }
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeShort(bootstrapMethodAttributeIndex);
        os.writeShort(nameAndTypeIndex);
    }

    public ConstantNameAndType getNameAndType(ConstantPoolEntry[] cpool) {
        return (ConstantNameAndType) cpool[nameAndTypeIndex];
    }
}
