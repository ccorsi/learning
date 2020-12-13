package org.valhalla.plogger.instrumentation;

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

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileException;
import org.valhalla.plogger.instrumentation.bytecode.manager.ClassManager;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.File;
import java.io.FileOutputStream;
import java.io.FileReader;
import java.io.IOException;
import java.lang.instrument.ClassFileTransformer;
import java.lang.instrument.IllegalClassFormatException;
import java.lang.module.ModuleDescriptor;
import java.lang.module.ModuleReader;
import java.lang.module.ModuleReference;
import java.lang.reflect.Method;
import java.net.URI;
import java.security.ProtectionDomain;
import java.util.Set;

public class AgentClassFileTransformer implements ClassFileTransformer {
    private final Module thisModule;
    private final Set<String> thisModulePackages;
    private final Module unnameModule;

    private boolean canLoadLoggerClasses(Module module, ClassLoader loader, String className) {
//        if (className.contains("sun/launcher/LauncherHelper")) {
////            System.out.println("NOT INSTRUMENTING LAUNCHER HELPER CLASS");
//            return false;
//        }

        // All non-null class loaders should be able to load the Logger classes.
        if (loader != null) {
            try {
                loader.loadClass(Logger.class.getName());
                return true;
            } catch (Throwable t) {
                // do notthing
            }
        }

        if (module != null) {
            // Should I test this against the Module class loader????
            ClassLoader cl = module.getClassLoader();
            if (cl != null) {
                try {
                    cl.loadClass(Logger.class.getName());
                    return true;
                } catch (Throwable t) {
                    // do notthing.
                }
            }
        }

//        if (loader != null) {
//            try {
//                Class<?> loaderClass = loader.getClass();
//                Method method = loaderClass.getMethod("loadModule", ModuleReference.class);
//                // Add our stuff this this class loader.
//                ModuleReference moduleReference = new AgentModuleReference();
//                method.invoke(loader, moduleReference);
//                return true;
//            } catch (Throwable t) {
//                // do notthing
//            }
//        }

//        System.out.println("NOT INSTRUMENTING CLASS " + className + " MODULE " + module + " CLASSLOADER " + loader);
//        return false;
        return true;
    }

//    private void addToBuiltinClassLoader(ClassLoader loader) {
//        if (loader != null) {
//            try {
//                Class<?> loaderClass = loader.getClass();
//                Method method = loaderClass.getMethod("loadModule", ModuleReference.class);
//                // Add our stuff this this class loader.
//                ModuleReference moduleReference = new AgentModuleReference();
//                method.invoke(loader, moduleReference);
//            } catch (Throwable t) {
//                // do notthing
//            }
//        }
//    }
//
//    private class AgentModuleReference extends ModuleReference {
//
//        protected AgentModuleReference() {
//            super(ModuleDescriptor.newModule("org.valhalla.plogger.instrumentation")
//                            .requires("java.base").exports("org.valhalla.plogger.instrumentation")
//                            .packages(Set.of("org.valhalla.plogger.instrumentation")).build(),
//                    AgentMain.getJarFile().toURI());
//        }
//
//        @Override
//        public ModuleReader open() throws IOException {
//            return null;
//        }
//    }

    public AgentClassFileTransformer() {
        ClassLoader cl = ClassLoader.getPlatformClassLoader();
//        addToBuiltinClassLoader(cl);
        unnameModule = cl.getUnnamedModule();
        thisModule = this.getClass().getClassLoader().getUnnamedModule();
        thisModulePackages = thisModule.getPackages();
    }

    public byte[] transform(ClassLoader loader, String className, Class<?> classBeingRedefined, ProtectionDomain protectionDomain, byte[] classfileBuffer) throws IllegalClassFormatException {
//        InitializeLogger.init();
//        System.out.println("Calling transform method for class: " + className);
        if (! className.startsWith("org/valhalla/plogger/instrumentation")
                && canLoadLoggerClasses(null, loader, className)) {
            try {
//                System.out.println("Instrumenting class: " + className);
                ClassManager classManager = new ClassManager(className, classfileBuffer);
                if (classManager.instrument()) {
                    ByteArrayOutputStream bos = new ByteArrayOutputStream();
                    try (DataOutputStream dos = new DataOutputStream(bos)) {
                        classManager.write(dos);
                    }
//                    System.out.println("Instrumented class: " + className);
                    return bos.toByteArray();
                }
            } catch (Throwable e) {
                System.out.println("An exception was thrown when transforming class: " + className);
                e.printStackTrace(System.out);
//                decompileJavaClass(className);
            } finally {
//                System.out.println("Completed Instrumenting class: " + className);
            }
        }
        return null;
    }

    public byte[] transform(Module module, ClassLoader loader, String className, Class<?> classBeingRedefined, ProtectionDomain protectionDomain, byte[] classfileBuffer) throws IllegalClassFormatException {
//        System.out.println("Calling transform method for class: " + className);
        // TODO: We need to include the use of the Module parameter.
        if (! className.startsWith("org/valhalla/plogger/instrumentation")
                && canLoadLoggerClasses(module, loader, className)) {
            try {
//                System.out.println("Instrumenting class: " + className);
                ClassManager classManager = new ClassManager(className, classfileBuffer);
                if (classManager.instrument()) {
                    ByteArrayOutputStream bos = new ByteArrayOutputStream();
                    try (DataOutputStream dos = new DataOutputStream(bos)) {
                        classManager.write(dos);
                    }
//                    System.out.println("Module Instrumented class: " + className);
                    for (String pn : module.getPackages()) {
                        thisModule.addOpens(pn, module);
                    }
                    if (className.equals("org/valhalla/plogger/test/Main") ||
                            className.equals("java/lang/String") || className.equals("sun/launcher/LauncherHelper")
                            || className.equals("java/text/SimpleDateFormat")
                            || className.startsWith("java/util/concurrent/LinkedBlockingQueue")) {
                        String fileName = String.format("%s.class",
                                className.substring(className.lastIndexOf('/') + 1));
                        byte[] data = bos.toByteArray();
                        try (FileOutputStream fos = new FileOutputStream(fileName)) {
                            fos.write(data);
                        }
                        return data;
                    }
                    return bos.toByteArray();
                } else {
//                    System.out.println("Nothing to instrument for class: " + className);
                }
            } catch (Throwable e) {
                System.out.println("An exception was thrown when transforming class: " + className + " for module "
                        + module);
                e.printStackTrace(System.out);
//                decompileJavaClass(className);
            } finally {
//                System.out.println("Completed Instrumenting class: " + className);
            }
        }
        return null;
    }

    private void decompileJavaClass(String className) {
        try {
            System.out.println("Printing out decompiled class");
            className = className.replace('/', '.');
            ProcessBuilder processBuilder = new ProcessBuilder("javap", "-s", "-c", "-l", "-verbose",
                    "-p", className);
            processBuilder = processBuilder.redirectErrorStream(true);
            String fileName = className + ".javap";
            File file = new File(fileName);
            processBuilder = processBuilder.redirectOutput(file);
            Process process = processBuilder.start();
            process.waitFor();
            FileReader fr = new FileReader(fileName);
            try (BufferedReader br = new BufferedReader(fr)) {
                for(String line = br.readLine() ; line != null ; line = br.readLine()) {
                    System.out.println(String.format("%s: %s", className, line));
                }
            }
            file.delete();
        } catch (IOException | InterruptedException ie) {
            ie.printStackTrace();
        }
    }

    @Override
    public String toString() {
        return "AgentClassFileTransformer(JDK 9)";
    }
}
