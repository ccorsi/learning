package org.valhalla.plogger.instrumentation.bytecode.attributes;

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

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileException;
import org.valhalla.plogger.instrumentation.bytecode.constantpool.ConstantPoolEntry;
import org.valhalla.plogger.instrumentation.bytecode.constantpool.ConstantUtf8;

import java.io.DataInputStream;
import java.io.IOException;

public class ClassAttributeFactory {
    public static ClassAttribute load(ClassFile classFile, DataInputStream dis) throws IOException, ClassAttributeException, ClassFileException {
        // Extract the attribute index into the constant pool
        int nameIndex = dis.readUnsignedShort();
        int length = dis.readInt();
        // validate that the referencing attribute index is a ConstantUtf8 constant pool entry
        ConstantPoolEntry cp = classFile.getConstantPool()[nameIndex];
        // this will through a ClassCastException if it can't sub class the instance to ConstantUtf8
        ConstantUtf8 utf8 = (ConstantUtf8) cp;
        String name = utf8.getString();
        ClassAttribute attribute;
        switch(name) {
            case "Code":
                attribute = createCodeAttribute(nameIndex, classFile, dis);
                break;
            default:
                byte[] data = new byte[length];
                int copiedCount = dis.read(data);
                // confirm that bytes were read
                if (copiedCount != length) {
                    throw new ClassAttributeException("Unable to read all attribute data");
                }
                attribute = new DefaultAttribute(classFile, nameIndex, data);
        }
        return attribute;
    }

    public static ClassAttribute loadCodeAttributes(ClassFile classFile, CodeAttribute code, DataInputStream dis) throws IOException, ClassAttributeException, ClassFileException {
        // Extract the attribute index into the constant pool
        int nameIndex = dis.readUnsignedShort();
        int length = dis.readInt();
        // validate that the referencing attribute index is a ConstantUtf8 constant pool entry
        ConstantPoolEntry cp = classFile.getConstantPool()[nameIndex];
        // this will through a ClassCastException if it can't sub class the instance to ConstantUtf8
        ConstantUtf8 utf8 = (ConstantUtf8) cp;
        String name = utf8.getString();
        ClassAttribute attribute;
        switch(name) {
            case "StackMapTable":
                attribute = createStackMapTable(classFile, code, nameIndex, dis);
                break;
            case "LineNumberTable":
                attribute = createLineNumberTable(classFile, code, nameIndex, dis);
                break;
            case "LocalVariableTable":
                attribute = createLocalVariableTable(classFile, code, nameIndex, dis);
                break;
            case "LocalVariableTypeTable":
                attribute = createLocalVariableTypeTable(classFile, code, nameIndex, dis);
                break;
            default:
                byte[] data = new byte[length];
                int copiedCount = dis.read(data);
                // confirm that bytes were read
                if (copiedCount != length) {
                    throw new ClassAttributeException("Unable to read all attribute data");
                }
                attribute = new DefaultAttribute(classFile, nameIndex, data);
        }
        return attribute;
    }

    private static ClassAttribute createLocalVariableTypeTable(ClassFile classFile, CodeAttribute code, int nameIndex, DataInputStream dis) throws IOException {
        int numEntries = dis.readUnsignedShort();
        LocalVariableTypeTableEntry[] entries = new LocalVariableTypeTableEntry[numEntries];
        for (int idx = 0 ; idx < numEntries ; idx++) {
            int startPc = dis.readUnsignedShort();
            int length = dis.readUnsignedShort();
            int typeNameIndex = dis.readUnsignedShort();
            int typeSignatureIndex = dis.readUnsignedShort();
            int typeIndex = dis.readUnsignedShort();
            entries[idx] = new LocalVariableTypeTableEntry(classFile, code, startPc, length, typeNameIndex, typeSignatureIndex, typeIndex);
        }
        return new LocalVariableTypeTable(classFile, code, nameIndex, entries);
    }

    private static ClassAttribute createLocalVariableTable(ClassFile classFile, CodeAttribute code, int nameIndex, DataInputStream dis) throws IOException {
        int numEntries = dis.readUnsignedShort();
        LocalVariableTableEntry[] entries = new LocalVariableTableEntry[numEntries];
        for (int idx = 0 ; idx < numEntries ; idx++) {
            int startPc = dis.readUnsignedShort();
            int length = dis.readUnsignedShort();
            int entryNameIndex = dis.readUnsignedShort();
            int entryDescriptorIndex = dis.readUnsignedShort();
            int entryIndex = dis.readUnsignedShort();
            entries[idx] = new LocalVariableTableEntry(classFile, code, startPc, length, entryNameIndex, entryDescriptorIndex, entryIndex);
        }
        return new LocalVariableTable(classFile, code, nameIndex, entries);
    }

    private static ClassAttribute createLineNumberTable(ClassFile classFile, CodeAttribute code, int nameIndex, DataInputStream dis) throws IOException {
        int numEntries = dis.readUnsignedShort();
        LineNumberTableEntry[] entries = new LineNumberTableEntry[numEntries];
        for (int idx = 0 ; idx < numEntries ; idx++) {
            int startPc = dis.readUnsignedShort();
            int lineNumber = dis.readUnsignedShort();
            entries[idx] = new LineNumberTableEntry(classFile, code, startPc, lineNumber);
        }
        return new LineNumberTable(classFile, code, nameIndex, entries);
    }

    private static ClassAttribute createStackMapTable(ClassFile classFile, CodeAttribute code, int nameIndex, DataInputStream dis) throws IOException, ClassFileException {
        int numEntries = dis.readUnsignedShort();
        StackMapFrame[] entries = new StackMapFrame[numEntries];
        for(int idx = 0 ; idx < numEntries ; idx++) {
            entries[idx] = StackMapFrameFactory.createStackMapFrame(classFile, code, dis);
        }
        return new StackMapTable(classFile, nameIndex, entries);
    }

    private static ClassAttribute createCodeAttribute(int nameIndex, ClassFile classFile, DataInputStream dis) throws ClassAttributeException, IOException, ClassFileException {
        int maxStack = dis.readUnsignedShort();
        int maxLocals = dis.readUnsignedShort();
        int length = dis.readInt();
        byte[] code = new byte[length];
        int size = dis.read(code);
        if (size != length) {
            throw new ClassAttributeException("Unable to read all code bytes");
        }
        size = dis.readUnsignedShort();
        CodeExceptionTable[] exceptions = new CodeExceptionTable[size];
        int[] startPcs = new int[size];
        int[] endPcs = new int[size];
        int[] handlePcs = new int[size];
        int[] catchTypes = new int[size];
        for(int idx = 0 ; idx < size ; idx++) {
            startPcs[idx] = dis.readUnsignedShort();
            endPcs[idx] = dis.readUnsignedShort();
            handlePcs[idx] = dis.readUnsignedShort();
            catchTypes[idx] = dis.readUnsignedShort();
        }
        int numAttributes = dis.readUnsignedShort();
        ClassAttribute[] attributes = new ClassAttribute[numAttributes];
        CodeAttribute codeAttribute =  new CodeAttribute(classFile, nameIndex, maxStack, maxLocals, code, exceptions, attributes);

        for(int idx = 0 ; idx < numAttributes ; idx++) {
            attributes[idx] = loadCodeAttributes(classFile, codeAttribute, dis);
        }

        // Update the exception table entries
        for (int idx = 0 ; idx < size ; idx++) {
            exceptions[idx] = new CodeExceptionTable(classFile, codeAttribute, startPcs[idx], endPcs[idx], handlePcs[idx], catchTypes[idx]);
        }
        return codeAttribute;
    }
}
