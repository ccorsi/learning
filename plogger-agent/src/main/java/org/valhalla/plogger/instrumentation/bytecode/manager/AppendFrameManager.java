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

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileException;

import java.io.DataInputStream;
import java.io.DataOutput;
import java.io.IOException;
import java.util.Arrays;

public class AppendFrameManager implements StackMapFrameManager {
    private final int frameType;
    private int offset;
    private final VerificationTypeManager[] entries;
    private boolean debug = Boolean.getBoolean(StackMapTableManager.DEBUG_PROPERTY_NAME);

    public AppendFrameManager(int frameType, DataInputStream dis) {
        this.frameType = frameType;
        try {
            this.offset = dis.readUnsignedShort();
            int size = frameType - 251;
            entries = new VerificationTypeManager[size];
            for(int idx = 0 ; idx < entries.length ; idx++) {
                entries[idx] = VerificationTypeManagerFactory.create(dis);
            }
        } catch (IOException e) {
            throw new ClassFileException(e);
        }
    }

    public AppendFrameManager(int offSet, VerificationTypeManager[] entries) {
        this.frameType = 251 + entries.length;
        this.offset = offSet;
        this.entries = entries;
    }

    @Override
    public int offset() {
        return offset;
    }

    @Override
    public void setOffset(int offset) {
        this.offset = offset;
    }

    @Override
    public void sync(AbstractInstruction instruction, int pos) {
        for(VerificationTypeManager type : entries) {
            type.sync(instruction, pos);
        }
    }

    @Override
    public void write(DataOutput os) throws IOException {
        if (debug) {
            System.out.println(this);
        }
        os.write(frameType);
        os.writeShort(offset);
        for (VerificationTypeManager type : entries) {
            type.write(os);
        }
    }

    @Override
    public String toString() {
        return "AppendFrameManager{" +
                "frameType=" + frameType +
                ", offset=" + offset +
                ", entries=" + Arrays.toString(entries) +
                '}';
    }
}
