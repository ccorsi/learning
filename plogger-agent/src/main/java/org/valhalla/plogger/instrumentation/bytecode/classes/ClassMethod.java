package org.valhalla.plogger.instrumentation.bytecode.classes;

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

import org.valhalla.plogger.instrumentation.bytecode.attributes.ClassAttribute;
import org.valhalla.plogger.instrumentation.bytecode.attributes.ClassAttributeException;
import org.valhalla.plogger.instrumentation.bytecode.attributes.ClassAttributeFactory;
import org.valhalla.plogger.instrumentation.bytecode.attributes.CodeAttribute;
import org.valhalla.plogger.instrumentation.bytecode.constantpool.ConstantPoolEntry;
import org.valhalla.plogger.instrumentation.bytecode.constantpool.ConstantUtf8;

import java.io.DataInputStream;
import java.io.IOException;
import java.util.Arrays;

public class ClassMethod {
    private int accessFlags;
    private int nameIndex;
    private int descriptorIndex;
    private ClassAttribute[] attributes;

    private ClassMethod() {}

    public static ClassMethod load(ClassFile classFile, DataInputStream dis) throws IOException, ClassAttributeException, ClassFileException {
        ClassMethod method =  new ClassMethod();
        method.accessFlags = dis.readUnsignedShort();
        method.nameIndex = dis.readUnsignedShort();
        method.descriptorIndex = dis.readUnsignedShort();
        int count = dis.readUnsignedShort();
        method.attributes = new ClassAttribute[count];
        for (int idx = 0 ; idx < count ; idx++) {
            method.attributes[idx] = ClassAttributeFactory.load(classFile, dis);
        }
        return method;
    }

    @Override
    public String toString() {
        return "ClassMethod{" +
                "accessFlags=" + accessFlags +
                ", nameIndex=" + nameIndex +
                ", descriptorIndex=" + descriptorIndex +
                ", attributes=" + Arrays.toString(attributes) +
                '}';
    }

    public CodeAttribute getCode() {
        for (ClassAttribute attribute : attributes) {
            if (attribute instanceof CodeAttribute) {
                return (CodeAttribute) attribute;
            }
        }
        return null;
    }

    public String getName(ClassFile classFile) {
        ConstantPoolEntry[] cpool = classFile.getConstantPool();
        ConstantPoolEntry entry = cpool[nameIndex];
        if (entry instanceof ConstantUtf8) {
            ConstantUtf8 utf8 = (ConstantUtf8) entry;
            return utf8.getString();
        }
        return "n/a";
    }
}
