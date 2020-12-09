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
import org.valhalla.plogger.instrumentation.bytecode.attributes.StackMapFrame;
import org.valhalla.plogger.instrumentation.bytecode.attributes.VerificationType;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class FullFrame implements StackFrameInstruction {

    private final int offset;
    private final VerificationType[] locals;
    private final VerificationType[] stacks;

    public FullFrame(int offset, VerificationType[] locals, VerificationType[] stacks) {
        this.offset = offset;
        this.locals = locals;
        this.stacks = stacks;
    }

    @Override
    public void write(DataOutput os) throws IOException {
//        os.write(255);
//        os.writeShort(offset);
//        os.writeShort(locals.length);
//        for(VerificationType local : locals) {
//            local.write(os);
//        }
//        os.writeShort(stacks.length);
//        for(VerificationType stack : stacks) {
//            stack.write(os);
//        }
    }

    @Override
    public StackMapFrame getStackMapFrame(ClassFile classFile, CodeAttribute codeAttribute) {
        return new org.valhalla.plogger.instrumentation.bytecode.attributes.FullFrame(classFile,
                codeAttribute, 255, offset, locals, stacks);
    }
}
