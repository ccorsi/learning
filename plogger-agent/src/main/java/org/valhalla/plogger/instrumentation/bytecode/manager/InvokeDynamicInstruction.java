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
public class InvokeDynamicInstruction extends AbstractInstruction {
    private final int constantPoolIndex;
    private final int dummy;
    private int size = 5;
    private int operandStackChange; // TODO: This needs the ConstantPool table

    public InvokeDynamicInstruction(int constantPoolIndex, int dummy, InstructionEntry entry) {
        super(InstructionEntryFactory.INVOKEDYNAMIC, "INVOKEDYNAMIC", entry);
        this.constantPoolIndex = constantPoolIndex;
        this.dummy = dummy; // TODO: this has to be zero
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public int stack() {
        /*
        TODO: The stack size depends on the number of parameters for the calling
            static method.
         */
        throw new ClassFileException(String.format("stack method not implemented for class: %s", getClass().getSimpleName()));
    }

    @Override
    protected void sync() {

    }

    @Override
    public void write(DataOutput os) throws IOException {
        super.write(os);
        os.writeShort(constantPoolIndex);
        os.writeShort(dummy);  // This is really just 0
    }
}
