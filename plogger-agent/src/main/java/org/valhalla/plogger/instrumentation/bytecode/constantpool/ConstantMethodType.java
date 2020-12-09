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

public class ConstantMethodType implements ConstantPoolEntry {
    private final int descriptorIndex;
//    private final ClassFile classFile;

    public ConstantMethodType(int descriptorIndex) {
//        this.classFile = classFile;
        this.descriptorIndex = descriptorIndex;
    }

//    @Override
//    public void validate() throws ConstantPoolEntryException {
//        ConstantPoolEntry[] cpool = classFile.getConstantPool();
//        if ( descriptorIndex < 1 || descriptorIndex >= cpool.length) {
//            throw new ConstantPoolEntryException("Invalid descriptor index: " + descriptorIndex
//                    + " it is supposed to be between [0," + cpool.length + "].");
//        }
//        if (! (cpool[descriptorIndex] instanceof ConstantUtf8)) {
//            throw new ConstantPoolEntryException("The descriptor index is not a Constant Utf8 entry.");
//        }
//    }

    @Override
    public int entries() {
        return 1;
    }

    @Override
    public String toString() {
        return "ConstantMethodType{" +
                "descriptorIndex=" + descriptorIndex +
                '}';
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(METHOD_TYPE);
        os.writeShort(descriptorIndex);
    }
}
