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

public class ConstantNameAndType implements ConstantPoolEntry {
    private final int nameIndex;
    private final int descriptorIndex;

    public ConstantNameAndType(int nameIndex, int descriptorIndex) {
        this.nameIndex = nameIndex;
        this.descriptorIndex = descriptorIndex;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.write(NAME_AND_TYPE);
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

    public ConstantUtf8 getName(ConstantPoolEntry[] cpool) {
        return (ConstantUtf8) cpool[nameIndex];
    }

    public ConstantUtf8 getDescriptor(ConstantPoolEntry[] cpool) {
        return (ConstantUtf8) cpool[descriptorIndex];
    }

    public int getNameIndex() {
        return nameIndex;
    }

    public int getDescriptorIndex() {
        return descriptorIndex;
    }
}
