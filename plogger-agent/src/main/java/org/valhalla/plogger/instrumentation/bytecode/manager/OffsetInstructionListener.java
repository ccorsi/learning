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

public abstract class OffsetInstructionListener implements InstructionListener {
    private final AbstractInstruction startInstruction;

    public OffsetInstructionListener(AbstractInstruction startInstruction) {
        this.startInstruction = startInstruction;
    }

    @Override
    public void event(InstructionEntry endInstruction, int newPos) {
        int offset = 0;
        AbstractInstruction instruction = startInstruction;

        for (; instruction != null && instruction != endInstruction;
             instruction = instruction.getNext()) {
            offset += instruction.size();
        }

        if (instruction != endInstruction) {
            throw new ClassFileException("Unable to find endInstruction " + endInstruction);
        }

        offset(offset);
    }

    protected abstract void offset(int offset);
}
