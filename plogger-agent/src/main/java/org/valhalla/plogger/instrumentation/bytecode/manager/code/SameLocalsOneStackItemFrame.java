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

import org.valhalla.plogger.instrumentation.bytecode.attributes.*;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class SameLocalsOneStackItemFrame implements StackFrameInstruction {

    private final int offset;
    private final VerificationType type;

    public SameLocalsOneStackItemFrame(int offset, VerificationType type) {
        this.offset = offset;
        this.type = type;
    }

    @Override
    public void write(DataOutput os) throws IOException {
//        if (offset < 64) {
//            throw new IOException("Invalid frame type: " + offset);
//        } else if (offset > 127) {
//            // Write a Same Locals 1 Stack Iterm Extended Frame
//            os.write(247);
//            os.writeShort(offset - 64);
//        } else {
//            // Write a Same Locals 1 Stack Item Frame
//            os.write(offset);
//        }
//        type.write(os);
    }

    @Override
    public StackMapFrame getStackMapFrame(ClassFile classFile, CodeAttribute codeAttribute) {
        if (offset > 127) {
            // Write a Same Locals 1 Stack Iterm Extended Frame
            return new SameLocal1StackItemExtendedFrame(classFile, codeAttribute, 247, offset - 64, type);
        } else {
            // Write a Same Locals 1 Stack Item Frame
            return new SameLocals1StackItemFrame(classFile, codeAttribute, offset, type);
        }
    }
}
