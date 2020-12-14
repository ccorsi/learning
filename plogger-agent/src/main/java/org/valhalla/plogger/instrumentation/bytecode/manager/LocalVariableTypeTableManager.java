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
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileWriter;

import java.io.DataInputStream;
import java.io.DataOutput;
import java.io.IOException;
import java.util.Arrays;

public class LocalVariableTypeTableManager implements AttributeManager {
    private final int nameIndex;
    private final LocalVariableTypeTableEntryManager[] entries;

    public LocalVariableTypeTableManager(int nameIndex, DataInputStream dis) {
        this.nameIndex = nameIndex;
        try {
            int size = dis.readUnsignedShort();
            this.entries = new LocalVariableTypeTableEntryManager[size];
            for(int idx = 0 ; idx < entries.length ; idx++) {
                int startPc = dis.readUnsignedShort();
                int length = dis.readUnsignedShort();
                nameIndex = dis.readUnsignedShort();
                int signatureIndex = dis.readUnsignedShort();
                int index = dis.readUnsignedShort();
                entries[idx] = new LocalVariableTypeTableEntryManager(startPc, length, nameIndex, signatureIndex,
                        index);
            }
        } catch(IOException ioe) {
            throw new ClassFileException(ioe);
        }
    }

    public void sync(AbstractInstruction instruction, int pos) {
        for(LocalVariableTypeTableEntryManager entry : entries) {
            entry.sync(instruction, pos);
        }
    }

    @Override
    public String toString() {
        return "LocalVariableTypeTableManager{" +
                "nameIndex=" + nameIndex +
                ", entries=" + Arrays.toString(entries) +
                '}';
    }

    // TODO: The startPc and length will need to be updated whenever that instruction
    //   has moved from it original position.
    private class LocalVariableTypeTableEntryManager implements ClassFileWriter {
        private final int index;
        private int startPc;
        private int length;
        private final int nameIndex;
        private final int signatureIndex;

        public LocalVariableTypeTableEntryManager(int startPc, int length, int nameIndex, int signatureIndex, int index) {
            this.startPc = startPc;
            this.length = length;
            this.nameIndex = nameIndex;
            this.signatureIndex = signatureIndex;
            this.index = index;
        }

        public int getStartPc() {
            return startPc;
        }

        public int getLength() {
            return length;
        }

        public int getNameIndex() {
            return nameIndex;
        }

        public int getSignatureIndex() {
            return signatureIndex;
        }

        public void sync(AbstractInstruction instruction, int pos) {
            if (startPc != 0 && pos == startPc) {
                instruction.addListener(new InstructionListener() {
                    public void event(InstructionEntry instruction, int newPos) {
                        // update the startPc
                        startPc = newPos;
                    }
                });
            } else if (pos == (startPc + length)) {
                // The length can be updated because of instructions like lookupswitch and tableswitch
                instruction.addListener(new InstructionListener() {
                    public void event(InstructionEntry instruction, int newPos) {
                        // Update new position
                        length = newPos - startPc;
                    }
                });
            }
        }

        @Override
        public void write(DataOutput os) throws IOException {
            os.writeShort(startPc);
            os.writeShort(length);
            os.writeShort(nameIndex);
            os.writeShort(signatureIndex);
            os.writeShort(index);
        }

        @Override
        public String toString() {
            return "LocalVariableTypeTableEntryManager{" +
                    "index=" + index +
                    ", startPc=" + startPc +
                    ", length=" + length +
                    ", nameIndex=" + nameIndex +
                    ", signatureIndex=" + signatureIndex +
                    '}';
        }
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeShort(nameIndex);
        os.writeInt(2 + ( 10 * entries.length ) );
        os.writeShort(entries.length);
        for (LocalVariableTypeTableEntryManager entry : entries) {
            entry.write(os);
        }
    }
}
