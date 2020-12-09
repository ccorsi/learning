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

// TODO: The calculation of the size value will be depend if we are popping
//   a category 1 or category 2 reference.  Type 2 are basically long and
//   double types.  The rest are all category 1.
public class Pop2Instruction extends AbstractInstruction {
    private int pos; // TODO: is this really required?
    private int stackOperandChange;

    public Pop2Instruction(int pos, InstructionEntry entry) {
        super(InstructionEntryFactory.POP2, "POP2", entry);
        this.stackOperandChange = 2; // Set it to the worse case
        this.pos = pos;
    }

    @Override
    public int size() {
        return 1;
    }

    @Override
    public int stack() {
        /*
        TODO: The stack size depends on what type of instance that is being
            popped.  A category 1 type will return 1 while a category 2 type
            will return 2.
         */
        throw new ClassFileException("stack method not implemented");
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
