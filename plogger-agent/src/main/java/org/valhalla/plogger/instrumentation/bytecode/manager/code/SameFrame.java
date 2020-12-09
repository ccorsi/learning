package org.valhalla.plogger.instrumentation.bytecode.manager.code;
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

import org.valhalla.plogger.instrumentation.bytecode.attributes.CodeAttribute;
import org.valhalla.plogger.instrumentation.bytecode.attributes.SameExtendedFrame;
import org.valhalla.plogger.instrumentation.bytecode.attributes.StackMapFrame;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class SameFrame implements StackFrameInstruction {

    private final int offset;

    public SameFrame(int offset) {
        this.offset = offset;
    }

    @Override
    public void write(DataOutput os) throws IOException {
//        if (offset > 63) {
//            // Write a Same Frame Extended Stack Frame
//            os.write(251);
//            os.writeShort(offset);
//        } else {
//            // Write a Same Frame Stack Frame
//            os.write(offset);
//        }
    }

    @Override
    public StackMapFrame getStackMapFrame(ClassFile classFile, CodeAttribute codeAttribute) {
        if (offset > 63) {
            // Write a Same Frame Extended Stack Frame
            return new SameExtendedFrame(classFile, codeAttribute, 251, offset);
        } else {
            // Write a Same Frame Stack Frame
            return new org.valhalla.plogger.instrumentation.bytecode.attributes.SameFrame(classFile, codeAttribute, offset);
        }
    }
}
