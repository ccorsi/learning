package org.valhalla.plogger.test;

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

import org.valhalla.plogger.instrumentation.utils.SampleClass;

public class Main {

    public static void main(String[] args) {
        int count = 1;
        if (args.length > 0) {
            try {
                count = Integer.parseInt(args[0]);
            } catch (RuntimeException e) {

            }
        }
        print();
        while( count-- > 0 )
            load(count);

        recursive(10, 0);

        System.out.println("Thread: " + Thread.currentThread().getName());
    }

    private static void recursive(int max, int current) {
        System.out.println(String.format("Calling recursive call %d", current));
        if (current < max) recursive(max, ++current);
    }

    private static void print() {
        System.out.println("Hello, world!");
    }

    private static void load(int c) {
        SampleClass sampleClass = new SampleClass(String.format("Name:%d", c));
        System.out.println(String.format("SampleClass name: %s", sampleClass.getName()));
        sampleClass.setName(String.format("Updated Name:%d", c));
        System.out.println(String.format("SampleClass name: %s", sampleClass.getName()));
    }
}
