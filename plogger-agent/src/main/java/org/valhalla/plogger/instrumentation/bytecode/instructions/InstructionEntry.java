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

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileWriter;

public interface InstructionEntry extends ClassFileWriter {
    /**
     * This will return the number of bytes that this instruction will
     * use.  This is useful to determine which position the current
     * instruction is located within the byte code array.
     *
     * @return The number of bytes this instruction will use
     */
    int size();

    /**
     * This method will return this instruction operand code.
     *
     * @return The operand code associated with this instruction
     */
    int opCode();

    /**
     * This will return the associated string representation of this
     * instruction operand code.
     *
     * @return instruction name for this instruction operand code
     */
    String name();

    /**
     * This method will return the affects of the operand stack after
     * calling this instruction.  This value can be negative, zero or
     * positive.  This value is static throughout most of the different
     * instructions.  The few remaining ones will be require to sync
     * up with the associated instruction call.
     *
     * @return The operand stack count change after calling this instruction
     */
    int stack();

}
