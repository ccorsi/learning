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

import org.valhalla.plogger.instrumentation.bytecode.manager.MethodManager;

import java.io.IOException;
import java.lang.instrument.Instrumentation;
import java.lang.instrument.UnmodifiableClassException;
import java.util.StringTokenizer;

public class AgentMain {

    private static String[] appenderSettings = new String[0];
    private static final Debug debugException = Debug.getDebug("agent.exception");

    public static void premain(String argString, Instrumentation inst) throws IOException, UnmodifiableClassException {
        if (parseArgs(argString)) {
            // Initialize first
            LoggerManager.init(appenderSettings);
            // Insure that these calls will not cause any logging
            LoggerManager.enter();
            try {
                // Now create the transformer class.
                AgentClassFileTransformer transformer = new AgentClassFileTransformer();
                // Get currently loaded classes.
                Class[] classes = inst.getAllLoadedClasses();
                // Add transformer
                inst.addTransformer(transformer);
                System.out.println("Added Agent Transformer: " + transformer);
                try {
                    if (inst.isRetransformClassesSupported()) {
                        // TODO: This has a huge impact on the system when it is starting because of the amount of
                        //  classes that need to be transformed.  We need to think a of smarter way of including these
                        //  classes or just deal with the fact that we just don't have these instrumented.
                        //  NOTE: We can't span a thread and execute the retransformClasses call.  The JVM will generate
                        //      an exception in that case.
                        // Re-transform the loaded classes
                        for (Class<?> loadedClass : classes) {
                            if (inst.isModifiableClass(loadedClass)) {
                                inst.retransformClasses(loadedClass);
                            }
                        }
                    }
                } catch (UnmodifiableClassException e) {
                    if (debugException.isDebug()) {
                        debugException.debug(e); // e.printStackTrace(System.out);
                    }
//            throw e;
                } catch (Throwable t) {
                    if (debugException.isDebug()) {
                        debugException.debug("An exception was raised when adding class transformer", t);
                    }
                }
            } finally {
                LoggerManager.exit();
            }
        }
    }

    private static boolean parseArgs(String args) {
        if (args != null) {
            StringTokenizer st = new StringTokenizer(args, ";");
            while (st.hasMoreTokens()) {
                String token = st.nextToken();
                int eq = token.indexOf('=');
                String option;
                String parameters;
                if (eq > 0) {
                    option = token.substring(0, eq);
                    parameters = token.substring(eq + 1);
                } else {
                    option = token;
                    parameters = "";
                }
                if (option.equals("debug")) {
                    // Which sections to debug
                    Debug.initialize(parameters);
                    LoggerDebug.initialize(parameters);
                } else if (option.equals("access")) {
                    // TODO: move this to the MethodManager.setInstrumentation method
                    //  determine the access level of the methods to instrument
                    if ("public".equals(parameters)) {
                        // default public methods only
                        MethodManager.setIntrumentation(MethodManager.ACC_PUBLIC);
                    } else if ("protected".equals(parameters)) {
                        // public and protected methods
                        MethodManager.setIntrumentation(MethodManager.ACC_PUBLIC | MethodManager.ACC_PROTECTED);
                    } else if ("private".equals(parameters)) {
                        // public, protected, package and private methods all
                        MethodManager.setIntrumentation(MethodManager.ACC_PUBLIC | MethodManager.ACC_PROTECTED
                                | MethodManager.ACC_PRIVATE);
                    }
                } else if (option.equals("appender")) {
                    // This will be used to define and set the Appender being used.
                    // We'll start with one simple appender and move to others that can become useful
                    StringTokenizer at = new StringTokenizer(parameters, ",");
                    appenderSettings = new String[at.countTokens()];
                    for ( int idx = 0 ; at.hasMoreTokens() ; ) {
                        appenderSettings[idx++] = at.nextToken();
                    }
                } else if (option.equals("include")) {
                    AbstractAgentClassFileTransformer.setClassesToInclude(parameters);
                } else if (option.equals("exclude")) {
                    AbstractAgentClassFileTransformer.setClassesToExclude(parameters);
                } else if (option.equals("bytecode")) {
                    AbstractAgentClassFileTransformer.setClassesByteCodeToFile(parameters);
                } else if (option.equals("help")) {
                    // print usage and exit?
                    usage();
                    return false;
                }
            }
        }
        return true;
    }

    private static void usage() {
        System.out.println("usage: -javaagent:<agent.jar.file>[=<options>]");
        System.out.println("where <options> is defined as <option>[,<option>]");
        System.out.println("while <option> is defined as <name>[=<parameter>[;<parameter>]]");
    }
}
