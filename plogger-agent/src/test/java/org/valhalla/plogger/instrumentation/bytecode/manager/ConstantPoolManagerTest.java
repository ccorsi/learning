package org.valhalla.plogger.instrumentation.bytecode.manager;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileException;
import org.valhalla.plogger.instrumentation.bytecode.constantpool.ConstantClass;
import org.valhalla.plogger.instrumentation.bytecode.constantpool.ConstantMethodRef;
import org.valhalla.plogger.instrumentation.bytecode.constantpool.ConstantNameAndType;
import org.valhalla.plogger.instrumentation.bytecode.constantpool.ConstantPoolEntry;
import org.valhalla.plogger.instrumentation.bytecode.constantpool.ConstantPoolEntryException;
import org.valhalla.plogger.instrumentation.bytecode.constantpool.ConstantString;
import org.valhalla.plogger.instrumentation.bytecode.constantpool.ConstantUtf8;
import org.valhalla.plogger.instrumentation.utils.ClassManagerUtil;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Iterator;

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

public class ConstantPoolManagerTest {

    private ClassManager classManager;
    private ConstantPoolManager constantPoolManager;
    private static final String testClassName = "java/lang/Integer";
    private ClassManagerUtil classManagerUtil;

    @BeforeEach
    void setUp() throws ClassFileException, IOException {
        try {
            classManagerUtil = new ClassManagerUtil(testClassName);
            classManager = classManagerUtil.getClassManager();
            constantPoolManager = classManager.getConstantPoolManager();
        } catch(RuntimeException e) {
            e.printStackTrace(System.out);
            throw e;
        }
    }

    @AfterEach
    void tearDown() throws IOException {
        classManagerUtil.close();
    }

    @Test
    void getStringEntry() {
        for(ConstantPoolEntry entry : constantPoolManager) {
            if (entry instanceof ConstantString) {
                ConstantString constantString = (ConstantString) entry;
                ConstantUtf8 constantUtf8 = constantPoolManager.getEntry(constantString.getStringIndex());
                String value = constantUtf8.getString();
                constantString = constantPoolManager.getStringEntry(value);
                Assertions.assertNotNull(constantString, "Unable to find string: " + value);
                return;
            }
        }
        Assertions.fail("Instance class does not contain any constant string constant pool entries");
    }

    @Test
    void getClassEntry() throws ConstantPoolEntryException {
        String className = classManager.getClassName();
        ConstantClass constantClass = constantPoolManager.getClassEntry(className);
        Assertions.assertNotNull(constantClass, "Unable to find class: " + className);
    }

    @Test
    void getMethodRefEntry() throws ConstantPoolEntryException {
        for(ConstantPoolEntry entry : constantPoolManager) {
            if (entry instanceof ConstantMethodRef) {
                ConstantMethodRef constantMethodRef = (ConstantMethodRef) entry;
                ConstantClass constantClass = constantPoolManager.getEntry(constantMethodRef.getClassIndex());
                ConstantUtf8 utf8 = constantPoolManager.getEntry(constantClass.getNameIndex());
                String className = utf8.getString();
                ConstantNameAndType constantNameAndType =
                        constantPoolManager.getEntry(constantMethodRef.getNameAndTypeIndex());
                utf8 = constantPoolManager.getEntry(constantNameAndType.getNameIndex());
                String name = utf8.getString();
                utf8 = constantPoolManager.getEntry(constantNameAndType.getDescriptorIndex());
                String signature = utf8.getString();
//                System.out.println("Searching ConstantMethodRef for class: " + className + " for method: "
//                        + name + " with signature: " + signature);
                constantMethodRef = constantPoolManager.getMethodRefEntry(className, name, signature);
                Assertions.assertNotNull(constantMethodRef, "Unable to find method: " + name);
                return;
            }
        }
        Assertions.fail("Instance class does not contain any constant method ref constant pool entries");
    }

    @Test
    void getNameAndTypeEntry() {
        for(ConstantPoolEntry entry : constantPoolManager) {
            if (entry instanceof ConstantNameAndType) {
                ConstantNameAndType constantNameAndType = (ConstantNameAndType) entry;
                ConstantUtf8 utf8 = constantPoolManager.getEntry(constantNameAndType.getNameIndex());
                String name = utf8.getString();
                utf8 = constantPoolManager.getEntry(constantNameAndType.getDescriptorIndex());
                String signature = utf8.getString();
                constantNameAndType = constantPoolManager.getNameAndTypeEntry(name, signature);
                Assertions.assertNotNull(constantNameAndType, "Unable to find name and type constant pool entry");
                return;
            }
        }
        Assertions.fail("Instance class does not contain any constant name and type constant pool entries");
    }

    @Test
    void getUtf8Entry() {
        for(ConstantPoolEntry entry : constantPoolManager) {
            if(entry instanceof ConstantUtf8) {
                ConstantUtf8 utf8 = (ConstantUtf8) entry;
                String value = utf8.getString();
                utf8 = constantPoolManager.getUtf8Entry(value);
                Assertions.assertNotNull(utf8, "Unable to find utf8 constant pool entry");
                return;
            }
        }
        Assertions.fail("Instance class does not contain any constant utf8 constant pool entries");
    }

    @Test
    void iterator() {
        Iterator<ConstantPoolEntry> iterator = constantPoolManager.iterator();
        Assertions.assertNotNull(iterator, "ConstantPoolManager did not return an iterator");
    }

    @Test
    void addStringEntry() {
        String string = "find this string";
        ConstantString constantString = constantPoolManager.getStringEntry(string);
        Assertions.assertNotNull(constantString, "A Constant String entry was not created");
    }

    @Test
    void addClassEntry() throws ConstantPoolEntryException {
        String name = "Find/Me/Class/Name";
        ConstantClass constantClass = constantPoolManager.getClassEntry(name);
        Assertions.assertNotNull(constantClass, "Unable to create a constant class constant pool entry");
    }

    @Test
    void addMethodRefEntry() throws ConstantPoolEntryException {
        String className = "Create/Me/Class/Name";
        String name = "methodNameToCreate";
        String signature = "(Find/Me/Class/Name)";
        ConstantMethodRef constantMethodRef = constantPoolManager.getMethodRefEntry(className, name, signature);
        Assertions.assertNotNull(constantMethodRef, "Unable to create constant method ref constant pool entry");
    }

    @Test
    void addNameAndTypeEntry() {
//        System.out.println("Starting addNameAndTypeEntry test");
        String name = "methodNameToCreate";
        String signature = "(Find/Me/Class/Name)";
        ConstantNameAndType constantNameAndType;
        constantNameAndType = constantPoolManager.getNameAndTypeEntry(name, signature);
        Assertions.assertNotNull(constantNameAndType, "Unable to create constant name and type constant pool entry");
    }

    @Test
    void addUtf8Entry() {
        String string = "find this utf8 string";
        ConstantString constantString = constantPoolManager.getStringEntry(string);
        Assertions.assertNotNull(constantString, "A Constant Utf8 entry was not created");
    }
}