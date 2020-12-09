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

import org.valhalla.plogger.instrumentation.bytecode.attributes.DefaultAttribute;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileException;

import java.io.DataOutput;
import java.io.IOException;
import java.util.Arrays;

/**
 * This class will only store attribute data to manage attributes that
 * don't require to be updated within a class structure.  This can
 * include any of the class, field, method, and code structures of the
 * class file.
 */
public class DefaultAttributeManager implements AttributeManager {
    private final int nameIndex;
    private final byte[] data;

    /**
     * @param nameIndex An index to the constant pool of the name of this attribute
     * @param data The actual data that is used to define the attribute.
     */
    public DefaultAttributeManager(int nameIndex, byte[] data) {
        this.nameIndex = nameIndex;
        this.data = data;
    }

    public DefaultAttributeManager(DefaultAttribute defaultAttribute) {
        this.nameIndex = defaultAttribute.getNameIndex();
        this.data = defaultAttribute.getData();
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeShort(nameIndex);
        os.writeInt(data.length);
        os.write(data);
    }

    @Override
    public String toString() {
        return "DefaultAttributeManager{" +
                "nameIndex=" + nameIndex +
                ", data=" + Arrays.toString(data) +
                '}';
    }
}
