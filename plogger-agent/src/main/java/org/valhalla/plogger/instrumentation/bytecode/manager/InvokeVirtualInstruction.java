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

// TODO: We need to calculate the operand stack change
public class InvokeVirtualInstruction extends AbstractInstruction {
    private final int constantPoolIndex;
    private int size = 3;
    private int operandStackChange = 0; // TODO: needs to be calculated using the ConstantPool table

    public InvokeVirtualInstruction(int constantPoolIndex, InstructionEntry entry) {
        super(InstructionEntryFactory.INVOKEVIRTUAL, "INVOKEVIRTUAL", entry);
        this.constantPoolIndex = constantPoolIndex;
    }

    @Override
    public int stack() {
        /*
        TODO: This needs to be calculated using the ConstantPoolManager
         */
        throw new ClassFileException("method not implemented");
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    protected void sync() {

    }

    @Override
    public void write(DataOutput os) throws IOException {
        super.write(os);
        os.writeShort(constantPoolIndex);
    }
}
