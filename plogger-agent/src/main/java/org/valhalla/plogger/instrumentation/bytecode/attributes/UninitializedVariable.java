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

import java.io.DataOutput;
import java.io.IOException;

// TODO: Insure that the offset is updated when the byte code array is being
//  updated.
public class UninitializedVariable implements VerificationType {

    /**
     * This is the offset within the byte code array in which its
     * associated StackMapTable in which the new instruction that
     * create the object that is being stored.
     */
    private final int offset;
    private final ClassFile classFile;

    public UninitializedVariable(ClassFile classFile, int offset) {
        this.classFile = classFile;
        this.offset = offset;
    }

    @Override
    public int tag() {
        return VerificationTypeTag.UNINITIALIZED;
    }

    @Override
    public int size() {
        return 1;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.write(VerificationTypeTag.UNINITIALIZED);
        os.writeShort(offset);
    }

    @Override
    public String toString() {
        return "UninitializedVariable{" +
                "offset=" + offset +
                '}';
    }

    public int getOffSet() {
        return offset;
    }
}
