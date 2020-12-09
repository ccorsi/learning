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

import org.valhalla.plogger.instrumentation.bytecode.attributes.*;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileException;
import org.valhalla.plogger.instrumentation.bytecode.constantpool.ConstantUtf8;

import java.io.DataInputStream;

public class AttributeManagerFactory {

    public static AttributeManager create(ClassAttribute attribute) {
        if (attribute instanceof StackMapTable) {
            StackMapTable stackMapTable = (StackMapTable) attribute;
            return new StackMapTableManager(stackMapTable);
        } else if (attribute instanceof CodeAttribute) {
            CodeAttribute codeAttribute = (CodeAttribute) attribute;
            return new CodeAttributeManager(codeAttribute.getNameIndex(), codeAttribute);
        } else if (attribute instanceof LocalVariableTable) {
            LocalVariableTable localVariableTable = (LocalVariableTable) attribute;
            return new LocalVariableTableManager(localVariableTable);
        } else if (attribute instanceof LocalVariableTypeTable) {
            LocalVariableTypeTable localVariableTypeTable = (LocalVariableTypeTable) attribute;
            return new LocalVariableTypeTableManager(localVariableTypeTable);
        } else if (attribute instanceof LineNumberTable) {
            LineNumberTable lineNumberTable = (LineNumberTable) attribute;
            return new LineNumberTableManager(lineNumberTable);
        } else if (attribute instanceof DefaultAttribute) {
            DefaultAttribute defaultAttribute = (DefaultAttribute) attribute;
            return new DefaultAttributeManager(defaultAttribute);
        }
        return null;
    }

    static AttributeManager create(DataInputStream dis, ConstantPoolManager constantPoolManager) {
        try {
            // Extract the attribute index into the constant pool
            int nameIndex = dis.readUnsignedShort();
            int length = dis.readInt();
            // this will through a ClassCastException if it can't sub class the instance to ConstantUtf8
            ConstantUtf8 utf8 = constantPoolManager.getEntry(nameIndex);
            String name = utf8.getString();
            AttributeManager attribute;
            switch (name) {
                case "Code":
                    attribute = createCodeAttributeManager(constantPoolManager, nameIndex, dis);
                    break;
                case "StackMapTable":
                    attribute = new StackMapTableManager(nameIndex, dis);
                    break;
                case "LineNumberTable":
                    attribute = new LineNumberTableManager(nameIndex, dis);
                    break;
                case "LocalVariableTable":
                    attribute = new LocalVariableTableManager(nameIndex, dis);
                    break;
                case "LocalVariableTypeTable":
                    attribute = new LocalVariableTypeTableManager(nameIndex, dis);
                    break;
                default:
                    byte[] data = new byte[length];
                    int copiedCount = dis.read(data);
                    // confirm that bytes were read
                    if (copiedCount != length) {
                        throw new ClassFileException("Unable to read all attribute data");
                    }
                    attribute = new DefaultAttributeManager(nameIndex, data);
            }
            return  attribute;
        } catch(Throwable t) {
            throw new ClassFileException(t);
        }
    }

    private static CodeAttributeManager createCodeAttributeManager(ConstantPoolManager constantPoolManager, int nameIndex, DataInputStream dis) {
        try {
            int maxStack = dis.readUnsignedShort();
            int maxLocals = dis.readUnsignedShort();
            int length = dis.readInt();
            byte[] code = new byte[length];
            int size = dis.read(code);
            if (size != length) {
                throw new ClassFileException("Unable to read all code bytes");
            }
//            size = dis.readUnsignedShort();
            ExceptionTableManager exceptionTableManager = new ExceptionTableManager(dis);
//            ExceptionTableEntryManager[] exceptions = new ExceptionTableEntryManager[size];
//            for (int idx = 0; idx < size; idx++) {
//                int startPc = dis.readUnsignedShort();
//                int endPc = dis.readUnsignedShort();
//                int handlePc = dis.readUnsignedShort();
//                int catchType = dis.readUnsignedShort();
//                exceptions[idx] = new ExceptionTableEntryManager(startPc, endPc, handlePc, catchType);
//            }
            int numAttributes = dis.readUnsignedShort();
            AttributeManager[] attributes = new AttributeManager[numAttributes];

            for (int idx = 0; idx < numAttributes; idx++) {
                attributes[idx] = create(dis, constantPoolManager);
            }

            return new CodeAttributeManager(nameIndex, maxStack, maxLocals, code, exceptionTableManager, attributes);
        } catch(Throwable t) {
            throw new ClassFileException(t);
        }
    }

}
