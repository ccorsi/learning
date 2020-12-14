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

import java.lang.instrument.IllegalClassFormatException;
import java.security.ProtectionDomain;

public class AgentClassFileTransformer extends AbstractAgentClassFileTransformer {
    private final Module thisModule;

    public AgentClassFileTransformer() {
        // TODO: Do I still need this?
        thisModule = getClass().getClassLoader().getUnnamedModule();
    }

    public byte[] transform(Module module, ClassLoader loader, String className, Class<?> classBeingRedefined,
                            ProtectionDomain protectionDomain, byte[] classfileBuffer)
            throws IllegalClassFormatException
    {
        byte[] classBytes = instrumentClass(className, classfileBuffer);
        if (classBytes != null) {
            // TODO: Do I need to do this still?
            for (String pn : module.getPackages()) {
                thisModule.addOpens(pn, module);
            }
            return classBytes;
        }
        return null;
    }

    @Override
    public String toString() {
        return "AgentClassFileTransformer(JDK 9)";
    }
}
