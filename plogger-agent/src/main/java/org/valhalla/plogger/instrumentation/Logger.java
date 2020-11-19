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

import java.text.SimpleDateFormat;
import java.util.*;

public class Logger {
    private static final SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd-HH-mm-ssSSSZ");
    private static final Object[] NONE = new Object[0];

    public static void write(Class<?> clz, String methodName) {
        _write(clz.getName(), methodName, NONE);
    }

    public static void write(Object object, String methodName) {
        _write(object.getClass().getName() + "@" + System.identityHashCode(object), methodName, NONE);
    }

    public static void write(Class<?> clz, String methodName, Object[] values) {
        _write(clz.getName(), methodName, values);
    }

    public static void write(Object object, String methodName, Object[] values) {
        _write(object.getClass().getName() + "@" + System.identityHashCode(object), methodName, values);
    }

    private static void _write(String objectId, String methodName, Object[] parameters) {
        List<String> entries = LoggerManager.getEntriesBuffer();
        StringBuilder string = new StringBuilder();
        // Add Thread Name
        Thread thread = Thread.currentThread();
        string.append("Thread[Id=").append(thread.getId()).append(",").append(thread.getName()).append("]] ");
        // Add current date and time
        string.append("<[");
        string.append(formatter.format(Calendar.getInstance().getTime()));
        string.append("]> ");
        string.append(objectId).append('.').append(methodName).append("(");
        if (parameters != null && parameters.length > 0) {
            createParameterValue(string, parameters[0]);
            for (int idx = 1 ; idx < parameters.length ; idx++) {
                string.append(',');
                createParameterValue(string, parameters[idx]);
            }
        }
        string.append(")");
        entries.add(string.toString());
    }

    private static void createParameterValue(StringBuilder string, Object parameter) {
        if (parameter instanceof String) {
            string.append("String[").append(parameter.toString()).append("]");
        } else if (parameter instanceof Number) {
            string.append("Number[").append(parameter.toString()).append("]");
        } else if (parameter instanceof Class) {
            string.append("Class[").append(((Class<?>) parameter).getName()).append("]");
        } else {
            Class<?> parameterClass = parameter.getClass();
            if (parameterClass.isArray()) {
                // parameterClass.getSimpleName();
                // string.append("Array[size=").append(map.size()).append(',').append(parameterClass).append('@').append(System.identityHashCode(parameter)).append("]");
                string.append("Array[").append(parameterClass).append('@').append(System.identityHashCode(parameter)).append("]");
            } else if (parameterClass.isAssignableFrom(Map.class)) {
                Map<?,?> map = (Map<?,?>) parameter;
                string.append("Map[size=").append(map.size()).append(',').append(parameterClass).append('@').append(System.identityHashCode(parameter)).append("]");
            } else if (parameterClass.isAssignableFrom(Set.class)) {
                Set<?> set = (Set<?>) parameter;
                string.append("Set[size=").append(set.size()).append(',').append(parameterClass).append('@').append(System.identityHashCode(parameter)).append("]");
            } else if (parameterClass.isAssignableFrom(List.class)) {
                List<?> list = (List<?>) parameter;
                string.append("List[size=").append(list.size()).append(',').append(parameterClass).append('@').append(System.identityHashCode(parameter)).append("]");
            } else if (parameterClass.isAssignableFrom(Queue.class)) {
                Queue<?> queue = (Queue<?>) parameter;
                string.append("Collection[size=").append(queue.size()).append(',').append(parameterClass).append('@').append(System.identityHashCode(parameter)).append("]");
            } else if (parameterClass.isAssignableFrom(Collection.class)) {
                Collection<?> collection = (Collection<?>) parameter;
                string.append("Collection[size=").append(collection.size()).append(',').append(parameterClass).append('@').append(System.identityHashCode(parameter)).append("]");
            } else {
                string.append("Object[").append(parameterClass).append('@').append(System.identityHashCode(parameter)).append("]");
            }
        }
    }
}
