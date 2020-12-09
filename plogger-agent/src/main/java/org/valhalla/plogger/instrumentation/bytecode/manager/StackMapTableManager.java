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

import org.valhalla.plogger.instrumentation.bytecode.attributes.StackMapFrame;
import org.valhalla.plogger.instrumentation.bytecode.attributes.StackMapTable;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileException;

import java.io.*;
import java.util.Arrays;
import java.util.List;

public class StackMapTableManager implements AttributeManager {
    private final int nameIndex;
    private final StackMapFrameManager[] frameManagers;
    private int frameIdx;
    private int framePos;
    private AbstractInstruction priorInstruction;

    public StackMapTableManager(StackMapTable stackMapTable) {
        // Deals with the case that the original method code attribute
        // does not contain a StackMapTable for whatever reason.
        nameIndex = stackMapTable.getNameIndex();
        List<StackMapFrame> frames = stackMapTable.getStackFrames();
        frameManagers = new StackMapFrameManager[frames.size()];
        for(int idx = 0 ; idx < frameManagers.length ; idx++) {
            frameManagers[idx] = StackMapFrameManagerFactory.create(frames.get(idx));
        }
        frameIdx = 0;
        framePos = frameManagers[frameIdx].offset();
        priorInstruction = null;
    }

    public StackMapTableManager(int nameIndex, DataInputStream dis) {
        // TODO: Implement constructor.
        this.nameIndex = nameIndex;
        try {
            int size = dis.readUnsignedShort();
            frameManagers = new StackMapFrameManager[size];
            for(int idx = 0 ; idx < frameManagers.length ; idx++) {
                frameManagers[idx] = StackMapFrameManagerFactory.create(dis);
            }
        } catch(IOException e) {
            throw new ClassFileException(e);
        }
    }

    public void sync(AbstractInstruction instruction, int pos) {
        if (framePos == pos) {
            StackMapFrameListener listener = new StackMapFrameListener(frameIdx, priorInstruction, instruction);
            if (priorInstruction != null) {
                priorInstruction.addListener(listener);
            }
            instruction.addListener(listener);
            priorInstruction = instruction;
            // increment the framePos to point to the next frame
            frameIdx++;
            if (frameIdx < frameManagers.length) {
                framePos += 1 + frameManagers[frameIdx].offset();
            }
        }
        for(StackMapFrameManager frame : frameManagers) {
            // All this just to be able to sync the Uninitialized variable info verification type!
            frame.sync(instruction, pos);
        }
    }

    @Override
    public String toString() {
        return "StackMapTableManager{" +
                "nameIndex=" + nameIndex +
                ", frameManagers=" + Arrays.toString(frameManagers) +
                '}';
    }

    private class StackMapFrameListener implements InstructionListener {

        private final int frameIndex;
        private final AbstractInstruction priorFrameInstruction;
        private final AbstractInstruction frameInstruction;
        private int priorFramePos;

        public StackMapFrameListener(int frameIndex, AbstractInstruction priorFrameInstruction,
                                     AbstractInstruction frameInstruction) {
            this.frameIndex = frameIndex;
            this.priorFrameInstruction = priorFrameInstruction;
            this.frameInstruction = frameInstruction;
            this.priorFramePos = 0;
        }

        @Override
        public void event(InstructionEntry instruction, int newPos) {
            if (instruction == priorFrameInstruction) {
                // store start frame position
                priorFramePos = newPos;
            } else if (instruction == frameInstruction) {
                if (priorFramePos == 0) {
                    // This is the first frame so we don't add 1 to the offset check
                    if ((priorFramePos + frameManagers[frameIndex].offset()) != newPos) {
                        frameManagers[frameIndex].setOffset(newPos);
                    }
                } else {
                    // check that the offset is correct, if not update stack map frame
                    if ((priorFramePos + frameManagers[frameIndex].offset() + 1) != newPos) {
                        int offset = newPos - priorFramePos - 1;
                        frameManagers[frameIndex].setOffset(offset);
                    }
                }
            }
        }

        @Override
        public String toString() {
            return "StackMapFrameListener{" +
                    "frameIndex=" + frameIndex +
                    ", priorFrameInstruction=" + priorFrameInstruction +
                    ", frameInstruction=" + frameInstruction +
                    ", priorFramePos=" + priorFramePos +
                    '}';
        }
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeShort(nameIndex);
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        try(DataOutputStream dos = new DataOutputStream(bos)) {
            dos.writeShort(frameManagers.length);
            for (StackMapFrameManager frame : frameManagers) {
                frame.write(dos);
            }
        }
        byte[] data = bos.toByteArray();
        os.writeInt(data.length);
        os.write(data);
    }
}
