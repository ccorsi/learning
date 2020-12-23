package org.valhalla.plogger.instrumentation.bytecode.manager;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;
import org.valhalla.plogger.instrumentation.LoggerManager;
import org.valhalla.plogger.instrumentation.utils.ClassLoaderClass;
import org.valhalla.plogger.instrumentation.utils.ClassManagerUtil;
import org.valhalla.plogger.test.types.SampleClass;
import org.valhalla.plogger.test.types.SimpleClass;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;

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

public class ClassManagerTest {

    private ClassManagerUtil classManagerUtil;

    @AfterEach
    void tearDown() throws IOException {
        classManagerUtil.close();
    }

    @Test
    void getConstantPoolManager() throws IOException {
        String className = "java/lang/Integer";
        classManagerUtil = new ClassManagerUtil(className);
        ClassManager classManager = classManagerUtil.getClassManager();
        ConstantPoolManager constantPoolManager = classManager.getConstantPoolManager();
        Assertions.assertNotNull(constantPoolManager, "No ConstantPoolManager was returned");
    }

    @Test
    void getMethodManager() throws IOException {
        String className = "java/lang/Integer";
        classManagerUtil = new ClassManagerUtil(className);
        ClassManager classManager = classManagerUtil.getClassManager();
        String methodName = "toString";
        String signature = "(II)Ljava/lang/String;";
        MethodManager methodManager = classManager.getMethodManager(methodName, signature);
        Assertions.assertNotNull(methodManager, "Method " + methodName + " was not found");
    }

    @Test
    void testInstantiatingLoadedClass() throws IOException {
        String className = SimpleClass.class.getName().replace('.', '/');
        classManagerUtil = new ClassManagerUtil(className);
        ClassManager classManager = classManagerUtil.getClassManager();
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        try (DataOutputStream dos = new DataOutputStream(bos)) {
            classManager.write(dos);
        }
        byte[] classBytes = bos.toByteArray();
        Assertions.assertArrayEquals(classManagerUtil.getBytes(), classBytes);
        ClassLoaderClass classLoaderClass = new ClassLoaderClass(null);
        new ClassManager(className, classBytes);
        classLoaderClass.loadClass(classManager.getClassName().replace('/', '.'), classBytes);
    }

    @Test
    void testInstrumentingSimpleClass() throws IOException, IllegalAccessException, InstantiationException,
            InvocationTargetException, NoSuchMethodException {
        String className = SimpleClass.class.getName().replace('.', '/');
        Class<?>[] constructorParameterTypes = new Class<?>[]{String.class};
        Object[] constructorParameters = new Object[] { "Here we are" };
        MethodDefinition[] methodDefinitions = new MethodDefinition[] {
                new MethodDefinition("getName", new Class<?>[] {}, null),
                new MethodDefinition("setName", new Class<?>[] { String.class }, new String[] { "Set Me" }),
        };
        loadInstrumentAndCallClass(className, constructorParameterTypes, constructorParameters, methodDefinitions);
    }

    @Test
    void testInstrumentingSampleClass() throws IOException, IllegalAccessException, InstantiationException,
            InvocationTargetException, NoSuchMethodException {
        String className = SampleClass.class.getName().replace('.', '/');
        Class<?>[] constructorParameterTypes = new Class<?>[]{String.class};
        Object[] constructorParameters = new Object[] { "Here we are" };
        MethodDefinition[] methodDefinitions = new MethodDefinition[] {
                new MethodDefinition("getName", new Class<?>[] {}, null),
                new MethodDefinition("setName", new Class<?>[] { String.class }, new String[] { "Set Me" }),
                new MethodDefinition("staticMethod", new Class<?>[] { String.class }, new String[] { "Setting Static Method" }),
        };
        loadInstrumentAndCallClass(className, constructorParameterTypes, constructorParameters, methodDefinitions);
    }

    @Test
    @Disabled("Failing because we now don't instrument empty parameter methods")
    void loadLauncherHelperClass() throws IOException {
        String className = "sun/launcher/LauncherHelper";
        classManagerUtil = new ClassManagerUtil(className);
        ClassManager classManager = classManagerUtil.getClassManager();
        Assertions.assertTrue( classManager.instrument(), "Unable to instrument class LauncherHelper");
    }

