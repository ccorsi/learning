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

public class ConstantClass implements ConstantPoolEntry {

    private int nameIndex;

    public ConstantClass(int nameIndex) throws ConstantPoolEntryException {
        if (nameIndex < 1) {
            throw new ConstantPoolEntryException("Invalid name index: " + nameIndex + " must be greater than 0");
        }
        this.nameIndex = nameIndex;
    }

    @Override
    public int entries() {
        return 1;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.write(CLASS);
        os.writeShort(nameIndex);
    }

    @Override
    public String toString() {
        return "ConstantClass{" +
                "nameIndex=" + nameIndex +
                '}';
    }

    public String getClassName(ConstantPoolEntry[] cpools) {
        ConstantUtf8 utf8 = (ConstantUtf8) cpools[nameIndex];
        return utf8.getString();
    }

    public int getNameIndex() {
        return nameIndex;
    }
}
