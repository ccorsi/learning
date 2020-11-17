package org.valhalla.plogger.instrumentation.bytecode.classes;

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