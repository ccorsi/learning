package org.valhalla.plogger.instrumentation.bytecode.manager;
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

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileWriter;
import org.valhalla.plogger.instrumentation.bytecode.instructions.AbstractInstruction;
import org.valhalla.plogger.instrumentation.bytecode.instructions.InstructionEntry;
import org.valhalla.plogger.instrumentation.bytecode.instructions.InstructionListener;

import java.io.DataOutput;
import java.io.IOException;

public class ExceptionTableEntryManager implements ClassFileWriter {
    private int startPc;
    private int endPc;
    private int handlePc;
    private final int catchType;

    public ExceptionTableEntryManager(int startPcs, int endPcs, int handlePcs, int catchTypes) {
        this.startPc = startPcs;
        this.endPc = endPcs;
        this.handlePc = handlePcs;
        this.catchType = catchTypes;
    }

    public void sync(AbstractInstruction instruction, int pos) {
        if (startPc == pos) {
            instruction.addListener(new InstructionListener() {
                @Override
                public void event(InstructionEntry instruction, int newPos) {
                    startPc = newPos;
                }
            });
        }
        if(endPc == pos) {
            instruction.addListener(new InstructionListener() {
                @Override
                public void event(InstructionEntry instruction, int newPos) {
                    endPc = newPos;
                }
            });
        }
        if(handlePc == pos) {
            instruction.addListener(new InstructionListener() {
                @Override
                public void event(InstructionEntry instruction, int newPos) {
                    handlePc = newPos;
                }
            });
        }
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeShort(startPc);
        os.writeShort(endPc);
        os.writeShort(handlePc);
        os.writeShort(catchType);
    }

    @Override
    public String toString() {
        return "ExceptionTableEntryManager{" +
                "startPc=" + startPc +
                ", endPc=" + endPc +
                ", handlePc=" + handlePc +
                ", catchType=" + catchType +
                '}';
    }
}
