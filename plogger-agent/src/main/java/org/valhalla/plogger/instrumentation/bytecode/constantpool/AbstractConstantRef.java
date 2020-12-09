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

import java.io.DataOutput;
import java.io.IOException;

public abstract class AbstractConstantRef implements ConstantPoolEntry {

    protected final int classIndex;
    protected final int nameAndTypeIndex;
    protected final int tag;

    protected AbstractConstantRef(int tag, int classIndex, int nameAndTypeIndex) {
        this.tag = tag;
        this.classIndex = classIndex;
        this.nameAndTypeIndex = nameAndTypeIndex;
    }

    @Override
    public int entries() {
        return 1;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(tag);
        os.writeShort(classIndex);
        os.writeShort(nameAndTypeIndex);
    }

    public ConstantClass getClass(ConstantPoolEntry[] cpool) {
        return (ConstantClass) cpool[classIndex];
    }

    public ConstantNameAndType getNameAndType(ConstantPoolEntry[] cpool) {
        return (ConstantNameAndType) cpool[nameAndTypeIndex];
    }

    public int getClassIndex() {
        return classIndex;
    }

    public int getNameAndTypeIndex() {
        return nameAndTypeIndex;
    }
}
