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

public class LineNumberTableManager implements AttributeManager {
    private final int nameIndex;
    private final LineNumberTableEntryManager[] entries;

    public LineNumberTableManager(int nameIndex, DataInputStream dis) {
        try {
            this.nameIndex = nameIndex;
            int size = dis.readShort();
            this.entries = new LineNumberTableEntryManager[size];
            for (int idx = 0; idx < entries.length; idx++) {
                int startPc = dis.readShort();
                int lineNumber = dis.readShort();
                entries[idx] = new LineNumberTableEntryManager(startPc, lineNumber);
            }
        } catch(IOException ioe) {
            throw new ClassFileException(ioe);
        }
    }

    public int getNameIndex() {
        return nameIndex;
    }

    public LineNumberTableEntryManager[] getEntries() {
        return entries;
    }

    @Override
    public String toString() {
        return "LineNumberTableManager{" +
                "nameIndex=" + nameIndex +
                ", entries=" + Arrays.toString(entries) +
                '}';
    }

    // TODO: This class needs to be notified if the startPc instruction is being
    //  moved to a different position in the byte code array.
    private class LineNumberTableEntryManager implements ClassFileWriter {
        private int startPc;
        private final int lineNumber;

        public LineNumberTableEntryManager(int startPc, int lineNumber) {
            this.startPc = startPc;
            this.lineNumber = lineNumber;
        }

        @Override
        public void write(DataOutput os) throws IOException {
            os.writeShort(startPc);
            os.writeShort(lineNumber);
        }

        @Override
        public String toString() {
            return "LineNumberTableEntryManager{" +
                    "startPc=" + startPc +
                    ", lineNumber=" + lineNumber +
                    '}';
        }
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeShort(nameIndex);
        os.writeInt(2 + 4 * entries.length);
        os.writeShort(entries.length);
        for(LineNumberTableEntryManager entry : entries) {
            entry.write(os);
        }
    }
}
