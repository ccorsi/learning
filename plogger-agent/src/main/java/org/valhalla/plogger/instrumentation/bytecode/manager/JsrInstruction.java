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

public class JsrInstruction extends AbstractInstruction {
    private static final int operandStackChange = 1;

    private int branchPc;

    public JsrInstruction(int opCode, String name, int branchPc, InstructionEntry entry) {
        super(opCode, name, entry);
        this.branchPc = branchPc;
    }

    @Override
    public int size() {
        return 3;
    }

    @Override
    public int stack() {
        return operandStackChange;
    }

    @Override
    protected void sync() {
        int current = 0;
        AbstractInstruction instruction = this;
        if (branchPc < 0) {
            for ( instruction = instruction.getPrior() ; // Don't include this size
                  instruction != null && current > branchPc ; instruction = instruction.getPrior() ) {
                current -= instruction.size();
            }
        } else {
            current = size();
            for ( ; instruction != null && current < branchPc ; instruction = instruction.getNext() ) {
                current += instruction.size();
            }
        }
        if (current == branchPc) {
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
        } else {
            throw new ClassFileException(String.format("No instruction with branch offset %s found"));
        }
    }

    @Override
    public void write(DataOutput os) throws IOException {
        super.write(os);
        os.writeShort(branchPc);
    }
}
