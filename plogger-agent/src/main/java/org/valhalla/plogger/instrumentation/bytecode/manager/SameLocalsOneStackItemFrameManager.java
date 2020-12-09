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

import org.valhalla.plogger.instrumentation.bytecode.attributes.VerificationType;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileException;

import java.io.DataOutput;
import java.io.IOException;

// TODO: This stack map frame needs to be notified whenever the associated
//  instruction was updated.
public class SameLocalsOneStackItemFrameManager implements StackMapFrameManager {
    private int frameType;
    private final VerificationTypeManager verificationTypeManager;

    public SameLocalsOneStackItemFrameManager(int frameType, VerificationTypeManager verificationTypeManager) {
        this.frameType = frameType;
        this.verificationTypeManager = verificationTypeManager;
    }

    public SameLocalsOneStackItemFrameManager(int frameType, VerificationType verificationType) {
        this.frameType = frameType;
        this.verificationTypeManager = VerificationTypeManagerFactory.convert(verificationType);
    }

    @Override
    public int offset() {
        return frameType;
    }

    @Override
    public void setOffset(int offset) {
        if (offset > 63) {
            // SameLocals1StackItemFrameExtended stack map frame
            frameType = offset;
        } else {
            // SameLocals1StackItemExtended stack map frame
            frameType = offset + 64;
        }
    }

    @Override
    public void sync(AbstractInstruction instruction, int pos) {
        this.verificationTypeManager.sync(instruction, pos);
    }

    @Override
    public void write(DataOutput os) throws IOException {
        if (frameType < 128) {
            // store a SameLocals1StackItemFrame stack map frame
            os.write(frameType);
            verificationTypeManager.write(os);
        } else {
            // store a SameLocals1StackItemFrameExtended stack map frame
            os.write(247);
            os.writeShort(frameType);  // This is now the offset
            verificationTypeManager.write(os);
        }
    }

    @Override
    public String toString() {
        return "SameLocalsOneStackItemFrameManager{" +
                "frameType=" + frameType +
                ", verificationTypeManager=" + verificationTypeManager +
                '}';
    }
}
