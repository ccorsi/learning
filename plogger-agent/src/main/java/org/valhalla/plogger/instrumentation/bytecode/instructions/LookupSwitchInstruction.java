package org.valhalla.plogger.instrumentation.bytecode.instructions;
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
import org.valhalla.plogger.instrumentation.bytecode.manager.OffsetInstructionListener;

import java.io.DataInputStream;
import java.io.DataOutput;
import java.io.IOException;
import java.util.Arrays;

public class LookupSwitchInstruction extends AbstractInstruction {
    private static final int STACK_OPERAND_CHANGE = -1;
    public static final int LOOKUP_MATCH = 0;
    public static final int LOOKUP_OFFSET = 1;

    private int pos;
    private int defaultPc;
    private final int[][] npairs;

    public LookupSwitchInstruction(int pos, int defaultPc, int[][] npairs, InstructionEntry entry) {
        super(InstructionEntryFactory.LOOKUPSWITCH, "LOOKUPSWITCH", entry);
        this.pos = pos;
        this.defaultPc = defaultPc;
        this.npairs = npairs;
    }

    public static InstructionEntry create(DataInputStream dis, int pos, InstructionEntry entry) {
        try {
            int temp = pos;
            int pad = 0;
            while ((pos + pad + 1) % 4 != 0) {
                dis.read(); // read non-required byte
                pad++; // increment padding length.
            }
            int defaultPc = dis.readInt();
            int npairCount = dis.readInt();
            int[][] npairs = new int[npairCount][2];
            for(int idx = 0 ; idx < npairs.length ; idx++) {
                npairs[idx][LOOKUP_MATCH] = dis.readInt(); // match
                npairs[idx][LOOKUP_OFFSET] = dis.readInt(); // offset
            }
            return new LookupSwitchInstruction(pos, defaultPc, npairs, entry);
        } catch(IOException ioe) {
            throw new ClassFileException(ioe);
        }
    }

    @Override
    public int size() {
        int size = 1 + ( 8 * ( npairs.length + 1  ) );
        for(int pc = pos + 1 ; pc % 4 != 0 ; pc++) {
            size++;
        }
        return size;
    }

    @Override
    public int stack() {
        return STACK_OPERAND_CHANGE;
    }

    @Override
    public void sync() {
        AbstractInstruction instruction = getOffsetInstruction(defaultPc);

        if (defaultPc < 0) {
            addListener(new OffsetInstructionListener(instruction) {
                @Override
                protected void offset(int offset) {
                    defaultPc = 0;
                    defaultPc -= offset;
                }
            });
        } else {
            instruction.addListener(new OffsetInstructionListener(this) {
                @Override
                protected void offset(int offset) {
                    defaultPc = offset;
                }
            });
        }

        for(int idx = 0 ; idx < this.npairs.length ; idx++) {
            addListenerForNPairsOffset(idx);
        }
    }

    @Override
    public void update(int pos) {
        // Update this instruction position within the byte code array
        this.pos = pos;
        super.update(pos);
    }

    private void addListenerForNPairsOffset(final int idx) {
        AbstractInstruction instruction = getOffsetInstruction(npairs[idx][LOOKUP_OFFSET]);

        if (npairs[idx][LOOKUP_OFFSET] < 0) {
            addListener(new OffsetInstructionListener(instruction) {
                @Override
                protected void offset(int offset) {
                    npairs[idx][LOOKUP_OFFSET] = 0;
                    npairs[idx][LOOKUP_OFFSET] -= offset;
                }
            });
        } else {
            instruction.addListener(new OffsetInstructionListener(this) {
                @Override
                protected void offset(int offset) {
                    npairs[idx][LOOKUP_OFFSET] = offset;
                }
            });
        }
    }

    @Override
    public String toString() {
        return "LookupSwitchInstruction{" +
                "pos=" + pos +
                ", defaultPc=" + defaultPc +
                ", npairs=" + toNPairs() +
                '}';
    }

    private String toNPairs() {
        StringBuilder sb = new StringBuilder();
        sb.append('[');

        if (npairs.length > 0) {
            sb.append(Arrays.toString(npairs[0]));
            for(int idx = 1 ; idx < npairs.length ; idx++) {
                sb.append(", ").append(Arrays.toString(npairs[idx]));
            }
        }
        sb.append(']');
        return sb.toString();
    }

    @Override
    public void write(DataOutput os) throws IOException {
        super.write(os);
        // Add the required padding to insure that the next part of the instruction is on a multiple of four as part
        // of the byte code array.
        for(int cnt = pos + 1 ; (cnt % 4) != 0 ; cnt++) {
            os.write(0);
        }
        os.writeInt(defaultPc);
        os.writeInt(npairs.length);
        for( int[] npair : npairs ) {
            os.writeInt(npair[LOOKUP_MATCH]);
            os.writeInt(npair[LOOKUP_OFFSET]);
        }
    }
}
