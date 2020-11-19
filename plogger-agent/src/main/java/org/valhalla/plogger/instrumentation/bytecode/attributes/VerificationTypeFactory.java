package org.valhalla.plogger.instrumentation.bytecode.attributes;

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

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileException;

import java.io.DataInputStream;
import java.io.IOException;

public class VerificationTypeFactory implements VerificationTypeTag {
    public static VerificationType create(ClassFile classFile, DataInputStream dis) throws IOException, ClassFileException {
        int tag = dis.readUnsignedByte();
        VerificationType type;

        switch(tag) {
            case TOP:
                type = VerificationType.TopVariable;
                break;
            case INTEGER:
                type = VerificationType.IntegerVariable;
                break;
            case FLOAT:
                type = VerificationType.FloatVariable;
                break;
            case DOUBLE:
                type = VerificationType.DoubleVariable;
                break;
            case LONG:
                type = VerificationType.LongVariable;
                break;
            case OBJECT:
                type = new ObjectVariable(classFile, dis.readUnsignedShort());
                break;
            case UNINITIALIZED:
                type = new UninitializedVariable(classFile, dis.readUnsignedShort());
                break;
            case UNINITIALIZED_THIS:
                type = VerificationType.UninitializedThisVariable;
                break;
            default:
                throw new ClassFileException("Unknown Verification type: " + tag);
        }

        return type;
    }
}
