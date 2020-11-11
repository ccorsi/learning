package org.valhalla.instrumentation.plogger.agent.bytecode.classes;

import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.concurrent.ConcurrentHashMap;

import static org.junit.jupiter.api.Assertions.*;

class ClassFileTest {

    @org.junit.jupiter.api.BeforeEach
    void setUp() {
    }

    @org.junit.jupiter.api.AfterEach
    void tearDown() {
    }

    @org.junit.jupiter.api.Test
    void load() throws IOException, ClassFileException {
        String className = ConcurrentHashMap.class.getCanonicalName();
        String name = ConcurrentHashMap.class.getName().replace('.','/') + ".class";
        System.out.println("name: " + name);
        byte[] bytes = new byte[0];
        try (InputStream is = ClassLoader.getSystemResourceAsStream(name)) {
            ByteArrayOutputStream bos = new ByteArrayOutputStream();
            for ( ; is.available() > 0 ; ) {
                bos.write(is.read());
            }
            bos.close();
            bytes = bos.toByteArray();
        }
        System.out.println("bytes length: " + bytes.length);
        System.out.println("Before Calling ClassFile load");
        try {
            ClassFile classFile = ClassFile.load(className, bytes);
        } catch (ClassFileException t) {
            t.printStackTrace(System.out);
            // throw t;
        }
        System.out.println("After Calling ClassFile load");
    }
}