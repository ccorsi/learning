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
import org.valhalla.plogger.instrumentation.bytecode.constantpool.ConstantUtf8;

import java.io.DataInputStream;
import java.io.DataOutput;
import java.io.IOException;
import java.util.Arrays;

public class FieldManager implements ClassFileWriter {

    private final int nameIndex;
    private final int accessFlags;
    private final int descriptorIndex;
    private final AttributeManager[] attributes;

    public FieldManager(ConstantPoolManager constantPoolManager, DataInputStream dis) {
        try {
            this.accessFlags = dis.readUnsignedShort();
            this.nameIndex = dis.readUnsignedShort();
            this.descriptorIndex = dis.readUnsignedShort();
            int size = dis.readUnsignedShort();
            this.attributes = new AttributeManager[size];
            for(int idx = 0 ; idx < size ; idx++) {
                try {
                    this.attributes[idx] = AttributeManagerFactory.create(dis, constantPoolManager);
                } catch (RuntimeException re) {
                    System.out.println("An exception was raised while processing attribute " + idx +
                            " out of " + size + " for field at index " + this.nameIndex);
                    throw re;
                }
            }
        } catch (IOException e) {
            throw new ClassFileException(e);
        }
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeShort(accessFlags);
        os.writeShort(nameIndex);
        os.writeShort(descriptorIndex);
        os.writeShort(attributes.length);
        for (AttributeManager attribute : attributes) {
            attribute.write(os);
        }
    }

    public String getName(ConstantPoolManager constantPoolManager) {
        ConstantUtf8 utf8 = constantPoolManager.getEntry(nameIndex);
        return utf8.getString();
    }

    @Override
    public String toString() {
        return "FieldManager{" +
                "nameIndex=" + nameIndex +
                ", accessFlags=" + accessFlags +
                ", descriptorIndex=" + descriptorIndex +
                ", attributes=" + Arrays.toString(attributes) +
                '}';
    }
}
