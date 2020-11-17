package org.valhalla.plogger.instrumentation.bytecode.classes;

import org.valhalla.plogger.instrumentation.bytecode.attributes.ClassAttribute;
import org.valhalla.plogger.instrumentation.bytecode.attributes.ClassAttributeFactory;
import org.valhalla.plogger.instrumentation.bytecode.constantpool.*;

import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.IOException;
import java.util.Arrays;
import java.util.Iterator;
import java.util.NoSuchElementException;

public class ClassFile {
    private byte[] magic;
    private int vminor;
    private int vmajar;
    private ConstantPoolEntry[] cpools;
    private int accessFlags;
    private int thisClassIndex;
    private int superClassIndex;
    private int[] interfaces;
    private ClassField[] fields;
    private ClassMethod[] methods;
    private ClassAttribute[] attributes;

    private ClassFile() {}

    public static ClassFile load(String className, byte[] data) throws ClassFileException {
        ByteArrayInputStream is = new ByteArrayInputStream(data);
        try (DataInputStream dis = new DataInputStream(is)) {
            ClassFile classFile = new ClassFile();
            classFile.magic = new byte[4];
            int read = dis.read(classFile.magic);
            if (read != classFile.magic.length) {
                throw new ClassFileException("Unable to read magic value for class: " + className);
            }
            // validate magic string
            byte[] expectedMagic = {(byte) 0xCA, (byte) 0xFE, (byte) 0xBA, (byte) 0xBE};
            for(int idx = 0 ; idx < expectedMagic.length ; idx++) {
                if (classFile.magic[idx] != expectedMagic[idx]) {
                    throw new ClassFileException("Invalid class file magic value for class: " + className);
                }
            }
            // Extract the class file version
            classFile.vminor = dis.readUnsignedShort();
            classFile.vmajar = dis.readUnsignedShort();
            // Extract the class file constant pool entries
            classFile.cpools = loadConstantPool(classFile, dis);
            // Extract the class file access flags
            classFile.accessFlags = dis.readUnsignedShort();
            // Extract the class file this class constant pool entry index
            classFile.thisClassIndex = dis.readUnsignedShort();
            // Extract the class file super class constant pool entry index
            classFile.superClassIndex = dis.readUnsignedShort();
            // Extract the class file interfaces
            int count = dis.readUnsignedShort();
            classFile.interfaces = new int[count];
            for(int idx = 0 ; idx < count ; idx++) {
                classFile.interfaces[idx] = dis.readUnsignedShort();
                // TODO: Validate each interface.
                validateInterface(classFile, classFile.interfaces[idx]);
            }
            // Extract the class file fields
            count = dis.readUnsignedShort();
            classFile.fields = new ClassField[count];
            for(int idx = 0 ; idx < count ; idx++) {
                classFile.fields[idx] = ClassField.load(classFile, dis);
            }
            // Extract the class file methods
            count = dis.readUnsignedShort();
            classFile.methods = new ClassMethod[count];
            for(int idx = 0 ; idx < count ; idx++) {
                classFile.methods[idx] = ClassMethod.load(classFile, dis);
            }
            // Extract the class file attributes
            count = dis.readUnsignedShort();
            classFile.attributes = new ClassAttribute[count];
            for(int idx = 0 ; idx < count ; idx++) {
                classFile.attributes[idx] = ClassAttributeFactory.load(classFile, dis);
            }
            return classFile;
        } catch (Throwable exception) {
            throw new ClassFileException("An exception was caught while loading class: " + className, exception);
        }
    }

    private static void validateInterface(ClassFile classFile, int interfaceIndex) throws ClassFileException {
        ConstantPoolEntry[] cp = classFile.getConstantPool();
        if (interfaceIndex < 1 || interfaceIndex >= cp.length) {
            // TODO: throw exception
            throw new ClassFileException("Invalid interface index");
        }
    }

    private static ConstantPoolEntry[] loadConstantPool(ClassFile classFile, DataInputStream dis) throws IOException, ConstantPoolEntryException {
        int constant_pool_count = dis.readUnsignedShort();
        ConstantPoolEntry[] cpool = new ConstantPoolEntry[constant_pool_count];
        for( int idx = 1 ; idx < constant_pool_count ; ) {
            cpool[idx] = ConstantPoolEntryFactory.create(classFile, dis);
            // System.out.println("Created Constant Pool Entry: " + cpool[idx]);
            idx += cpool[idx].entries();
        }
        return cpool;
    }

    public int getMinorVersion() {
        return vminor;
    }

    public int getMajorVersion() {
        return vmajar;
    }

    public ConstantPoolEntry[] getConstantPool() {
        return cpools;
    }

    @Override
    public String toString() {
        return "ClassFile{" +
                "magic=" + Arrays.toString(magic) +
                ", minor version=" + vminor +
                ", majar version=" + vmajar +
                ", Constant Pool Entries=" + Arrays.toString(cpools) +
                ", accessFlags=" + accessFlags +
                ", thisClassIndex=" + thisClassIndex +
                ", superClassIndex=" + superClassIndex +
                ", interfaces=" + Arrays.toString(interfaces) +
                ", fields=" + Arrays.toString(fields) +
                ", methods=" + Arrays.toString(methods) +
                ", attributes=" + Arrays.toString(attributes) +
                '}';
    }

    public String getThisClassName() {
        ConstantClass entry = (ConstantClass) cpools[thisClassIndex];
        return entry.getClassName(cpools);
    }

    public String getSuperClassName() {
        if (superClassIndex == 0) {
            return "";
        } else {
            ConstantClass entry = (ConstantClass) cpools[superClassIndex];
            return entry.getClassName(cpools);
        }
    }

    public Iterator<ClassMethod> getMethods() {
        Iterator<ClassMethod> iterator = new Iterator<ClassMethod>() {
            ClassMethod[] methods = ClassFile.this.methods.clone();
            int idx = 0;

            @Override
            public boolean hasNext() {
                return idx < methods.length;
            }

            @Override
            public ClassMethod next() {
                if (idx >= methods.length) {
                    throw new NoSuchElementException("No element remain");
                }
                return methods[idx++];
            }

            @Override
            public void remove() {
                // do nothing
            }
        };
        return iterator;
    }
}
