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

public class FullFrameManager implements StackMapFrameManager {
    private static final int frameType = 255;
    private int offset;
    private final VerificationTypeManager[] locals;
    private final VerificationTypeManager[] stack;
    private boolean debug = Boolean.getBoolean(StackMapTableManager.DEBUG_PROPERTY_NAME);

    public FullFrameManager(DataInputStream dis) {
        try {
            this.offset = dis.readUnsignedShort();
            int size = dis.readUnsignedShort();
            locals = new VerificationTypeManager[size];
            for(int idx = 0 ; idx < locals.length ; idx++) {
                locals[idx] = VerificationTypeManagerFactory.create(dis);
            }
            size = dis.readUnsignedShort();
            stack = new VerificationTypeManager[size];
            for(int idx = 0 ; idx < stack.length ; idx++) {
                try {
                    stack[idx] = VerificationTypeManagerFactory.create(dis);
                } catch (ClassFileException cfe) {
                    System.out.println("Raised exception when trying to create verification entry: " + idx);
                    throw cfe;
                }
            }
        } catch (IOException e) {
            throw new ClassFileException(e);
        }
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
        for(VerificationTypeManager type : this.locals) {
            type.sync(instruction, pos);
        }
        for(VerificationTypeManager type : this.stack) {
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
        os.writeShort(locals.length);
        for(VerificationTypeManager type : locals) {
            type.write(os);
        }
        os.writeShort(stack.length);
        for(VerificationTypeManager type : stack) {
            type.write(os);
        }
    }

    @Override
    public String toString() {
        return "FullFrameManager{" +
                "offset=" + offset +
                ", locals=" + Arrays.toString(locals) +
                ", stack=" + Arrays.toString(stack) +
                '}';
    }
}
