package org.valhalla.plogger.instrumentation.utils;

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

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class PrintStreamThread extends Thread {
    private final String prefix;
    private final InputStream is;
    private boolean output = false;

    public PrintStreamThread(String prefix, InputStream is) {
        super("PrintStreamThread:");
        this.prefix = prefix;
        this.is = is;
    }

    public boolean isOutput() {
        return output;
    }

    @Override
    public void run() {
        setName(getName() + getId());
        try (BufferedReader br = new BufferedReader(new InputStreamReader(is))) {
            String line = null;
            while ((line = br.readLine()) != null) {
                output = true;
                System.out.println(prefix + line);
            }
        } catch (IOException e) {
            e.printStackTrace(System.out);
        }
    }
}
