package org.valhalla.plogger.instrumentation.utils;
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

import org.junit.jupiter.api.Assertions;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileException;
import org.valhalla.plogger.instrumentation.bytecode.manager.ClassManager;

import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class ClassManagerUtil {
    private final String className;
    private final InputStream is;
    private final ClassManager classManager;
    private final byte[] bytes;

    public ClassManagerUtil(String className) throws IOException, ClassFileException {
        this.className = className;
        ClassLoader classLoader = this.getClass().getClassLoader();
        is = classLoader.getResourceAsStream(className + ".class");
        Assertions.assertNotNull(is, String.format("Unable to find class: %s", className));
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        for(int c = is.read() ; c > -1 ; c = is.read()) {
            bos.write(c);
        }
        bytes = bos.toByteArray();
        Assertions.assertNotEquals(0, bytes.length, "The class file was empty");
        classManager = new ClassManager(className, bytes);
    }

    public ClassManager getClassManager() {
        return classManager;
    }

    public void close() throws IOException {
        if (is != null) {
            is.close();
        }
    }

    public byte[] getBytes() {
        return bytes;
    }

}
