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

public class ConstantNameAndType implements ConstantPoolEntry {
    private final int nameIndex;
    private final int descriptorIndex;
    private final ClassFile classFile;

    public ConstantNameAndType(ClassFile classFile, int nameIndex, int descriptorIndex) {
        this.classFile = classFile;
        this.nameIndex = nameIndex;
        this.descriptorIndex = descriptorIndex;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(NAME_AND_TYPE);
        os.writeShort(nameIndex);
        os.writeShort(descriptorIndex);
    }

    @Override
    public int entries() {
        return 1;
    }

    @Override
    public String toString() {
        return "ConstantNameAndType{" +
                "nameIndex=" + nameIndex +
                ", descriptorIndex=" + descriptorIndex +
                '}';
    }

    @Override
    public void validate() throws ConstantPoolEntryException {
        ConstantPoolEntry[] cpool = classFile.getConstantPool();
        if (nameIndex < 1 || nameIndex >= cpool.length) {
            throw new ConstantPoolEntryException("Invalid name index range: " + nameIndex + " should be between [1,"
                    + (cpool.length -1) + "].");
        }
        if ( ! (cpool[nameIndex] instanceof ConstantUtf8)) {
            throw new ConstantPoolEntryException("Name index " + nameIndex + " is not a ConstantUtf8 constant pool entry");
        }
        if ( ! (cpool[descriptorIndex] instanceof ConstantUtf8)) {
            throw new ConstantPoolEntryException("The descriptor index " + descriptorIndex
                    + " is not a ConstantUtf8 constant pool entry");
        }
    }

    public ConstantUtf8 getName(ConstantPoolEntry[] cpool) {
        return (ConstantUtf8) cpool[nameIndex];
    }

    public ConstantUtf8 getDescriptor(ConstantPoolEntry[] cpool) {
        return (ConstantUtf8) cpool[descriptorIndex];
    }
}
