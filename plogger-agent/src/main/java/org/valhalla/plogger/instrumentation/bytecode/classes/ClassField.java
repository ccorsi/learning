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

import java.io.DataInputStream;
import java.io.IOException;
import java.util.Arrays;

public class ClassField {

    private final ClassFile classFile;
    private int accessFlags;
    private int nameIndex;
    private int descriptionIndex;
    private ClassAttribute[] attributes;

    private ClassField(ClassFile classFile) { this.classFile = classFile; }

    public static ClassField load(ClassFile classFile, DataInputStream dis) throws IOException, ClassAttributeException, ClassFileException {
        ClassField field = new ClassField(classFile);
        field.accessFlags = dis.readUnsignedShort();
        field.nameIndex = dis.readUnsignedShort();
        field.descriptionIndex = dis.readUnsignedShort();
        int count = dis.readUnsignedShort();
        field.attributes = new ClassAttribute[count];
        for(int idx = 0 ;  idx < count ; idx++) {
            field.attributes[idx] = ClassAttributeFactory.load(classFile, dis);
        }
        return field;
    }

    @Override
    public String toString() {
        return "ClassField{" +
                "accessFlags=" + accessFlags +
                ", nameIndex=" + nameIndex +
                ", descriptionIndex=" + descriptionIndex +
                ", attributes=" + Arrays.toString(attributes) +
                '}';
    }
}
