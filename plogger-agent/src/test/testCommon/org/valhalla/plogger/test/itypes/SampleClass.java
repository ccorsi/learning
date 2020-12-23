package org.valhalla.plogger.test.itypes;
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

public class SampleClass {

    private final int[] a;
    private final long l;
    private String name;

    private static String staticName;

    static {
        System.out.println("Calling static class method");
        staticName = "This is a static field";
    }

    public void staticMethod(String name) {
        staticName = name;
    }

    public SampleClass(String name, long l, int[] a) {
        this.name = name;
        this.l = l;
        this.a = a;
    }

    public SampleClass(String name) {
        this(name, 101, new int[] { 1, 2, 3 });
    }

    public String getName() {
        return name;
    }

    public String tableswitch(int value) {
        switch(value) {
            case 0:
                return "0";
            case 1:
                return "1";
            case 2:
                return "2";
            default:
                return "N/A";
        }
    }

    public String tablelookup(int value) {
        switch(value) {
            case 0:
                return "0";
            case 101:
                return "101";
            default:
                return "N/A";
        }
    }

    public void setName(String name) {
        this.name = name;
    }
}
