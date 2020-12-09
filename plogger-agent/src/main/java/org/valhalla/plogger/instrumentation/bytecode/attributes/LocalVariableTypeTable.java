package org.valhalla.plogger.instrumentation.bytecode.attributes;

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

import java.io.ByteArrayOutputStream;
import java.io.DataOutput;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.Arrays;

public class LocalVariableTypeTable implements ClassAttribute {
    private final int nameIndex;
    private final LocalVariableTypeTableEntry[] types;
    private final ClassFile classFile;
    private final CodeAttribute code;

    public LocalVariableTypeTable(ClassFile classFile, CodeAttribute code, int nameIndex, LocalVariableTypeTableEntry[] types) {
        this.classFile = classFile;
        this.code = code;
        this.nameIndex = nameIndex;
        this.types = types;
    }

    public int getNameIndex() {
        return nameIndex;
    }

    public LocalVariableTypeTableEntry[] getEntries() {
        return types;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        DataOutputStream dos = new DataOutputStream(bos);

    }

    @Override
    public String toString() {
        return "LocalVariableTypeTable{" +
                "nameIndex=" + nameIndex +
                ", types=" + Arrays.toString(types) +
                '}';
    }
}
