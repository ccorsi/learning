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

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileWriter;
import org.valhalla.plogger.instrumentation.bytecode.instructions.AbstractInstruction;

public interface VerificationTypeManager extends ClassFileWriter {
    int TOP = 0;
    int INTEGER = 1;
    int FLOAT = 2;
    int DOUBLE = 3;
    int LONG = 4;
    int NULL = 5;
    int UNINITIALIZED_THIS = 6;
    int OBJECT = 7;
    int UNINITIALIZED = 8;

    int tag();
    int size();

    VerificationTypeManager TopVariable = new BasicVariableInfoManager(TOP, 1);
    VerificationTypeManager IntegerVariable = new BasicVariableInfoManager(INTEGER, 1);
    VerificationTypeManager FloatVariable = new BasicVariableInfoManager(FLOAT, 1);
    VerificationTypeManager DoubleVariable = new BasicVariableInfoManager(DOUBLE, 2);
    VerificationTypeManager LongVariable = new BasicVariableInfoManager(LONG, 2);
    VerificationTypeManager UninitializedThisVariable = new BasicVariableInfoManager(UNINITIALIZED_THIS, 1);

    void sync(AbstractInstruction instruction, int pos);
}
