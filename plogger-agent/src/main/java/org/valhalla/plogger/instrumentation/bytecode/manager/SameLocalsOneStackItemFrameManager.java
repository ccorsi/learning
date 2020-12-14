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

import org.valhalla.plogger.instrumentation.bytecode.instructions.AbstractInstruction;

import java.io.DataOutput;
import java.io.IOException;

public class SameLocalsOneStackItemFrameManager implements StackMapFrameManager {
    private int offset;
    private final VerificationTypeManager verificationTypeManager;
    private boolean debug = Boolean.getBoolean(StackMapTableManager.DEBUG_PROPERTY_NAME);

    public SameLocalsOneStackItemFrameManager(int offset, VerificationTypeManager verificationTypeManager) {
        // The passed offset if the *real* offset and not the frameType
        // SameLocal1StackItemFrame stack map frame
        // SameLocal1StackItemFrameExtended stack map frame
        this.offset = offset;
        this.verificationTypeManager = verificationTypeManager;
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
        this.verificationTypeManager.sync(instruction, pos);
    }

    @Override
    public void write(DataOutput os) throws IOException {
        if (debug) {
            System.out.println(this);
        }
        if (offset < 64) {
            // store a SameLocals1StackItemFrame stack map frame
            os.write(offset + 64);
            verificationTypeManager.write(os);
        } else {
            // store a SameLocals1StackItemFrameExtended stack map frame
            os.write(247);
            os.writeShort(offset);  // This is now the offset
            verificationTypeManager.write(os);
        }
    }

    @Override
    public String toString() {
        return "SameLocalsOneStackItemFrameManager{" +
                "frameType=" + offset +
                ", verificationTypeManager=" + verificationTypeManager +
                '}';
    }
}
