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

public class Dup2Instruction extends AbstractInstruction {

    private int pos; // TODO: is this really required?

    protected Dup2Instruction(int pos, InstructionEntry entry) {
        super(InstructionEntryFactory.DUP2, "DUP2", entry);
        this.pos = pos;
    }

    @Override
    public int size() {
        return 1;
    }

    @Override
    public int stack() {
        /*
        TODO: The stack size depends on what type of instances that is being
        dup.  A category 1 type will add 1 to the stack.  While a category 2
        will add 2 to the stack.  Category 2 type are double and long types.
         */
//        return 0;
        throw new ClassFileException("stack method was not implemented");
    }

    @Override
    public void update(int pos) {
        // Update this instruction position within the byte code array
        this.pos = pos;
        super.update(pos);
    }

    @Override
    protected void sync() {

    }
}
