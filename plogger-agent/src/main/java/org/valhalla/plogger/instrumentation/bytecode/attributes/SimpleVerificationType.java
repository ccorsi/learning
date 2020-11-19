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

import java.io.DataOutput;
import java.io.IOException;

public class SimpleVerificationType implements VerificationType, VerificationTypeTag {
    private final int tag;
    private final int size;

    public SimpleVerificationType(int tag, int size) {
        this.tag = tag;
        this.size = size;
    }

    @Override
    public int tag() {
        return tag;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.write(tag);
    }

    @Override
    public String toString() {
        String tagName = "n/a";
        switch(tag) {
            case TOP:
                tagName = "top";
                break;
            case INTEGER:
                tagName = "int";
                break;
            case FLOAT:
                tagName = "float";
                break;
            case LONG:
                tagName = "long";
                break;
            case DOUBLE:
                tagName = "double";
                break;
            case NULL:
                tagName = "null";
                break;
            case UNINITIALIZED_THIS:
                tagName = "uninitialized this";
                break;
        }
        return "VerificationType{" +
                "tag=" + tagName +
                ", size=" + size +
                '}';
    }
}
