package org.valhalla.plogger.instrumentation.bytecode.constantpool;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataInputStream;
import java.io.IOException;

public class ConstantPoolEntryFactory implements ConstantPoolEntryTag {

    public static ConstantPoolEntry create(ClassFile classFile, DataInputStream dis) throws IOException, ConstantPoolEntryException {
        int tag = dis.readUnsignedByte();
        int len;
        byte buf[], buf2[];
        switch(tag) {
            case UTF8:
                len = dis.readUnsignedShort();
                buf = new byte[len];
                dis.read(buf);
                return new ConstantUtf8(len, buf);
            case STRING:
                return new ConstantString(classFile, dis.readUnsignedShort());
            case INTEGER:
                buf = new byte[4];
                dis.read(buf);
                return new ConstantInteger(buf);
            case LONG:
                buf = new byte[4];
                dis.read(buf);
                buf2 = new byte[4];
                dis.read(buf);
                return new ConstantLong(buf,buf2);
            case FLOAT:
                buf = new byte[4];
                dis.read(buf);
                return new ConstantFloat(buf);
            case DOUBLE:
                buf = new byte[4];
                dis.read(buf);
                buf2 = new byte[4];
                dis.read(buf);
                return new ConstantDouble(buf,buf2);
            case CLASS:
                return new ConstantClass(classFile, dis.readUnsignedShort());
            case FIELD:
                return new ConstantFieldRef(classFile, dis.readUnsignedShort(), dis.readUnsignedShort());
            case METHOD:
                return new ConstantMethodRef(classFile, dis.readUnsignedShort(), dis.readUnsignedShort());
            case INTERFACE_METHOD:
                return new ConstantInterfaceMethodRef(classFile, dis.readUnsignedShort(), dis.readUnsignedShort());
            case NAME_AND_TYPE:
                return new ConstantNameAndType(classFile, dis.readUnsignedShort(), dis.readUnsignedShort());
            case METHOD_HANDLE:
                return new ConstantMethodHandle(classFile, dis.readUnsignedByte(), dis.readUnsignedShort());
            case METHOD_TYPE:
                return new ConstantMethodType(classFile, dis.readUnsignedShort());
            case DYNAMIC:
                return new ConstantDynamic(classFile, dis.readUnsignedShort(), dis.readUnsignedShort());
            case INVOKE_DYNAMIC:
                return new ConstantInvokeDynamic(classFile, dis.readUnsignedShort(), dis.readUnsignedShort());
            case MODULE:
                return new ConstantModule(classFile, dis.readUnsignedShort());
            case PACKAGE:
                return new ConstantPackage(classFile, dis.readUnsignedShort());
            default:
                throw new ConstantPoolEntryException("Invalid Constant Pool Entry: " + tag);
        }

    }
}
