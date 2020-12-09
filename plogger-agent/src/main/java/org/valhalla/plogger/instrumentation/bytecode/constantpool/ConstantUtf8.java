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

import java.io.DataOutput;
import java.io.IOException;

public class ConstantUtf8 implements ConstantPoolEntry {
    private final int length;
    private final byte[] bytes;

    public ConstantUtf8(int length, byte[] bytes) {
        this.length = length;
        this.bytes = bytes;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.write(UTF8);
        os.writeShort(bytes.length);
        os.write(bytes);
    }

    @Override
    public int entries() {
        return 1;
    }

    @Override
    public String toString() {
        return "ConstantUtf8{" +
                "length=" + length +
                // ", bytes=" + Arrays.toString(bytes) +
                ", string=" + new String(bytes) +
                '}';
    }

    public String getString() {
        return new String(bytes);
    }
}
