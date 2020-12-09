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

import org.valhalla.plogger.instrumentation.bytecode.attributes.ClassAttribute;
import org.valhalla.plogger.instrumentation.bytecode.classes.*;
import org.valhalla.plogger.instrumentation.bytecode.constantpool.ConstantClass;
import org.valhalla.plogger.instrumentation.bytecode.constantpool.ConstantUtf8;

import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.DataOutput;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Iterator;
import java.util.List;

public class ClassManager implements ClassFileWriter {

    private static final byte[] expectedMagic = {(byte) 0xCA, (byte) 0xFE, (byte) 0xBA, (byte) 0xBE};

    private final ConstantPoolManager constantPoolManager;
    private final MethodManager[] methodManagers;
    private final int accessFlags;
    private final int thisClassIndex;
    private final int superClassIndex;
    private final InterfaceManager interfaceManager;
    private final int minorVersion;
    private final int majorVersion;
    private final FieldManager[] fieldManagers;
    private final AttributeManager[] attributeManagers;
    private final String className;

    public ClassManager(ClassFile classFile) {
        this.className = classFile.getThisClassName();
        this.minorVersion = classFile.getMinorVersion();
        this.majorVersion = classFile.getMajorVersion();
        this.constantPoolManager = new ConstantPoolManager(classFile);
        this.accessFlags = classFile.getAccessFlags();
        this.thisClassIndex = classFile.getThisClassIndex();
        this.superClassIndex = classFile.getSuperClassIndex();
        this.interfaceManager = new InterfaceManager(classFile.getInterfaces());
        this.fieldManagers = initializeFieldManagerList(classFile);
        this.methodManagers = initializeMethodManagerList(classFile);
        this.attributeManagers = initializeAttributeManagerList(classFile);
    }

    public ClassManager(String className, byte[] bytes) throws ClassFileException {
        this.className = className;
            ByteArrayInputStream is = new ByteArrayInputStream(bytes);
            try (DataInputStream dis = new DataInputStream(is)) {
                byte[] magic = new byte[4];
                int read = dis.read(magic);
                if (read != magic.length) {
                    throw new ClassFileException("Unable to read magic value for class: " + className);
                }
                // validate magic string
                for(int idx = 0; idx < expectedMagic.length ; idx++) {
                    if (magic[idx] != expectedMagic[idx]) {
                        throw new ClassFileException("Invalid class file magic value for class: " + className);
                    }
                }
                // Extract the class file version
                minorVersion = dis.readUnsignedShort();
                majorVersion = dis.readUnsignedShort();
                // Extract the class file constant pool entries
                constantPoolManager = new ConstantPoolManager(dis);
                // Extract the class file access flags
                accessFlags = dis.readUnsignedShort();
                // Extract the class file this class constant pool entry index
                thisClassIndex = dis.readUnsignedShort();
                // Extract the class file super class constant pool entry index
                superClassIndex = dis.readUnsignedShort();
                // Extract the class file interfaces
                int size = dis.readUnsignedShort();
                int[] interfaces = new int[size];
//                for(int idx = 0 ; idx < size ; idx++) {
//                    interfaces[idx] = dis.readUnsignedShort();
//                    // TODO: Validate each interface.
////                    validateInterface(classFile, classFile.interfaces[idx]);
//                }
                interfaceManager = new InterfaceManager(interfaces);
                // Extract the class file fields
                size = dis.readUnsignedShort();
                this.fieldManagers = new FieldManager[size];
                for(int idx = 0 ; idx < size ; idx++) {
                    fieldManagers[idx] = new FieldManager(constantPoolManager, dis);
                }
                // Extract the class file methods
                size = dis.readUnsignedShort();
                this.methodManagers = new MethodManager[size];
                for(int idx = 0 ; idx < size ; idx++) {
                    methodManagers[idx] = new MethodManager(constantPoolManager, dis);
                }
                // Extract the class file attributes
                size = dis.readUnsignedShort();
                this.attributeManagers = new AttributeManager[size];
                for(int idx = 0 ; idx < size ; idx++) {
                    attributeManagers[idx] = AttributeManagerFactory.create(dis, constantPoolManager);
                }
        } catch(IOException ioe) {
            throw new ClassFileException(ioe);
        }
    }

