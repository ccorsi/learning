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

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileException;

import java.io.DataOutput;
import java.io.IOException;

public class GotoInstruction extends AbstractInstruction {
    private final int operandStackChange;
    private int branchPc;

    @Override
    public int stack() {
        return operandStackChange;
    }

    @Override
    protected void sync() {
        AbstractInstruction instruction = getOffsetInstruction(branchPc);

        if (branchPc < 0) {
            addListener(new OffsetInstructionListener(instruction) {
                @Override
                protected void offset(int offset) {
                    branchPc = 0;
                    branchPc -= offset;
                }
            });
        } else {
            instruction.addListener(new OffsetInstructionListener(this) {
                @Override
                protected void offset(int offset) {
                    branchPc = offset;
                }
            });
        }
    }

    public GotoInstruction(int opCode, int operandStackChange, String name, int branchPc, InstructionEntry entry) {
        super(opCode, name, entry);
        // TODO: replace the operandStackChange value with a static final int since it does
        //  not change throughout the lifetime of the instruction.
        this.operandStackChange = operandStackChange;
        this.branchPc = branchPc;
    }

    @Override
    public int size() {
        return 3;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        super.write(os);
        os.writeShort(branchPc);
    }

    @Override
    public String toString() {
        return "GotoInstruction{" +
                "branchPc=" + branchPc +
                '}';
    }
}
