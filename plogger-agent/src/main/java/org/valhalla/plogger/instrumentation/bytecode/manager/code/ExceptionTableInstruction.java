package org.valhalla.plogger.instrumentation.bytecode.manager.code;
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

import org.valhalla.plogger.instrumentation.bytecode.attributes.CodeAttribute;
import org.valhalla.plogger.instrumentation.bytecode.attributes.CodeExceptionTable;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class ExceptionTableInstruction implements Instruction {

    private final Instruction startPc;
    private final Instruction endPc;
    private final Instruction handlePc;
    private final int catchType;

    // This will contain a list of ExceptionTableEntry that
    // will reference the startPc, endPc, handlePc, and catchType
    // information.  The startPc, endPc and handlePc should all
    // be an instruction instance that can be used to determine
    // the byte code position within the code byte array.

    public ExceptionTableInstruction(Instruction startPc, Instruction endPc,
                                     Instruction handlePc, int catchType) {
        this.startPc = startPc;
        this.endPc = endPc;
        this.handlePc = handlePc;
        this.catchType = catchType;
    }

    public CodeExceptionTable getExceptionTable(ClassFile classFile, CodeAttribute attribute) {
        return new CodeExceptionTable(classFile, attribute, startPc.pos(), endPc.pos(), handlePc.pos(), catchType);
    }

    @Override
    public int normalize(ClassFile classFile, int pc) {
        return startPc.normalize(classFile, pc);
    }

    @Override
    public void updateReferences() {
        startPc.updateReferences();
    }

    @Override
    public int pos() {
        return startPc.pos();
    }

    @Override
    public int size() {
        return startPc.size();
    }

    @Override
    public int stack() {
        return startPc.stack();
    }

    @Override
    public void write(DataOutput os) throws IOException {
        startPc.write(os);
    }

}
