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

public class WideFormat2Instruction extends AbstractInstruction {
    private static final int operandStackChange = 0;
    private final int constantValue;
    private final int variableTableIndex;

    public WideFormat2Instruction(int variableTableIndex, int constantValue, InstructionEntry entry) {
        super(InstructionEntryFactory.WIDE, "WIDE", entry);
        this.variableTableIndex = variableTableIndex;
        this.constantValue = constantValue;
    }

    @Override
    public int size() {
        return 5;
    }

    @Override
    public int stack() {
        /*
        TODO: This depends on the category type that is being widen.  This requires that we look at the
            prior instructions to determine the category and then we'll be able to provide the correct
            operand stack change for this instruction.
         */
        throw new ClassFileException("method not implemented");
    }

    @Override
    protected void sync() {

    }

    @Override
    public void write(DataOutput os) throws IOException {
        super.write(os);
        os.write(InstructionEntryFactory.IINC);
        os.writeShort(variableTableIndex);
        os.writeShort(constantValue);
    }
}
