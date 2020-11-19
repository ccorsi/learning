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

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Iterator;
import java.util.concurrent.ConcurrentHashMap;

import org.junit.jupiter.api.Assertions;
import org.valhalla.plogger.instrumentation.bytecode.attributes.CodeAttribute;
import org.valhalla.plogger.instrumentation.bytecode.attributes.StackMapTable;

class ClassFileTest {

    private byte[] classData;
    private String className;

    @org.junit.jupiter.api.BeforeEach
    void setUp() throws IOException {
        className = ConcurrentHashMap.class.getName().replace('.', '/');
        InputStream is = ClassLoader.getSystemResourceAsStream(className + ".class");
        Assertions.assertNotNull(is, "Unable to find resource: " + className);
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        for (int b = is.read() ; b > -1 ; b = is.read()) {
            bos.write(b);
        }
        bos.close();
        classData = bos.toByteArray();
    }

    @org.junit.jupiter.api.AfterEach
    void tearDown() {
    }

    @org.junit.jupiter.api.Test
    void load() throws ClassFileException {
        ClassFile classFile = ClassFile.load(className, classData);
        String thisClassName = classFile.getThisClassName();
        String superClassName = classFile.getSuperClassName();
        System.out.println("This Class Name: " + thisClassName);
        System.out.println("Super Class Name: " + superClassName);
        for (Iterator<ClassMethod> it = classFile.getMethods(); it.hasNext(); ) {
            ClassMethod method = it.next();
            CodeAttribute code = method.getCode();
            if (code != null) {
                StackMapTable table = code.getStackMapTable();
//                System.out.println("Method:" + method.getName(classFile));
//                System.out.println(table);
            }
        }
//        System.out.println(classFile);
//        Assertions.fail("This is a test");
    }
}