package org.valhalla.plogger.tests;
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

import org.valhalla.plogger.test.common.Executor;

public class RecursiveExecutor implements Executor {
    @Override
    public void execute(String[] args) throws Throwable {

        int depth = 10;
        boolean debug = false;

        for (String arg : args) {
            if (arg.startsWith("depth=")) {
                try {
                    arg = arg.substring("depth=".length());
                    depth = Integer.parseInt(arg);
                } catch (NumberFormatException e) {
                    // do nothing.
                }
            } else if (arg.startsWith("debug=")) {
                try {
                    arg = arg.substring("debug=".length());
                    debug = Boolean.parseBoolean(arg);
                } catch (Throwable t) {
                    // do nothing
                }
            }
        }
        if (args.length > 0) {
        }

        recursive(depth, 0, debug);
    }

    private static void recursive(int max, int current, boolean debug) {
        if (debug) System.out.println(String.format("Calling recursive call %d", current));
        if (current < max) recursive(max, ++current, debug);
    }
}
