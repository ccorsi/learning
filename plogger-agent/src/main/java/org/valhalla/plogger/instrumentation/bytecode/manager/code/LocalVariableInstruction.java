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

import org.valhalla.plogger.instrumentation.bytecode.attributes.LocalVariableTable;
import org.valhalla.plogger.instrumentation.bytecode.attributes.LocalVariableTypeTable;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class LocalVariableInstruction implements Instruction {

    private final Instruction startPc;
    private final Instruction endPc;
    private final int localVariableType;

    public LocalVariableInstruction(Instruction startPc, Instruction endPc,
                                    int localVariableType) {
        this.startPc = startPc;
        this.endPc = endPc;
        this.localVariableType = localVariableType;
    }

    public LocalVariableTable getLocalVariable() {
        LocalVariableTable localVariable = null;
        return localVariable;
    }

    public LocalVariableTypeTable getLocalVariableTable() {
        LocalVariableTypeTable localVariableTable = null;
        return localVariableTable;
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
