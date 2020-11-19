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
