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

import java.io.IOException;
import java.lang.instrument.Instrumentation;
import java.lang.instrument.UnmodifiableClassException;

public class AgentMain {

    public static void premain(String argString, Instrumentation inst) throws IOException, UnmodifiableClassException {
        parseArgs(argString);
        // Initialize first
        LoggerManager.init();
        // Now create the transformer class.
        AgentClassFileTransformer transformer = new AgentClassFileTransformer();
        // Get currently loaded classes.
        Class[] classes = inst.getAllLoadedClasses();
        // Add transformer
        inst.addTransformer(transformer);
        System.out.println("Added Agent Transformer: " + transformer);
        try {
            // TODO: This has a huge impact on the system when it is starting because of the amount of
            //  classes that need to be transformed.  We need to think a of smarter way of including these
            //  classes or just deal with the fact that we just don't have these instrumented.
//            int count = 0;
            // Re-transform the loaded classes
            for(Class<?> loadedClass : classes) {
                if (inst.isModifiableClass(loadedClass)) {
//                    System.out.println("Retransforming class " + loadedClass);
                    inst.retransformClasses(loadedClass);
//                } else {
//                    System.out.println("Unable to transform class " + loadedClass);
//                    count++;
                }
            }
//            System.out.println("Unable to retransform " + count + " classes.");
        } catch (UnmodifiableClassException e) {
            e.printStackTrace(System.out);
//            throw e;
        }
    }

    private static String parseArgs(String args) {
        return "";
    }
}
