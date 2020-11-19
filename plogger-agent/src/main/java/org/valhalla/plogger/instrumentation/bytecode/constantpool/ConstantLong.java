package org.valhalla.plogger.instrumentation.bytecode.constantpool;

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

import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.DataOutput;
import java.io.IOException;
import java.util.Arrays;

public class ConstantLong implements ConstantPoolEntry {
    private final byte[] highBytes;
    private final byte[] lowBytes;

    public ConstantLong(byte[] highBytes, byte[] lowBytes) {
        this.highBytes = highBytes;
        this.lowBytes = lowBytes;
    }

    @Override
    public void validate() throws ConstantPoolEntryException {
        try {
            byte bytes[] = new byte[highBytes.length + lowBytes.length];
            System.arraycopy(highBytes,0, bytes, 0, highBytes.length);
            System.arraycopy(lowBytes, 0, bytes, highBytes.length, lowBytes.length);
            new DataInputStream(new ByteArrayInputStream(bytes)).readLong();
        } catch (Throwable t) {
            throw new ConstantPoolEntryException(t);
        }
    }

    @Override
    public String toString() {
        return "ConstantLong{" +
                "highBytes=" + Arrays.toString(highBytes) +
                ", lowBytes=" + Arrays.toString(lowBytes) +
                '}';
    }

    @Override
    public int entries() {
        return 2;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(LONG);
        os.write(highBytes);
        os.write(lowBytes);
    }
}
