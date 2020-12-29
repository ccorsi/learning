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
import java.util.HashMap;
import java.util.Map;
import java.util.StringTokenizer;

public class LoggerDebug {

    private static final Map<String, String> debugLevelMap;
    private static final Map<String, LoggerDebug> debugMap;

    static {
        debugLevelMap = new HashMap<>();

        String [][] debugLevels = new String[][] {
                {"logger", null},
                {"loggermanager", null},
                {"loggerstoragemanager", null},
        };

        for (String[] debugLevel : debugLevels) {
            debugLevelMap.put(debugLevel[0], debugLevel[1]);
            debugLevelMap.put(debugLevel[0] + ".name", debugLevel[0]);
            debugLevelMap.put(debugLevel[0] + ".exception", debugLevel[0]);
        }

        // Add and initialize different debug levels

        debugMap = new HashMap<>();

        for (Map.Entry<String, String> entry : debugLevelMap.entrySet()) {
            String name = entry.getKey();
            String parent = entry.getValue();
            debugMap.put(name, new LoggerDebug(name, parent));
        }
    }

    public static LoggerDebug getDebug(String name) {
        return debugMap.get(name);
    }

    public String[] getDebugLevels() {
        return debugLevelMap.keySet().toArray(new String[0]);
    }

    private boolean debug;
    private final String name, parent;

    private LoggerDebug(String name, String parent) {
        debug = false;
        this.name = name;
        this.parent = (parent != null) ? parent : "root";
    }

    public void debug(String message) {
        if (debug) {
            System.err.println(String.format("agent debug %s: %s", name, message));
        }
    }

    public void debug(String message, Throwable t) {
        if (debug) {
            StringWriter sw = new StringWriter();
            try (PrintWriter pw = new PrintWriter(sw)) {
                pw.println(String.format("agent debug %s: %s", name, message));
                pw.println(String.format("agent debug %s: Stack Trace ", name));
                t.printStackTrace(pw);
            }
            System.err.println(sw.toString());
        }
    }

    public void debug(Throwable t) {
        if (debug) {
            StringWriter sw = new StringWriter();
            try (PrintWriter pw = new PrintWriter(sw)) {
                pw.println(String.format("agent debug %s: Stack Trace ", name));
                t.printStackTrace(pw);
            }
            System.err.println(sw.toString());
        }
    }

    public boolean isDebug() {
        return debug;
    }

    public static void initialize(String parameters) {
        StringTokenizer st = new StringTokenizer(parameters, ",");
        while (st.hasMoreTokens()) {
            String debugLevel = st.nextToken();

            if (debugLevel.equals("all")) {
                for(LoggerDebug debug : debugMap.values()) {
                    if ("root".equals(debug.parent)) {
                        debug.enable();
                    }
                }
                // We are done.
                return;
            } else if (debugLevel.equals("exception")) {
                for(LoggerDebug debug : debugMap.values()) {
                    if (debug.parent.endsWith("exception")) {
                        debug.enable();
                    }
                }
                continue;
            }

            LoggerDebug debug = debugMap.get(debugLevel);
            if (debug != null) {
                debug.enable();
            } else {
                System.out.println("No debug level: " + debugLevel);
            }
        }
    }

    // Used for testing only
    public static void reset() {
        for(LoggerDebug loggerDebug : debugMap.values()) {
            loggerDebug.debug = false;
        }
    }

    private void enable() {
        System.out.println("Enable debug for " + name);
        debug = true;

        // find all levels that have this as a parent
        for( Map.Entry<String, LoggerDebug> entry : debugMap.entrySet() ) {
            if (name.equals(entry.getValue().parent)) {
                // enable level
                entry.getValue().enable();
            }
        }
    }
}
