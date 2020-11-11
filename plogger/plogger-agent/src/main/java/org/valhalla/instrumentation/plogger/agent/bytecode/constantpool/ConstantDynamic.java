package org.valhalla.instrumentation.plogger.agent.bytecode.constantpool;

import org.valhalla.instrumentation.plogger.agent.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class ConstantDynamic extends AbstractConstantDynamic {
    public ConstantDynamic(int bootstrapMethodAttributeIndex, int nameAndTypeIndex) {
        super(bootstrapMethodAttributeIndex, nameAndTypeIndex);
    }

    @Override
    public void validate(ClassFile classFile) throws ConstantPoolEntryException {
        super.validate(classFile);
        ConstantPoolEntry[] cpool = classFile.getConstantPool();
        ConstantNameAndType entry = getNameAndType(cpool);
        ConstantUtf8 descriptor = entry.getDescriptor(cpool);
        String signature = descriptor.getString();
        if ( signature.charAt(0) == '(') {
            throw new ConstantPoolEntryException("Invalid reference, it is not referencing a field.");
        }
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(DYNAMIC);
        super.write(os);
    }
}
