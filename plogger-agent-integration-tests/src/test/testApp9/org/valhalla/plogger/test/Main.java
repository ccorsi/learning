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

import org.apache.log4j.Logger;
import org.valhalla.plogger.test.common.LoggerManager;

//import java.lang.reflect.Method;

public class Main {
    public static void main(String[] args) throws Throwable {
        try {
            System.out.println("Simple Java 9 module application");

//        Class<?> loggerClass =  Class.forName("org.apache.log4j.LogManager");
//        Method method = loggerClass.getMethod("getLogger", Class.class);
//        method.invoke(null, Main.class);
//        // TODO: An issue with how maven compiler not able to distinguish between
//        //  module based jar files and non-module based jar files.
////        org.apache.log4j.LogManager.getLogger(Main.class);
            Logger logger = LoggerManager.getLogger(Main.class);
            System.out.println("Returned Logger instance: " + logger);
        } catch (Throwable t) {
            t.printStackTrace();
            System.exit(1);
        }
    }
}
