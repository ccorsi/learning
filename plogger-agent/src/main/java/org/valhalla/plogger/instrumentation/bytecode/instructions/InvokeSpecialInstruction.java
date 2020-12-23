package org.valhalla.plogger.instrumentation.bytecode.instructions;
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

import org.valhalla.plogger.instrumentation.bytecode.manager.ClassManager;

import java.io.DataOutput;
import java.io.IOException;

public class InvokeSpecialInstruction extends AbstractInstruction {
    private final int constantPoolIndex;
    private final int operandStackChange;

    public InvokeSpecialInstruction(ClassManager classManager, int constantPoolIndex, InstructionEntry entry) {
        super(InstructionEntryFactory.INVOKESPECIAL, "INVOKESPECIAL", entry);
        this.constantPoolIndex = constantPoolIndex;
        this.operandStackChange = calculateOperandStack(classManager.getConstantPoolManager(), constantPoolIndex,
                -1);
    }

    public int getConstantPoolIndex() {
        return constantPoolIndex;
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
    public void write(DataOutput os) throws IOException {
        super.write(os);
        os.writeShort(constantPoolIndex);
    }
}
