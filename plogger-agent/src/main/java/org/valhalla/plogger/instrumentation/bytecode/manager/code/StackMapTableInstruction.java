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
import org.valhalla.plogger.instrumentation.bytecode.attributes.StackMapTable;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

public class StackMapTableInstruction implements Instruction {
    // This will contain a list of stack frames that will be
    // used to generate the StackMapTable.
    // Each stack frame will be associated with an instruction
    // so that it is easy enough to determine the start of the
    // next frame compared to the prior instruction.

    private final Instruction startInstruction;
    private final List<StackFrameInstruction> frames;
    private final int nameIndex;

    public StackMapTableInstruction(int nameIndex, Instruction startInstruction) {
        this.nameIndex = nameIndex;
        this.startInstruction = startInstruction;
        this.frames = new ArrayList<StackFrameInstruction>();
    }

    public void addStackFrame(StackFrameInstruction frame) {
        frames.add(frame);
    }

    // TODO: does this method require more parameters?
    public StackMapTable getStackMapTable(ClassFile classFile, CodeAttribute codeAttribute) {
        StackMapTable stackMapTable = null;

        StackMapFrame[] stackFrames = new StackMapFrame[frames.size()];

        for(int idx = 0 ; idx < frames.size() ; idx++) {
            stackFrames[idx] = frames.get(idx).getStackMapFrame(classFile, codeAttribute);
        }

        return new StackMapTable(classFile, nameIndex, stackFrames);
    }

    @Override
    public int normalize(ClassFile classFile, int pc) {
        return startInstruction.normalize(classFile, pc);
    }

    @Override
    public void updateReferences() {
        startInstruction.updateReferences();
    }

    @Override
    public int pos() {
        return startInstruction.pos();
    }

    @Override
    public int size() {
        return startInstruction.size();
    }

    @Override
    public int stack() {
        return startInstruction.stack();
    }

    @Override
    public void write(DataOutput os) throws IOException {
        startInstruction.write(os);
    }
}
