package org.valhalla.instrumentation.plogger.agent.bytecode.classes;

import org.valhalla.instrumentation.plogger.agent.bytecode.attributes.ClassAttribute;
import org.valhalla.instrumentation.plogger.agent.bytecode.attributes.ClassAttributeFactory;
import org.valhalla.instrumentation.plogger.agent.bytecode.constantpool.ConstantPoolEntry;
import org.valhalla.instrumentation.plogger.agent.bytecode.constantpool.ConstantPoolEntryException;
import org.valhalla.instrumentation.plogger.agent.bytecode.constantpool.ConstantPoolEntryFactory;

import java.io.ByteArrayInputStream;
import java.io.DataInputStream;
import java.io.IOException;

public class ClassFile {
    private byte magic[];
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
            dis.read(classFile.magic);
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
            classFile.cpools = loadConstantPool(dis);
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

    private static ConstantPoolEntry[] loadConstantPool(DataInputStream dis) throws IOException, ConstantPoolEntryException {
        int constant_pool_count = dis.readUnsignedShort();
        ConstantPoolEntry[] cpool = new ConstantPoolEntry[constant_pool_count];
        for( int idx = 1 ; idx < constant_pool_count ; idx++) {
            cpool[idx] = ConstantPoolEntryFactory.create(dis);
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
}
