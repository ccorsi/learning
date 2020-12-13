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

public class TableSwitchInstruction extends AbstractInstruction {
    private static final int STACK_OPERAND_CHANGE = -1;

    private int pos;
    private int defaultPc;
    private final int lowPc;
    private final int highPc;
    private final int[] offsets;

    public TableSwitchInstruction(int pos, int defaultPc, int lowPc, int highPc, int[] offsets, InstructionEntry entry) {
        super(InstructionEntryFactory.TABLESWITCH, "TABLESWITCH", entry);
        this.pos = pos;
        this.defaultPc = defaultPc;
        this.lowPc = lowPc;
        this.highPc = highPc;
        this.offsets = offsets;
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
            int lowPc = dis.readInt();
            int highPc = dis.readInt();
            int[] pcs = new int[highPc - lowPc + 1];
            for (int idx = 0; idx < pcs.length; idx++) {
                pcs[idx] = dis.readInt();
            }
            return new TableSwitchInstruction(pos, defaultPc, lowPc, highPc, pcs, entry);
        } catch(IOException ioe) {
            throw new ClassFileException(ioe);
        }
    }

    @Override
    public int size() {
        int size = 1 + ( ( 3 + (highPc - lowPc + 1) ) * 4 );
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
    protected void sync() {
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

        for(int idx = 0 ; idx < this.offsets.length ; idx++) {
            addListenerForOffsetsOffset(idx);
        }
    }

    @Override
    public void update(int pos) {
        // Update this instruction position within the byte code array
        this.pos = pos;
        // forward the call to the super class
        super.update(pos);
    }

    private void addListenerForOffsetsOffset(final int idx) {
        AbstractInstruction instruction = getOffsetInstruction(offsets[idx]);

        if (offsets[idx] < 0) {
            addListener(new OffsetInstructionListener(instruction) {
                @Override
                protected void offset(int offset) {
                    offsets[idx] = 0;
                    offsets[idx] -= offset;
                }
            });
        } else {
            instruction.addListener(new OffsetInstructionListener(this) {
                @Override
                protected void offset(int offset) {
                    offsets[idx] = offset;
                }
            });
        }
    }

    @Override
    public String toString() {
        return "TableSwitchInstruction{" +
                "pos=" + pos +
                ", defaultPc=" + defaultPc +
                ", lowPc=" + lowPc +
                ", highPc=" + highPc +
                ", offsets=" + Arrays.toString(offsets) +
                '}';
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
        os.writeInt(lowPc);
        os.writeInt(highPc);
        for (int offset : offsets) {
            os.writeInt(offset);
        }
    }

}
