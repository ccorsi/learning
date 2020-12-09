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

/**
 * This instruction will manage all of the different load instructions that also
 * contain an associated _&lt;n&gt; type instruction.  These are the [a|i|l|d|f]load
 * instructions where they have ?load_#, where # is 0,1,2, or 3.
 */
public class LoadOrStoreInstruction extends AbstractInstruction {
    private final int index;
    private final int operandStackChange;

    /**
     * The instruction operand code, local variable table index,
     * stack operand change and a descriptive name.
     *
     * @param opCode This instruction operand code
     * @param index This is the index within the local variable table
     * @param operandStackChange This is the change to the stack after
     *                           this instruction is processed
     * @param name This is the descriptive name of this instruction
     */
    public LoadOrStoreInstruction(int opCode, int index, int operandStackChange, String name, InstructionEntry entry) {
        super(opCode, name, entry);
        this.index = index;
        this.operandStackChange = operandStackChange;
    }

    @Override
    public int size() {
        return (index > 3) ? 2 : 1;
    }

    @Override
    public int stack() {
        return operandStackChange;
    }

    @Override
    protected void sync() {

    }

    @Override
    public void write(DataOutput os) throws IOException {
        super.write(os);
        if (index > 3) {
            // This is one of the ?load or ?store instructions
            os.write(index);
        }
    }
}
