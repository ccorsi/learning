package org.valhalla.plogger.instrumentation.bytecode.constantpool;


import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class ConstantDynamic extends AbstractConstantDynamic {
    public ConstantDynamic(ClassFile classFile, int bootstrapMethodAttributeIndex, int nameAndTypeIndex) {
        super(classFile, bootstrapMethodAttributeIndex, nameAndTypeIndex);
    }

    @Override
    public void validate() throws ConstantPoolEntryException {
        super.validate();
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

    @Override
    public String toString() {
        return "ConstantDynamic{" +
                "bootstrapMethodAttributeIndex=" + bootstrapMethodAttributeIndex +
                ", nameAndTypeIndex=" + nameAndTypeIndex +
                '}';
    }
}
