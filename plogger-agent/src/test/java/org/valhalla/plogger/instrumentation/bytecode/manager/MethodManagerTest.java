package org.valhalla.plogger.instrumentation.bytecode.manager;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileException;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassMethod;
import org.valhalla.plogger.instrumentation.utils.ClassManagerUtil;

import java.io.IOException;
import java.lang.reflect.Method;
import java.util.Iterator;

import static org.junit.jupiter.api.Assertions.*;

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

public class MethodManagerTest {

    private static final String testClassName = "java/lang/Long";
    private ClassManagerUtil classManagerUtil;

    @BeforeEach
    void setUp() throws IOException, ClassFileException {
        classManagerUtil = new ClassManagerUtil(testClassName);
    }

    @AfterEach
    void tearDown() throws IOException {
        classManagerUtil.close();
    }

    @Test
    void getCodeAttributeManager() {
        ClassManager classManager = classManagerUtil.getClassManager();
        ClassFile classFile = classManagerUtil.getClassFile();
        ClassMethod method = classFile.getMethods().next();
        String methodName = method.getName(classFile);
        String signature = method.getSignature(classFile);
        MethodManager methodManager = classManager.getMethodManager(methodName, signature);
        Assertions.assertNotNull(methodManager,
                String.format("The returned MethodManager instance was null for method: %s with signature: %s",
                        methodName, signature));
        Assertions.assertNotNull(methodManager.getCodeAttributeManager(),
                String.format("The returned CodeAttributeManager instance was null for method: %s with signature: %s",
                        methodName, signature));

        byte[] code = methodManager.getCodeAttributeManager().getCode();
        new InstructionManager(classManager, code);
    }
}