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
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collections;
import java.util.List;

public class StackMapTable implements ClassAttribute {

    private final int nameIndex;
    private final StackMapFrame[] entries;
    private final ClassFile classFile;

    public StackMapTable(ClassFile classFile, int nameIndex, StackMapFrame[] entries) {
        this.classFile = classFile;
        this.nameIndex = nameIndex;
        this.entries = entries;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        DataOutputStream dos = new DataOutputStream(bos);

        try {
            for (StackMapFrame frame : entries) {
                frame.write(dos);
            }
        } finally {
            dos.close();
        }

        byte[] bytes = bos.toByteArray();
        os.writeShort(nameIndex);
        os.writeInt(bytes.length);
        os.write(bytes);
    }

    @Override
    public String toString() {
        return "StackMapTable{" +
                "nameIndex=" + nameIndex +
                ", entries=" + Arrays.toString(entries) +
                '}';
    }

    public List<StackMapFrame> getStackFrames() {
        List<StackMapFrame> frames = new ArrayList<StackMapFrame>(entries.length);
        for (StackMapFrame entry : entries) {
            frames.add(entry);
        }

        return Collections.unmodifiableList(frames);
    }

    public int getNameIndex() {
        return nameIndex;
    }
}
