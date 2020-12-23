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

import org.valhalla.plogger.instrumentation.bytecode.manager.ClassManager;

import java.io.ByteArrayOutputStream;
import java.io.DataOutputStream;
import java.io.FileOutputStream;
import java.lang.instrument.ClassFileTransformer;
import java.security.ProtectionDomain;
import java.util.ArrayList;
import java.util.List;
import java.util.StringTokenizer;

public abstract class AbstractAgentClassFileTransformer implements ClassFileTransformer {

    private static Condition[] classBytesToSave;
    protected static final Debug debug = Debug.getDebug("agent");
    protected static final Debug debugException = Debug.getDebug("agent.exception");
    protected static final Debug debugName = Debug.getDebug("agent.name");
    private static Condition[] classesToExclude;
    private static Condition[] classesToInclude;


    private interface Condition {
        boolean check(String className);
    }

    private static class RegularExpressionCondition implements Condition {
        private final String regex;
        private final boolean expected;

        public RegularExpressionCondition(String className) {
            this(className, true);
        }

        public RegularExpressionCondition(String className, boolean expected) {
            this.regex = className;
            this.expected = expected;
        }

        @Override
        public boolean check(String className) {
            return expected == className.matches(regex);
        }
    }

    private static class ClassNameCondition implements Condition {
        private final String name;
        private final boolean expected;

        public ClassNameCondition(String className) {
            this(className, true);
        }

        public ClassNameCondition(String className, boolean expected) {
            this.name = className;
            this.expected = expected;
        }

        @Override
        public boolean check(String className) {
            return expected == name.equals(className);
        }
    }

    static {
        classesToInclude = classBytesToSave = classesToExclude = new Condition[0];
    }

    public static void setClassesToInclude(String classes) {
        List<Condition> list = new ArrayList<>();

        StringTokenizer st = new StringTokenizer(classes, ",");
        while (st.hasMoreTokens()) {
            String className = st.nextToken();
            // replace . with / since that is how the names are passed to the class transformer
            className = className.replace('.', '/');
            // Determine if this is a regular expression.
            if (className.contains("*")) {
                // turn the check into a regular expression
                // replace all * with .* and pass it to a regular expression
                className = className.replace("*", ".*");
                list.add(new RegularExpressionCondition(className));
            } else {
                // this is a simple compare check.
                list.add(new ClassNameCondition(className));
            }
        }

        classesToInclude = list.toArray(new Condition[0]);
    }

    public static void setClassesToExclude(String classes) {
        List<Condition> list = new ArrayList<>();

        StringTokenizer st = new StringTokenizer(classes, ",");
        while (st.hasMoreTokens()) {
            String className = st.nextToken();
            // replace . with / since that is how the names are passed to the class transformer
            className = className.replace('.', '/');
            // Determine if this is a regular expression.
            if (className.contains("*")) {
                // turn the check into a regular expression
                // replace all * with .* and pass it to a regular expression
                className = className.replace("*", ".*");
                list.add(new RegularExpressionCondition(className, false));
            } else {
                // this is a simple compare check.
                list.add(new ClassNameCondition(className));
            }
        }

        classesToExclude = list.toArray(new Condition[0]);
    }

    public static void setClassesByteCodeToFile(String classes) {
        List<Condition> list = new ArrayList<>();

        StringTokenizer st = new StringTokenizer(classes, ",");
        while (st.hasMoreTokens()) {
            String className = st.nextToken();
            // replace . with / since that is how the names are passed to the class transformer
            className = className.replace('.', '/');
            // Determine if this is a regular expression.
            if (className.contains("*")) {
                // turn the check into a regular expression
                // replace all * with .* and pass it to a regular expression
                className = className.replace("*", ".*");
                list.add(new RegularExpressionCondition(className));
            } else {
                // this is a simple compare check.
                list.add(new ClassNameCondition(className));
            }
        }

        classBytesToSave = list.toArray(new Condition[0]);
    }

    public byte[] transform(ClassLoader loader, String className, Class<?> classBeingRedefined,
                            ProtectionDomain protectionDomain, byte[] classfileBuffer) {
        boolean entered = LoggerManager.enter();
        try {
            byte[] classBytes = instrumentClass(className, classfileBuffer);
            if (classBytes != null) {
                if (debug.isDebug()) {
                    debug.debug(String.format("Instrumented class: %s", className));
                }
                return classBytes;
            }
            return null;
        } finally {
            if (entered) {
                LoggerManager.exit();
            }
        }
    }

    private boolean canInstrumentClass(String className) {
        if (! className.startsWith("org/valhalla/plogger/instrumentation")) {
            if (classesToExclude.length > 0) {
                for (Condition check : classesToExclude) {
                    if (check.check(className)) {
                        if (debugName.isDebug()) {
                            debugName.debug(String.format("Excluding class: %s", className));
                        }
                        return false;
                    }
                }
            }
            if (classesToInclude.length == 0)
            {
                return true;
            } else {
                for (Condition check : classesToInclude) {
                    if (check.check(className)) {
                        return true;
                    }
                }
            }
        }

        return false;
    }

    private boolean storeClassBytes(String className) {
        for( Condition check : classBytesToSave) {
            if (check.check(className)) {
                return true;
            }
        }

        return false;
    }

    protected final byte[] instrumentClass(String className, byte[] classfileBuffer) {
        if ( canInstrumentClass( className ) ) {
            try {
                ClassManager classManager = new ClassManager(className, classfileBuffer);
                if (debugName.isDebug()) {
                    debugName.debug(String.format("Instrumenting class: %s", className));
                }
                if (classManager.instrument()) {
                    if (debugName.isDebug()) {
                        debugName.debug(String.format("Instrumented class: %s", className));
                    }
                    ByteArrayOutputStream bos = new ByteArrayOutputStream();
                    try (DataOutputStream dos = new DataOutputStream(bos)) {
                        classManager.write(dos);
                    }
                    byte[] classBytes = bos.toByteArray();
                    if ( storeClassBytes( className ) )
                    {
                        String fileName = String.format("%s.class", className.replace('/','.'));
                        try (FileOutputStream fos = new FileOutputStream(fileName)) {
                            fos.write(classBytes);
                        } catch (Throwable t) {
                            // do nothing since it is possible that we don't have any rights here
                        }
                    }
                    if (debugName.isDebug()) {
                        debugName.debug(String.format("Returning transformed class: %s class bytes", className));
                    }
                    return classBytes;
                }
            } catch (Throwable e) {
                if ( debugException.isDebug() ) {
                    String message = "An exception was thrown when transforming class: " + className;
                    debugException.debug(message, e);
                }
            }
        }
        return null;
    }
}
