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

import java.io.PrintWriter;
import java.io.StringWriter;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Collection;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.Set;

public class Logger {

    private static final Debug debug = Debug.getDebug("logger");

    private static final SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd-HH-mm-ssSSSZ");

    private static final Object[] NONE = new Object[0];

    public static void write(Class<?> clz, String methodName) {
        try {
            _write(clz.getName(), methodName, NONE);
        } catch (Throwable t) {
            if (debug.isDebug())
                t.printStackTrace();
        }
    }

    public static void write(Object object, String methodName) {
        try {
            _write(object.getClass().getName() + "@" + System.identityHashCode(object), methodName, NONE);
        } catch (Throwable t) {
            if (debug.isDebug())
                t.printStackTrace();
        }
    }

    public static void write(Class<?> clz, String methodName, Object[] values) {
        try {
            _write(clz.getName(), methodName, values);
        } catch (Throwable t) {
            if (debug.isDebug())
                t.printStackTrace();
        }
    }

    public static void write(Object object, String methodName, Object[] values) {
        try {
            _write(object.getClass().getName() + "@" + System.identityHashCode(object), methodName, values);
        } catch (Throwable t) {
            if (debug.isDebug())
                t.printStackTrace();
        }
    }

    private static void _write(String objectId, String methodName, Object[] parameters) {
        if (LoggerManager.enter()) {
            try {
                List<String> entries = LoggerManager.getEntriesBuffer();
                StringBuilder string = new StringBuilder();
                // Add Thread Name
                Thread thread = Thread.currentThread();
                string.append("Thread[[Id=").append(thread.getId()).append(",").append(thread.getName()).append("]] ");
                // Add current date and time
                string.append("[[");
                string.append(formatter.format(Calendar.getInstance().getTime()));
                string.append("]] ");
                string.append(objectId).append('.').append(methodName).append("(");
                if (parameters != null && parameters.length > 0) {
                    createParameterValue(string, parameters[0]);
                    for (int idx = 1; idx < parameters.length; idx++) {
                        string.append(',');
                        createParameterValue(string, parameters[idx]);
                    }
                }
                string.append(")");
                entries.add(string.toString());
            } catch (Throwable t) {
                // Insure that no exception is propagated up to the user calling code
                if (debug.isDebug()) {
                    StringWriter sw = new StringWriter();
                    try (PrintWriter pw = new PrintWriter(sw)) {
                        pw.print(String.format("Exception for objectId %s method %s", objectId, methodName));
                        if (parameters.length > 0) {
                            pw.println("with parameters:");
                            for (Object parameter : parameters)
                                pw.println(parameter);
                        }
                    }
                    debug.debug(sw.toString(), t);
                }
            } finally {
                LoggerManager.exit();
            }
        }
    }

    private static void createParameterValue(StringBuilder string, Object parameter) {
        if (parameter == null) {
            // Always avoid the possibility of someone passing null parameter values
            string.append("Null[]");
        } else if (parameter instanceof String) {
            string.append("String[").append(parameter.toString()).append("]");
        } else if (parameter instanceof Number) {
            string.append(parameter.getClass().getSimpleName()).append("[").append(parameter.toString()).append("]");
        } else if (parameter instanceof Class) {
            string.append("Class[").append(((Class<?>) parameter).getName()).append("]");
        } else if (parameter instanceof Boolean) {
            string.append("Boolean[").append(parameter.toString()).append("]");
        } else {
            Class<?> parameterClass = parameter.getClass();
            if (parameterClass.isArray()) {
                String simpleName = parameterClass.getSimpleName();
                string.append("Array[type=").append(simpleName.substring(0, simpleName.indexOf('[')))
                        .append(",values=[");
                createArrayValues(string, parameter);
                string.append("]]");
            } else if (parameterClass.isAssignableFrom(Map.class)) {
                Map<?,?> map = (Map<?,?>) parameter;
                string.append("Map[size=").append(map.size()).append(',')
                        .append(parameterClass).append('@').append(System.identityHashCode(parameter));
                string.append("]");
            } else if (parameterClass.isAssignableFrom(Set.class)) {
                Set<?> set = (Set<?>) parameter;
                string.append("Set[size=").append(set.size()).append(',').append(parameterClass).append('@').append(System.identityHashCode(parameter)).append("]");
            } else if (parameterClass.isAssignableFrom(List.class)) {
                List<?> list = (List<?>) parameter;
                string.append("List[size=").append(list.size()).append(',').append(parameterClass).append('@').append(System.identityHashCode(parameter)).append("]");
            } else if (parameterClass.isAssignableFrom(Queue.class)) {
                Queue<?> queue = (Queue<?>) parameter;
                string.append("Queue[size=").append(queue.size()).append(',').append(parameterClass).append('@').append(System.identityHashCode(parameter)).append("]");
            } else if (parameterClass.isAssignableFrom(Collection.class)) {
                Collection<?> collection = (Collection<?>) parameter;
                string.append("Collection[size=").append(collection.size()).append(',').append(parameterClass).append('@').append(System.identityHashCode(parameter)).append("]");
            } else {
                string.append("Object[").append(parameterClass).append('@').append(System.identityHashCode(parameter)).append("]");
            }
        }
    }

