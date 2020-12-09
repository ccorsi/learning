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

import org.valhalla.plogger.instrumentation.bytecode.attributes.CodeExceptionTable;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileException;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileWriter;

import java.io.DataInputStream;
import java.io.DataOutput;
import java.io.IOException;
import java.util.Arrays;
import java.util.Collection;
import java.util.Iterator;

public class ExceptionTableManager implements ClassFileWriter {
    private final ExceptionTableEntryManager[] entries;

    public ExceptionTableManager(Collection<CodeExceptionTable> exceptionTables) {
        this.entries = new ExceptionTableEntryManager[exceptionTables.size()];
        Iterator<CodeExceptionTable> iterator = exceptionTables.iterator();
        for (int idx = 0 ; idx < entries.length ; idx++) {
            CodeExceptionTable entry = iterator.next();
            entries[idx] = new ExceptionTableEntryManager(entry);
        }
    }

    public ExceptionTableManager(DataInputStream dis) {
        try {
            int size = dis.readUnsignedShort();
            entries = new ExceptionTableEntryManager[size];
            for (int idx = 0; idx < size; idx++) {
                int startPcs = dis.readUnsignedShort();
                int endPcs = dis.readUnsignedShort();
                int handlePcs = dis.readUnsignedShort();
                int catchTypes = dis.readUnsignedShort();
                entries[idx] = new ExceptionTableEntryManager(startPcs, endPcs, handlePcs, catchTypes);
            }
        } catch (Throwable t) {
            throw new ClassFileException(t);
        }
    }

    public void sync(AbstractInstruction instruction, int pos) {
        for(ExceptionTableEntryManager entry : entries) {
            entry.sync(instruction, pos);
        }
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeShort(entries.length);
        for (ExceptionTableEntryManager entry : entries) {
            entry.write(os);
        }
    }

    @Override
    public String toString() {
        return "ExceptionTableManager{" +
                "entries=" + Arrays.toString(entries) +
                '}';
    }
}
