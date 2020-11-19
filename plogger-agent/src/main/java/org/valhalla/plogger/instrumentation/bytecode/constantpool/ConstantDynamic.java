package org.valhalla.plogger.instrumentation.bytecode.constantpool;

/*
MIT License

Copyright (c) 2020 Claudio Corsi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

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