    private AttributeManager[] initializeAttributeManagerList(ClassFile classFile) {
        List<ClassAttribute> attributes = classFile.getAttributes();
        AttributeManager[] list = new AttributeManager[attributes.size()];

        for(int idx = 0 ; idx < list.length ; idx++) {
            list[idx] = AttributeManagerFactory.create(attributes.get(idx));
        }
        return list;
    }

    private FieldManager[] initializeFieldManagerList(ClassFile classFile) {
        List<ClassField> fields = classFile.getFields();
        FieldManager list[] = new FieldManager[fields.size()];
        for(int idx = 0 ; idx < list.length ; idx++) {
            list[idx] = new FieldManager(fields.get(idx));
        }
        return list;
    }

    private MethodManager[] initializeMethodManagerList(ClassFile classFile) {
        List<MethodManager> managers = new ArrayList<MethodManager>();
        for (Iterator<ClassMethod> it = classFile.getMethods(); it.hasNext(); ) {
            ClassMethod method = it.next();
            managers.add(new MethodManager(method.getName(classFile), method.getSignature(classFile), this, method ));
        }
        return managers.toArray(new MethodManager[managers.size()]);
    }

    public int getMajorVersion() {
        return majorVersion;
    }

    // This will return the associated ConstantPoolManager instance
    public ConstantPoolManager getConstantPoolManager() {
        return constantPoolManager;
    }

    // This will return the associated MethodManager for the given
    // method name
    public MethodManager getMethodManager(String name, String signature) {
        for(MethodManager methodManager : methodManagers) {
            if (name.equals(methodManager.getName()) && signature.equals(methodManager.getSignature())) {
                return methodManager;
            }
        }
        return null;
    }

    public String getClassName() {
        ConstantClass constantClass = constantPoolManager.getEntry(thisClassIndex);
        ConstantUtf8 utf8 = constantPoolManager.getEntry(constantClass.getNameIndex());
        return utf8.getString();
    }

    public int getAccessFlags() {
        return accessFlags;
    }

    public boolean instrument() {
        boolean instrumented = false;
        for(MethodManager method : methodManagers) {
            instrumented |= method.instrument(this);
            // TODO: Use a debug property to provide better debugging possibilities
//            boolean current = method.instrument(this);
//            instrumented |= current;
//            System.out.println("Instrumented method " + method.getName() + " was " + Boolean.toString(current));
        }
        return instrumented;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.write(expectedMagic);
        os.writeShort(minorVersion);
        os.writeShort(majorVersion);
        constantPoolManager.write(os);
        os.writeShort(accessFlags);
        os.writeShort(thisClassIndex);
        os.writeShort(superClassIndex);
        interfaceManager.write(os);
        os.writeShort(fieldManagers.length);
        for (FieldManager fieldManager : fieldManagers) {
            fieldManager.write(os);
        }
        os.writeShort(methodManagers.length);
        for (MethodManager methodManager : methodManagers) {
            methodManager.write(os);
        }
        os.writeShort(attributeManagers.length);
        for (AttributeManager attributeManager : attributeManagers) {
            attributeManager.write(os);
        }
    }

    @Override
    public String toString() {
        return "ClassManager{" +
                "constantPoolManager=" + constantPoolManager +
                ", methodManagers=" + Arrays.toString(methodManagers) +
                ", accessFlags=" + accessFlags +
                ", thisClassIndex=" + thisClassIndex +
                ", superClassIndex=" + superClassIndex +
                ", interfaceManager=" + interfaceManager +
                ", minorVersion=" + minorVersion +
                ", majorVersion=" + majorVersion +
                ", fieldManagers=" + Arrays.toString(fieldManagers) +
                ", attributeManagers=" + Arrays.toString(attributeManagers) +
                ", className='" + className + '\'' +
                '}';
    }

    public MethodManager[] getMethods() {
        return methodManagers;
    }
}
