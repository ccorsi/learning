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

import java.io.DataOutput;
import java.io.IOException;

public class WideFormat1Instruction extends AbstractInstruction {
    private final int localVariableTableIndex;
    private final int opCode;
    private int operandStackChange; // TODO: This depends on the passed opCode

    public WideFormat1Instruction(int opCode, int localVariableTableIndex, InstructionEntry entry) {
        super(InstructionEntryFactory.WIDE, "WIDE", entry);
        this.opCode = opCode;
        this.localVariableTableIndex = localVariableTableIndex;
    }

    @Override
    public int size() {
        return 4;
    }

    @Override
    public int stack() {
        /*
         This depends on the instruction that is being wide.  The opCode is the
         instruction that will be applied to wide the type.  These instructions can be
         one of  iload, fload, aload, lload, dload, istore, fstore, astore, lstore,
         dstore, or ret.

         NOTE:  This is not going to be implemented since I am not adding a wide
                instruction to the instrumenting method.
         */
        throw new ClassCastException("stack method not implemented");
    }

    @Override
    protected void sync() {

    }

    @Override
    public void write(DataOutput os) throws IOException {
        super.write(os);
        os.write(opCode);  // this opCode of the instruction being widen
        os.writeShort(localVariableTableIndex);
    }
}
