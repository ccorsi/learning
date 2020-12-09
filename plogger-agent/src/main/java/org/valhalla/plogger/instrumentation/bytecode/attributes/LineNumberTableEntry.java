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
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileWriter;

import java.io.DataOutput;
import java.io.IOException;

public class LineNumberTableEntry implements ClassFileWriter {
    private final int startPc;
    private final int lineNumber;
    private final CodeAttribute code;
    private final ClassFile classFile;

    public LineNumberTableEntry(ClassFile classFile, CodeAttribute code, int startPc, int lineNumber) {
        this.classFile = classFile;
        this.code = code;
        this.startPc = startPc;
        this.lineNumber = lineNumber;
    }

    public int getStartPc() {
        return startPc;
    }

    public int getLineNumber() {
        return lineNumber;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeShort(startPc);
        os.writeShort(lineNumber);
    }

    @Override
    public String toString() {
        return "LineNumberTableEntry{" +
                "startPc=" + startPc +
                ", lineNumber=" + lineNumber +
                '}';
    }
}
