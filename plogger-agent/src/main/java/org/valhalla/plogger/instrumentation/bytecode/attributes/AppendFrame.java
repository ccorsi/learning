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

import java.io.ByteArrayOutputStream;
import java.io.DataOutput;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.Arrays;

public class AppendFrame extends AbstractStackMapFrame {
    private final int offset;
    private final VerificationType[] verificationTypes;

    public AppendFrame(ClassFile classFile, CodeAttribute code, int frameType, int offset, VerificationType[] verificationTypes) {
        super(classFile, code, frameType);
        this.offset = offset;
        this.verificationTypes = verificationTypes;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        super.write(os);

        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        DataOutputStream dos = new DataOutputStream(bos);

        try {
            for(VerificationType type : verificationTypes) {
                type.write(dos);
            }
        } finally {
            dos.close();
        }

        byte[] bytes = bos.toByteArray();

        os.writeInt(bytes.length);
        os.write(bytes);
    }

    @Override
    public String toString() {
        return "AppendFrame{" +
                "offset=" + offset +
                ", verificationTypes=" + Arrays.toString(verificationTypes) +
                ", frameType=" + frameType +
                '}';
    }
}
