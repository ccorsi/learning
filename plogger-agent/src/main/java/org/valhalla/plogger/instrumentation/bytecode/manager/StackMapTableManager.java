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
import org.valhalla.plogger.instrumentation.bytecode.instructions.AbstractInstruction;
import org.valhalla.plogger.instrumentation.bytecode.instructions.InstructionEntry;
import org.valhalla.plogger.instrumentation.bytecode.instructions.InstructionListener;

import java.io.ByteArrayOutputStream;
import java.io.DataInputStream;
import java.io.DataOutput;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.Arrays;

public class StackMapTableManager implements AttributeManager {
    public static final String DEBUG_PROPERTY_NAME = "stack.map.table.debug";
    private final int nameIndex;
    private final StackMapFrameManager[] frameManagers;
    private int frameIdx;
    private int framePos;
    private AbstractInstruction priorInstruction;
    private boolean debug = Boolean.getBoolean(DEBUG_PROPERTY_NAME);

    public StackMapTableManager(int nameIndex, DataInputStream dis) {
        this.nameIndex = nameIndex;
        try {
            int size = dis.readUnsignedShort();
            frameManagers = new StackMapFrameManager[size];
            for(int idx = 0 ; idx < frameManagers.length ; idx++) {
                try {
                    frameManagers[idx] = StackMapFrameManagerFactory.create(dis);
                } catch (ClassFileException cfe) {
//                    System.out.println("Exception was raised when creating StackMapFrame: " + idx);
//                    for(int cnt = 0 ; cnt < idx ; cnt++) {
//                        System.out.println(frameManagers[cnt]);
//                    }
                    throw cfe;
                }
            }
        } catch(IOException e) {
            throw new ClassFileException(e);
        }
        frameIdx = 0;
        framePos = frameManagers[frameIdx].offset();
        priorInstruction = null;
//        System.out.println("FIRST STACK MAP FRAME: " + frameManagers[frameIdx]);
    }

    public void sync(AbstractInstruction instruction, int pos) {
        if (framePos == pos) {
            if (debug) {
                System.out.println("Adding StackMapFrameListener for pos " + pos + " at instruction " + instruction);
            }
            StackMapFrameListener listener = new StackMapFrameListener(framePos, frameIdx, priorInstruction);
            instruction.addListener(listener);
            priorInstruction = instruction;
            // increment the framePos to point to the next frame
            frameIdx++;
            if (frameIdx < frameManagers.length) {
                framePos += 1 + frameManagers[frameIdx].offset();
                if (debug) {
                    System.out.println(String.format("frameIdx: %d, framePos: %d - %s", frameIdx, framePos,
                            frameManagers[frameIdx]));
                }
            }
        } if (frameIdx < frameManagers.length && pos > framePos) {
            throw new ClassFileException(String.format("Unable to find stack map frame at position %s for frame %s",
                    framePos, frameManagers[frameIdx]));
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
        private final int framePos;

        public StackMapFrameListener(int framePos, int frameIndex, AbstractInstruction priorFrameInstruction) {
            this.framePos = framePos;
            this.frameIndex = frameIndex;
            this.priorFrameInstruction = priorFrameInstruction;
        }

        @Override
        public void event(final InstructionEntry instruction, int newPos) {
            int offset = 0;
            if (priorFrameInstruction == null) {
                // We are in the first stack map frame
                AbstractInstruction instr = (AbstractInstruction) instruction;
                for (instr = instr.getPrior() ; instr != null ; instr = instr.getPrior()) {
                    offset += instr.size();
                }
            } else {
                // This is not the first stack map frame
                for (AbstractInstruction instr = priorFrameInstruction ;
                     instr != instruction ; instr = instr.getNext()) {
                    offset += instr.size();
                }
                offset--;
            }
            if (debug) {
                System.out.println("offset: " + offset + " from " + priorFrameInstruction + " to " + instruction);
            }
            // check that the offset is correct, if not update stack map frame
            if (frameManagers[frameIndex].offset() != offset) {
                if (debug) {
                    System.out.println("Updating offset " + offset + " for Stack Map Frame "
                            + frameManagers[frameIndex]);
                }
                frameManagers[frameIndex].setOffset(offset);
                if (debug) {
                    System.out.println("to Stack Map Frame " + frameManagers[frameIndex]);
                }
            }
        }

        @Override
        public String toString() {
            return "StackMapFrameListener{" +
                    "frameIndex=" + frameIndex +
                    ", priorFrameInstruction=" + priorFrameInstruction +
                    '}';
        }
    }

    @Override
    public void write(DataOutput os) throws IOException {
        if (debug) {
            System.out.println("Storing StackMapTable");
            System.out.println(this);
        }
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
