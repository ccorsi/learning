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

/**
 * This class loader will be used to determine if the instructed class
 * was correctly instrumented by providing a means to create an instance
 * of the instrumented class.  This will also provide the ability to
 * determine if the injected Logger method calls will produce the
 * expected results.
 *
 */
public class ClassLoaderClass extends ClassLoader {

    public ClassLoaderClass(ClassLoader parent) {
        super(parent);
    }

    public ClassLoaderClass() {
        super();
    }

    /**
     * This method is used to load the given class bytes into
     * this class loader and it will return the instantiated
     * class instance.  This can then be used to create objects
     * that can then be used to test that the Logger implementation
     * actually produces the expected results.
     *
     * @param name The name of the instantiating class
     * @param bytes The bytes used to create the class
     * @return The generated class instance
     */
    public Class<?> loadClass(String name, byte[] bytes) {
        return defineClass(name, bytes, 0, bytes.length);
    }
}
