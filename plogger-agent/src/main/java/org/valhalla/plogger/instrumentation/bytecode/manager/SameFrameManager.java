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

import org.valhalla.plogger.instrumentation.Debug;
import org.valhalla.plogger.instrumentation.bytecode.instructions.AbstractInstruction;

import java.io.DataOutput;
import java.io.IOException;

/**
 * This Same Frame Manager will manage the manipulation of the Same Frame
 * and Same Frame Extended stack map table frame entries.  This is required
 * since it is possible that the addition of instructions can cause the
 * Same Frame stack map entry to become a Same Frame Extended stack map
 * table entry.
 */
public class SameFrameManager implements StackMapFrameManager {
    // values 0-63 are SameFrame while value greater than 63 are SameFrameExtended
    private int frameType;
    private static final Debug debug = Debug.getDebug("stackmapframe");

    public SameFrameManager(int frameType) {
        this.frameType = frameType;
    }

    @Override
    public int offset() {
        return frameType;
    }

    @Override
    public void setOffset(int offset) {
        this.frameType = offset;
    }

    @Override
    public void sync(AbstractInstruction instruction, int pos) {
        // nothing to do....
    }

    @Override
    public void write(DataOutput os) throws IOException {
        if (debug.isDebug()) {
            debug.debug(String.format("Storing %s", toString()));
        }
        if (frameType < 64) {
            // Store a SameFrame stack map frame
            os.write(frameType);
        } else {
            // Store a SameFrameExtended stack map frame
            os.write(251);
            os.writeShort(frameType);  // This is the offset
        }
    }

    @Override
    public String toString() {
        return "SameFrameManager{" +
                "frameType=" + frameType +
                '}';
    }
}