    @Test
    void loadIssueClasses() throws IOException {
        String[] classNames = {
                // Test fail because we now don't instrument parameterless methods.
//                "jdk/internal/loader/AbstractClassLoaderValue$Memoizer",
                "jdk/internal/loader/BuiltinClassLoader$5",
                "jdk/internal/module/SystemModuleFinders$SystemModuleReader",
                "jdk/internal/module/ModulePatcher$PatchedModuleReader",
                "jdk/internal/jimage/ImageReaderFactory$1",
                "jdk/internal/jimage/ImageReader",
                "jdk/internal/jimage/BasicImageReader",
                // as above
//                "jdk/internal/jimage/BasicImageReader$1",
//                "jdk/internal/jimage/NativeImageBuffer$1",
                "jdk/internal/jimage/ImageStringsReader",
                "jdk/internal/jimage/ImageReaderFactory$1",
        };

        MethodManager.setIntrumentation(MethodManager.ACC_PUBLIC | MethodManager.ACC_PROTECTED | MethodManager.ACC_PRIVATE);
        try {
            for (String className : classNames) {
                System.out.println("Loading class " + className);
                classManagerUtil = new ClassManagerUtil(className);
                ClassManager classManager = classManagerUtil.getClassManager();
                Assertions.assertTrue(classManager.instrument(), "Unable to instrument class " + className);
                classManagerUtil.close();
            }
        } finally {
            MethodManager.setIntrumentation(MethodManager.ACC_PUBLIC);
        }
    }

    @Test
    void loadLauncherClass() throws IOException {
//        System.setProperty(StackMapTableManager.DEBUG_PROPERTY_NAME, "true");
        try {
            String className = "sun/launcher/LauncherHelper";
            classManagerUtil = new ClassManagerUtil(className);
            ClassManager classManager = classManagerUtil.getClassManager();
            Assertions.assertTrue(classManager.instrument(), "Unable to instrument class " + className);
        } finally {
//            System.setProperty(StackMapTableManager.DEBUG_PROPERTY_NAME, "false");
        }
    }

    private void loadInstrumentAndCallClass(String className, Class<?>[] constructorParameterTypes,
                                            Object[] constructorParameters, MethodDefinition[] methodDefinitions)
            throws IOException, NoSuchMethodException, InstantiationException, IllegalAccessException, InvocationTargetException {

        classManagerUtil = new ClassManagerUtil(className);
        ClassManager classManager = classManagerUtil.getClassManager();
        Assertions.assertTrue(classManager.instrument(), "Class was not instrumented");

        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        try (DataOutputStream dos = new DataOutputStream(bos)) {
            classManager.write(dos);
        }
        byte[] instrumentedClassBytes = bos.toByteArray();
        Assertions.assertNotNull(instrumentedClassBytes);

        ClassLoaderClass classLoaderClass = new ClassLoaderClass(getClass().getClassLoader());
        String name = classManager.getClassName().replace('/', '.');
        Class<?> loadedClass = classLoaderClass.loadClass(name, instrumentedClassBytes);
        String methodName = "<init>";
        try {
            System.out.println("Instrumenting class: " + className);
            LoggerManager.remove(); // Remove the currently added entries
            Constructor<?> constructor = loadedClass.getConstructor(constructorParameterTypes);
            Object instance = constructor.newInstance(constructorParameters);
            for (MethodDefinition methodDefinition : methodDefinitions) {
                methodName = methodDefinition.name;
                Method method = loadedClass.getDeclaredMethod(methodDefinition.name, methodDefinition.parameterTypes);
                method.invoke(instance, methodDefinition.parameterValues);
            }
            // Write out the logged entries
            for(String entry : LoggerManager.getEntriesBuffer()) {
                System.out.println(entry);
            }
        } catch( ClassFormatError e) {
            System.out.println("Class format error for class: " + className);
            FileOutputStream fos = new FileOutputStream("SampleClass.class");
            try (DataOutputStream dos = new DataOutputStream(fos)) {
                classManager.write(dos);
            }
            throw e;
        } catch( VerifyError e) {
            System.out.println("Verification error for class: " + className);
            FileOutputStream fos = new FileOutputStream("SampleClass.class");
            try (DataOutputStream dos = new DataOutputStream(fos)) {
                classManager.write(dos);
            }
            throw e;
        } catch (InvocationTargetException e) {
            System.out.println("Invocation target exception for class: " + className);
            FileOutputStream fos = new FileOutputStream("SampleClass.class");
            try (DataOutputStream dos = new DataOutputStream(fos)) {
                classManager.write(dos);
            }
            throw e;
        }
    }

    class MethodDefinition {

        private final String name;
        private final Class<?>[] parameterTypes;
        private final Object[] parameterValues;

        public MethodDefinition(String name, Class<?>[] parameterTypes, Object[] parameterValues) {
            this.name = name;
            this.parameterTypes = parameterTypes;
            this.parameterValues = parameterValues;
        }
    }
}