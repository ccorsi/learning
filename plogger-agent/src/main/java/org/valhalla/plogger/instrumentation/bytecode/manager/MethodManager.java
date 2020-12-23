package org.valhalla.plogger.instrumentation.bytecode.manager;
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

import org.valhalla.plogger.instrumentation.Debug;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileException;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileWriter;
import org.valhalla.plogger.instrumentation.bytecode.constantpool.ConstantUtf8;

import java.io.DataInputStream;
import java.io.DataOutput;
import java.io.IOException;
import java.util.Arrays;

public class MethodManager implements ClassFileWriter {
    private static final Debug debug = Debug.getDebug("method");
    private static final Debug debugException = Debug.getDebug("method.exception");

    private static int instrumentAccess;
    public static final int ACC_PUBLIC;
    public static final int ACC_PRIVATE   = 0x0002;
    public static final int ACC_PROTECTED = 0x0004;
    private static final int ACC_NATIVE = 0x0100;
    private static final int ACC_ABSTRACT = 0x0400;

    static {
        ACC_PUBLIC       = 0x0001;
        instrumentAccess = ACC_PUBLIC;
    }

    //    private final ClassManager classManager;
    private final String name;
    private final String signature;
    private int nameIndex;
    private int descriptorIndex;
    private AttributeManager[] attributeManagers;
    private int accessFlags;

    public MethodManager(ConstantPoolManager constantPoolManager, DataInputStream dis) {
        try {
            this.accessFlags = dis.readUnsignedShort();
            this.nameIndex = dis.readUnsignedShort();
            ConstantUtf8 utf8 = constantPoolManager.getEntry(nameIndex);
            this.name = utf8.getString();
            this.descriptorIndex = dis.readUnsignedShort();
            utf8 = constantPoolManager.getEntry(descriptorIndex);
            this.signature = utf8.getString();
            int size = dis.readUnsignedShort();
            this.attributeManagers = new AttributeManager[size];
            for(int idx = 0 ; idx < size ; idx++) {
                this.attributeManagers[idx] = AttributeManagerFactory.create(dis, constantPoolManager);
            }
        } catch (IOException e) {
            throw new ClassFileException(e);
        }
    }

    public static void setIntrumentation(int instrumentAccess) {
        MethodManager.instrumentAccess = instrumentAccess;
    }

    // This will return this MethodManager ConstantPoolManager instance
//    public ConstantPoolManager getConstantPoolManager() {
//        return classManager.getConstantPoolManager();
//    }

    private <E extends AttributeManager> E getAttributeManager(Class<E> classType) {
        for(AttributeManager attributeManager : attributeManagers) {
//            System.out.println("Comparing AttributeManager: " + attributeManager);
            if (attributeManager != null && classType.isInstance(attributeManager)) {
                return classType.cast(attributeManager);
            }
        }
        return null;
    }

    private CodeAttributeManager codeAttributeManager = null;

    // This will return the CodeAttributeManager associated with this method
    public CodeAttributeManager getCodeAttributeManager() {
        if (codeAttributeManager == null) {
            codeAttributeManager = getAttributeManager(CodeAttributeManager.class);
            if (codeAttributeManager == null) {
                codeAttributeManager = CodeAttributeManager.getDefaultCodeAttributeManager();
            }
        }

        return codeAttributeManager;
    }

    // This will return the current method access flags.
    public int getAccessFlags() {
        return accessFlags;
    }

    public String getName() {
        return name;
    }

    public String getSignature() {
        return signature;
    }

    public boolean instrument(ClassManager classManager) {
        // Don't instrument static methods.
//        if (! "<clinit>".equals(name)) {
        // Only instrument methods that are passed parameters
        if ( ! signature.contains("()") ) {
            try {
                // TODO: We need to allow the users the ability to determine which methods can be instrumented.
//                // Only process a method that are public and parameters are being passed.
//                if ((accessFlags & ACC_PUBLIC) != 0 /*&& !signature.contains("()")*/) {
//                    // Check that the method is not abstract, native, ...
//                    if ((accessFlags & ACC_NATIVE) == 0 && (accessFlags & ACC_ABSTRACT) == 0) {
//                        // We are now ready to instrument the current method.
//                        CodeAttributeManager codeAttributeManager = getCodeAttributeManager();
//                        if (codeAttributeManager != null) {
//                            return codeAttributeManager.instrument(classManager, this);
//                        }
//                    }
//                } else if ((accessFlags & ACC_PUBLIC) == 0) {
//                    // We are now ready to instrument the current method.
//                    CodeAttributeManager codeAttributeManager = getCodeAttributeManager();
//                    if (codeAttributeManager != null) {
//                        return codeAttributeManager.instrument(classManager, this);
//                    }
//                }
                // We are now ready to instrument the current method.
                if ( (accessFlags & instrumentAccess) != 0 ) {
                    return getCodeAttributeManager().instrument(classManager, this);
                }
            } catch (ClassFileException e) {
                if (debugException.isDebug()) {
                    debugException.debug("An exception was raised when instrumenting method: " + getName(), e);
                }
                throw e;
            }
        }

        return false;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        if (debug.isDebug()) {
            debug.debug("Storing method " + getName());
        }
        os.writeShort(accessFlags);
        os.writeShort(nameIndex);
        os.writeShort(descriptorIndex);
        os.writeShort(attributeManagers.length);
        for (AttributeManager attributeManager : attributeManagers) {
            attributeManager.write(os);
        }
    }

    @Override
    public String toString() {
        return "MethodManager{" +
                "name='" + name + '\'' +
                ", signature='" + signature + '\'' +
                ", attributeManagers=" + Arrays.toString(attributeManagers) +
                ", accessFlags=" + accessFlags +
                '}';
    }
}
