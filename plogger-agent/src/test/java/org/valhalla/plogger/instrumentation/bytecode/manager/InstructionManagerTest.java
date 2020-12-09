package org.valhalla.plogger.instrumentation.bytecode.manager;

import org.junit.jupiter.api.*;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileException;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassMethod;
import org.valhalla.plogger.instrumentation.bytecode.manager.code.Instruction;
import org.valhalla.plogger.instrumentation.utils.ClassManagerUtil;

import java.io.IOException;
import java.util.Iterator;
import java.util.concurrent.ConcurrentHashMap;

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

public class InstructionManagerTest {

    private static final String testClassName = ConcurrentHashMap.class.getName().replace('.','/');
    public static final int ACC_STATIC = 0x0008;
    private ClassManagerUtil classManagerUtil;
    private static final Class<?> testClass = Long.class;
    private ClassManager classManager;
    private MethodManager methodManager;
    private String methodName;
    private String signature;

    @BeforeEach
    void setUp() throws IOException, ClassFileException {
        try {
            classManagerUtil = new ClassManagerUtil(testClassName);
        } catch(ClassFileException e) {
            e.printStackTrace(System.out);
            throw e;
        }

        classManager = classManagerUtil.getClassManager();
        ClassFile classFile = classManagerUtil.getClassFile();
        ClassMethod method = classFile.getMethods().next();
        methodName = method.getName(classFile);
        signature = method.getSignature(classFile);
        methodManager = classManager.getMethodManager(methodName, signature);
        Assertions.assertNotNull(methodManager,
                String.format("The returned MethodManager instance was null for method: %s with signature: %s",
                        methodName, signature));
        Assertions.assertNotNull(methodManager.getCodeAttributeManager(),
                String.format("The returned CodeAttributeManager instance was null for method: %s with signature: %s",
                        methodName, signature));
    }

    @AfterEach
    void tearDown() throws IOException {
        classManagerUtil.close();
    }

    @Test
    @Timeout(2)
    public void instantiateInstructionManager() {
        methodManager = classManager.getMethodManager(methodName, signature);
        byte[] code = methodManager.getCodeAttributeManager().getCode();
        InstructionManager instructionManager = new InstructionManager(classManager, code);
    }

    @Test
    @Timeout(2)
    public void testInstructionManagerIterator() {
        methodManager = classManager.getMethodManager(methodName, signature);
        byte[] code = methodManager.getCodeAttributeManager().getCode();
        InstructionManager instructionManager = new InstructionManager(classManager, code);
        int pos = 0;
        for(AbstractInstruction entry = instructionManager.getFirstInstruction() ; entry != null ;
            entry = entry.getNext()) {
            Assertions.assertTrue(( entry.size() > 0 ) || entry instanceof EndInstruction,
                    "InstructionEntry size is not supposed to be zero");
        }
    }

    @Test
    @Timeout(2)
    public void testInstructionStackMethod() {
        byte[] code = methodManager.getCodeAttributeManager().getCode();
        InstructionManager instructionManager = new InstructionManager(classManager, code);
//        int pos = 0;
        for(AbstractInstruction entry = instructionManager.getFirstInstruction() ; entry != null ;
            entry = entry.getNext()) {
            entry.stack();
            Assertions.assertTrue(( entry.size() > 0 ) || entry instanceof EndInstruction,
                    "InstructionEntry size is not supposed to be zero");
        }
    }

    @Test
    public void testInstructionManagerInstrumentMethod() {
        CodeAttributeManager codeAttributeManager = methodManager.getCodeAttributeManager();
        codeAttributeManager.instrument(classManager, methodManager);
        byte[] code = codeAttributeManager.getCode();
        InstructionManager instructionManager = new InstructionManager(classManager, code);
    }
}