package org.valhalla.instrumentation.plogger.agent.bytecode.constantpool;

import org.valhalla.instrumentation.plogger.agent.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;

public class ConstantMethodHandle implements ConstantPoolEntry {
    private final int referenceKind;
    private final int referenceIndex;

    public ConstantMethodHandle(int referenceKind, int referenceIndex) {
        this.referenceKind = referenceKind;
        this.referenceIndex = referenceIndex;
    }

    @Override
    public void validate(ClassFile classFile) throws ConstantPoolEntryException {
        ConstantPoolEntry[] cpool = classFile.getConstantPool();
        if (referenceIndex < 1 || referenceIndex >= cpool.length) {
            throw new ConstantPoolEntryException("Invalid reference index: " + referenceIndex
                    + " it should be between [1," + (cpool.length - 1) + "].");
        }
        // TODO: extract the checks from the switch block
        switch(referenceKind) {
            case 1: case 2: case 3: case 4:
                if ( ! (cpool[referenceIndex] instanceof ConstantFieldRef) ) {
                    throw new ConstantPoolEntryException("Invalid reference index: " + referenceIndex
                            + " it should be a constant field reference.");
                }
                break;
            case 5:
                if ( ! (cpool[referenceIndex] instanceof ConstantMethodRef) ) {
                    throw new ConstantPoolEntryException("Invalid reference index: " + referenceIndex
                            + " it should be a constant method reference.");
                }
            {
                AbstractConstantRef ref = (AbstractConstantRef) cpool[referenceIndex];
                ConstantNameAndType nameAndType = ref.getNameAndType(cpool);
                ConstantUtf8 utf8 = nameAndType.getDescriptor(cpool);
                String value = utf8.getString();
                if ("<init>".equals(value) || "<clinit>".equals(value)) {
                    throw new ConstantPoolEntryException("Referenced method is must not be <init> or <clinit>.");
                }
            }
                break;
            case 6:
            case 7:
                if ( ! (cpool[referenceIndex] instanceof ConstantMethodRef) &&
                     ! (cpool[referenceIndex] instanceof ConstantInterfaceMethodRef)) {
                    throw new ConstantPoolEntryException("Invalid reference index: " + referenceIndex
                            + " it should be a constant method reference or constant interface method reference.");
                }
            {
                AbstractConstantRef ref = (AbstractConstantRef) cpool[referenceIndex];
                ConstantNameAndType nameAndType = ref.getNameAndType(cpool);
                ConstantUtf8 utf8 = nameAndType.getDescriptor(cpool);
                String value = utf8.getString();
                if ("<init>".equals(value) || "<clinit>".equals(value)) {
                    throw new ConstantPoolEntryException("Referenced method is must not be <init> or <clinit>.");
                }
            }
                break;
            case 8:
                if ( ! (cpool[referenceIndex] instanceof ConstantMethodRef) ) {
                    throw new ConstantPoolEntryException("Invalid reference index: " + referenceIndex
                            + " it should be a constant method reference.");
                }
            {
                AbstractConstantRef ref = (AbstractConstantRef) cpool[referenceIndex];
                ConstantNameAndType nameAndType = ref.getNameAndType(cpool);
                ConstantUtf8 utf8 = nameAndType.getDescriptor(cpool);
                String value = utf8.getString();
                if (!"<init>".equals(value)) {
                    throw new ConstantPoolEntryException("Referenced method must be <init>.");
                }
            }
                break;
            case 9:
                if ( ! (cpool[referenceIndex] instanceof ConstantInterfaceMethodRef) ) {
                    throw new ConstantPoolEntryException("Invalid reference index: " + referenceIndex
                            + " it should be a constant interface method reference.");
                }
            {
                AbstractConstantRef ref = (AbstractConstantRef) cpool[referenceIndex];
                ConstantNameAndType nameAndType = ref.getNameAndType(cpool);
                ConstantUtf8 utf8 = nameAndType.getDescriptor(cpool);
                String value = utf8.getString();
                if ("<init>".equals(value) || "<clinit>".equals(value)) {
                    throw new ConstantPoolEntryException("Referenced method is must not be <init> or <clinit>.");
                }
            }
                break;
            default:
                throw new ConstantPoolEntryException("Invalid reference kind: " + referenceKind);
        }
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(METHOD_HANDLE);
        os.writeByte(referenceKind);
        os.writeShort(referenceIndex);
    }
}