    public static final int DEFAULT_MAX_SIZE = 5;

    private static int maxSize = Integer.getInteger("plogger.array.size", DEFAULT_MAX_SIZE);

    private static void createArrayValues(StringBuilder string, Object arrayParameter) {
        // TODO: need to deal with the case that we are processing a multi-dimensional array
        //  because index through it will not produce the correct parameter logging information.
        if (arrayParameter instanceof boolean[]) {
            boolean values[] = (boolean[]) arrayParameter;
            int size = Math.min(maxSize, values.length);
            if (size > 0) {
                string.append(values[0]);
                for (int idx = 1; idx < size; idx++) {
                    string.append(',').append(values[idx]);
                }
                if (size < values.length) {
                    string.append(",...");
                }
            }
        } else if (arrayParameter instanceof byte[]){
            byte values[] = (byte[])arrayParameter;
            int size = Math.min(maxSize, values.length);
            if (size > 0) {
                string.append(values[0]);
                for (int idx = 1; idx < size; idx++) {
                    string.append(',').append(values[idx]);
                }
                if (size < values.length) {
                    string.append(",...");
                }
            }
        } else if (arrayParameter instanceof char[]) {
            char values[] = (char[])arrayParameter;
            int size = Math.min(maxSize, values.length);
            if (size > 0) {
                string.append(values[0]);
                for (int idx = 1; idx < size; idx++) {
                    string.append(',').append(values[idx]);
                }
                if (size < values.length) {
                    string.append(",...");
                }
            }
        } else if (arrayParameter instanceof short[]) {
            short values[] = (short[])arrayParameter;
            int size = Math.min(maxSize, values.length);
            if (size > 0) {
                string.append(values[0]);
                for (int idx = 1; idx < size; idx++) {
                    string.append(',').append(values[idx]);
                }
                if (size < values.length) {
                    string.append(",...");
                }
            }
        } else if (arrayParameter instanceof int[]) {
            int values[] = (int[])arrayParameter;
            int size = Math.min(maxSize, values.length);
            if (size > 0) {
                string.append(values[0]);
                for (int idx = 1; idx < size; idx++) {
                    string.append(',').append(values[idx]);
                }
                if (size < values.length) {
                    string.append(",...");
                }
            }
        } else if (arrayParameter instanceof long[]) {
            long values[] = (long[])arrayParameter;
            int size = Math.min(maxSize, values.length);
            if (size > 0) {
                string.append(values[0]);
                for (int idx = 1; idx < size; idx++) {
                    string.append(',').append(values[idx]);
                }
                if (size < values.length) {
                    string.append(",...");
                }
            }
        } else if (arrayParameter instanceof float[]) {
            float values[] = (float[])arrayParameter;
            int size = Math.min(maxSize, values.length);
            if (size > 0) {
                string.append(values[0]);
                for (int idx = 1; idx < size; idx++) {
                    string.append(',').append(values[idx]);
                }
                if (size < values.length) {
                    string.append(",...");
                }
            }
        } else if (arrayParameter instanceof double[]) {
            double values[] = (double[])arrayParameter;
            int size = Math.min(maxSize, values.length);
            if (size > 0) {
                string.append(values[0]);
                for (int idx = 1; idx < size; idx++) {
                    string.append(',').append(values[idx]);
                }
                if (size < values.length) {
                    string.append(",...");
                }
            }
        } else {
            // This is just an array of objects types.
            Object values[] = (Object[])arrayParameter;
            int size = Math.min(maxSize, values.length);
            if (size > 0) {
                string.append(values[0]);
                for (int idx = 1; idx < size; idx++) {
                    string.append(',');
                    if (values[idx] instanceof Class<?>) {
                        string.append(((Class<?>)values[idx]).getName());
                    } else {
                        string.append(values[idx].getClass().getName()).append('@').append(System.identityHashCode(values[idx]));
                    }
                }
                if (size < values.length) {
                    string.append(",...");
                }
            }
        }
    }
}
