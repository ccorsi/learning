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
import org.valhalla.plogger.instrumentation.bytecode.constantpool.*;

import java.io.*;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class ConstantPoolManager implements Iterable<ConstantPoolEntry>, ClassFileWriter {
    private ConstantPoolEntry[] constantPool;
    private boolean debug;

    public ConstantPoolManager(DataInputStream dis) {
        int idx = 1;
        try {
            int constant_pool_count = dis.readUnsignedShort();
            constantPool = new ConstantPoolEntry[constant_pool_count];
            for(  ; idx < constant_pool_count ; ) {
                constantPool[idx] = ConstantPoolEntryFactory.create(dis);
                idx += constantPool[idx].entries();
            }
        } catch (IOException | ConstantPoolEntryException e) {
            // TODO: Combine the exception and message
            System.out.println("Invalid constant pool entry: " + idx);
            throw new ClassFileException(e);
        }
    }

    // This will create a ConstantString and ConstantUtf if required.
    public ConstantString getStringEntry(String name) {
        for (ConstantPoolEntry entry : constantPool) {
            if (entry instanceof ConstantString) {
                ConstantString constantString = (ConstantString) entry;
                ConstantUtf8 utf8 = (ConstantUtf8) constantPool[constantString.getStringIndex()];
                if (name.equals(utf8.getString())) {
                    return constantString;
                }
            }
        }
        // Create a new ConstantString entry and add to the constant pool
        ConstantUtf8 constantUtf8 = getUtf8Entry(name);
        ConstantString constantString = new ConstantString(getEntryIndex(constantUtf8));
        addConstantPoolEntry(constantString);

        return constantString;
    }

    // This will create a ConstantClass and ConstantUtf8 if required.
    public ConstantClass getClassEntry(String name) throws ConstantPoolEntryException {
        for (ConstantPoolEntry entry : constantPool) {
            if (entry instanceof ConstantClass) {
                ConstantClass constantClass = (ConstantClass) entry;
                if (name.equals(constantClass.getClassName(constantPool))) {
                    return constantClass;
                }
            }
        }
        // Create a new ConstantClass entry and add to the ConstantPool
        ConstantUtf8 constantUtf8 = getUtf8Entry(name);
        ConstantClass constantClass = new ConstantClass(getEntryIndex(constantUtf8));
        addConstantPoolEntry(constantClass);

        return constantClass;
    }

    // This will create a ConstantMethodRef entry and its dependent Constant Pool
    // entries if they don't exist
    public ConstantMethodRef getMethodRefEntry(String className, String name, String signature) throws ConstantPoolEntryException {
        for (ConstantPoolEntry entry : constantPool) {
            if (entry instanceof ConstantMethodRef) {
                ConstantMethodRef constantMethodRef = (ConstantMethodRef) entry;
                ConstantClass constantClass = (ConstantClass) constantPool[constantMethodRef.getClassIndex()];
                ConstantUtf8 constantUtf8 = (ConstantUtf8) constantPool[constantClass.getNameIndex()];
                if (className.equals(constantUtf8.getString())) {
                    ConstantNameAndType constantNameAndType = (ConstantNameAndType) constantPool[constantMethodRef.getNameAndTypeIndex()];
                    ConstantUtf8 constantName = (ConstantUtf8) constantPool[constantNameAndType.getNameIndex()];
                    if (name.equals(constantName.getString())) {
                        ConstantUtf8 constantDescriptor = (ConstantUtf8) constantPool[constantNameAndType.getDescriptorIndex()];
                        if (signature.equals(constantDescriptor.getString())) {
                            return constantMethodRef;
                        }
                    }
                }
            }
        }
        // Create a ConstantClass and ConstantNameAndType constant pool entry
        ConstantClass constantClass = getClassEntry(className);
        ConstantNameAndType constantNameAndType = getNameAndTypeEntry(name, signature);
        ConstantMethodRef constantMethodRef = new ConstantMethodRef(getEntryIndex(constantClass),
                getEntryIndex(constantNameAndType));
        addConstantPoolEntry(constantMethodRef);

        return constantMethodRef;
    }

    // This will create a ConstantNameAndType entry and its dependent Constant Pool
    // entries if they don't exist
    public ConstantNameAndType getNameAndTypeEntry(String name, String signature) {
        for (ConstantPoolEntry entry : constantPool) {
            if (entry instanceof ConstantNameAndType) {
                ConstantNameAndType constantNameAndType = (ConstantNameAndType) entry;
                ConstantUtf8 constantName = (ConstantUtf8) constantPool[constantNameAndType.getNameIndex()];
                if (name.equals(constantName.getString())) {
                    ConstantUtf8 constantDescriptor = (ConstantUtf8) constantPool[constantNameAndType.getDescriptorIndex()];
                    if (signature.equals(constantDescriptor.getString())) {
                        return constantNameAndType;
                    }
                }
            }
        }
        ConstantUtf8 constantName = getUtf8Entry(name);
        ConstantUtf8 constantDescriptor = getUtf8Entry(signature);
        ConstantNameAndType constantNameAndType = new ConstantNameAndType(getEntryIndex(constantName),
                getEntryIndex(constantDescriptor));
        addConstantPoolEntry(constantNameAndType);

        return constantNameAndType;
    }

    // This will create a ConstantUtf8 entry if it doesn't exist
    public ConstantUtf8 getUtf8Entry(String name) {
        for (ConstantPoolEntry entry : constantPool) {
            if (entry instanceof ConstantUtf8) {
                ConstantUtf8 constantUtf8 = (ConstantUtf8) entry;
                if (name.equals(constantUtf8.getString()))
                    return constantUtf8;
            }
        }
        // Create a ConstantUtf8 entry and add to the Constant Pool
        byte[] bytes = name.getBytes();
        ConstantUtf8 constantUtf8 = new ConstantUtf8(bytes.length, bytes);
        addConstantPoolEntry(constantUtf8);

        return constantUtf8;
    }

    public int getEntryIndex(ConstantPoolEntry entry) {
        for(int idx = 1 ; idx < this.constantPool.length ; idx++) {
            if (constantPool[idx] == entry) {
                return idx;
            }
        }
        throw new NoSuchElementException("Unable to find constant pool entry: " + entry);
    }

    private void addConstantPoolEntry(ConstantPoolEntry entry) {
        int size = entry.entries();
        ConstantPoolEntry[] newConstantPool = new ConstantPoolEntry[constantPool.length + size];
        System.arraycopy(constantPool,0,newConstantPool,0, constantPool.length);
        newConstantPool[constantPool.length] = entry;
        constantPool = newConstantPool;

        if (debug) {
            System.out.println("Updated Constant Pool Entry Table Start");
            for(int idx = 1 ; idx < constantPool.length ; idx++) {
                System.out.println("Entry " + idx + " = " + constantPool[idx]);
            }
            System.out.println("Updated Constant Pool Entry Table End");
        }
    }

    @Override
    public Iterator<ConstantPoolEntry> iterator() {
        return new Iterator<ConstantPoolEntry>() {
            final ConstantPoolEntry[] entries = ConstantPoolManager.this.constantPool;
            int idx = 1;

            @Override
            public boolean hasNext() {
                return idx < entries.length;
            }

            @Override
            public ConstantPoolEntry next() {
                if (! hasNext()) {
                    throw new NoSuchElementException("No elements remaining");
                }

                ConstantPoolEntry entry = entries[idx];
                idx += entry.entries();

                return entry;
            }

            @Override
            public void remove() {
                // do nothing.
            }
        };
    }

    @SuppressWarnings("unchecked cast")
    public <E extends ConstantPoolEntry> E getEntry(int index) {
        if (index < constantPool.length && constantPool[index] != null) {
            return (E) constantPool[index];
        }
        throw new NoSuchElementException("No Constant Pool Entry found for index: " + index);
    }

    @SuppressWarnings("unused")
    public void debug() {
        this.debug = true;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeShort(constantPool.length);
        for(int idx = 1 ; idx < constantPool.length ; ) {
            constantPool[idx].write(os);
            idx += constantPool[idx].entries();
        }
    }
}
