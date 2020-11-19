package org.valhalla.plogger.instrumentation.bytecode.constantpool;

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

public interface ConstantPoolEntryTag {
    int UTF8 = 1;
    int INTEGER = 3;
    int FLOAT = 4;
    int LONG = 5;
    int DOUBLE = 6;
    int CLASS = 7;
    int STRING = 8;
    int FIELD = 9;
    int METHOD = 10;
    int INTERFACE_METHOD = 11;
    int NAME_AND_TYPE = 12;
    int METHOD_HANDLE = 15; // jdk 7
    int METHOD_TYPE = 16; // jdk 7
    int DYNAMIC = 17; // jdk 11
    int INVOKE_DYNAMIC = 18; // jdk 7
    int MODULE = 19; // jdk 9
    int PACKAGE = 20; // jdk 9
}
