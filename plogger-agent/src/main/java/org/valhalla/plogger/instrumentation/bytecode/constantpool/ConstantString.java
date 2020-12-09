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

public class ConstantString implements ConstantPoolEntry {
    private final int stringIndex;

    public ConstantString(int stringIndex) {
        this.stringIndex = stringIndex;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(STRING);
        os.writeShort(stringIndex);
    }

    public int getStringIndex() {
        return stringIndex;
    }

    public String getString(ConstantPoolEntry[] entries) {
        ConstantUtf8 utf8 = (ConstantUtf8) entries[stringIndex];
        return utf8.getString();
    }

    @Override
    public int entries() {
        return 1;
    }

    @Override
    public String toString() {
        return "ConstantString{" +
                "stringIndex=" + stringIndex +
                '}';
    }

//    @Override
//    public void validate() throws ConstantPoolEntryException {
//        ConstantPoolEntry[] cpool = classFile.getConstantPool();
//        if (stringIndex < 1 || stringIndex >= cpool.length) {
//            throw new ConstantPoolEntryException("Invalid String Index range: " + stringIndex + " should be between [0,"
//                    + (cpool.length - 1) + "].");
//        }
//        if ( ! (cpool[stringIndex] instanceof ConstantUtf8) ) {
//            throw new ConstantPoolEntryException("Invalid string index reference, not referencing a constant utf8 entry.");
//        }
//    }
}
