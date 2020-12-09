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

import java.io.DataOutput;
import java.io.IOException;

public class ConstantMethodHandle implements ConstantPoolEntry {
    private final int referenceKind;
    private final int referenceIndex;
//    private final ClassFile classFile;

    public ConstantMethodHandle(int referenceKind, int referenceIndex) {
        this.referenceKind = referenceKind;
        this.referenceIndex = referenceIndex;
//        this.classFile = classFile;
    }

//    @Override
//    public void validate() throws ConstantPoolEntryException {
//        ConstantPoolEntry[] cpool = classFile.getConstantPool();
//        if (referenceIndex < 1 || referenceIndex >= cpool.length) {
//            throw new ConstantPoolEntryException("Invalid reference index: " + referenceIndex
//                    + " it should be between [1," + (cpool.length - 1) + "].");
//        }
//        // TODO: extract the checks from the switch block
//        switch(referenceKind) {
//            case 1: case 2: case 3: case 4:
//                if ( ! (cpool[referenceIndex] instanceof ConstantFieldRef) ) {
//                    throw new ConstantPoolEntryException("Invalid reference index: " + referenceIndex
//                            + " it should be a constant field reference.");
//                }
//                break;
//            case 5:
//                if ( ! (cpool[referenceIndex] instanceof ConstantMethodRef) ) {
//                    throw new ConstantPoolEntryException("Invalid reference index: " + referenceIndex
//                            + " it should be a constant method reference.");
//                }
//            {
//                AbstractConstantRef ref = (AbstractConstantRef) cpool[referenceIndex];
//                ConstantNameAndType nameAndType = ref.getNameAndType(cpool);
//                ConstantUtf8 utf8 = nameAndType.getDescriptor(cpool);
//                String value = utf8.getString();
//                if ("<init>".equals(value) || "<clinit>".equals(value)) {
//                    throw new ConstantPoolEntryException("Referenced method is must not be <init> or <clinit>.");
//                }
//            }
//                break;
//            case 6:
//            case 7:
//                if ( ! (cpool[referenceIndex] instanceof ConstantMethodRef) &&
//                     ! (cpool[referenceIndex] instanceof ConstantInterfaceMethodRef)) {
//                    throw new ConstantPoolEntryException("Invalid reference index: " + referenceIndex
//                            + " it should be a constant method reference or constant interface method reference.");
//                }
//            {
//                AbstractConstantRef ref = (AbstractConstantRef) cpool[referenceIndex];
//                ConstantNameAndType nameAndType = ref.getNameAndType(cpool);
//                ConstantUtf8 utf8 = nameAndType.getDescriptor(cpool);
//                String value = utf8.getString();
//                if ("<init>".equals(value) || "<clinit>".equals(value)) {
//                    throw new ConstantPoolEntryException("Referenced method is must not be <init> or <clinit>.");
//                }
//            }
//                break;
//            case 8:
//                if ( ! (cpool[referenceIndex] instanceof ConstantMethodRef) ) {
//                    throw new ConstantPoolEntryException("Invalid reference index: " + referenceIndex
//                            + " it should be a constant method reference.");
//                }
//            {
//                AbstractConstantRef ref = (AbstractConstantRef) cpool[referenceIndex];
//                ConstantNameAndType nameAndType = ref.getNameAndType(cpool);
//                ConstantUtf8 utf8 = nameAndType.getDescriptor(cpool);
//                String value = utf8.getString();
//                if (!"<init>".equals(value)) {
//                    throw new ConstantPoolEntryException("Referenced method must be <init>.");
//                }
//            }
//                break;
//            case 9:
//                if ( ! (cpool[referenceIndex] instanceof ConstantInterfaceMethodRef) ) {
//                    throw new ConstantPoolEntryException("Invalid reference index: " + referenceIndex
//                            + " it should be a constant interface method reference.");
//                }
//            {
//                AbstractConstantRef ref = (AbstractConstantRef) cpool[referenceIndex];
//                ConstantNameAndType nameAndType = ref.getNameAndType(cpool);
//                ConstantUtf8 utf8 = nameAndType.getDescriptor(cpool);
//                String value = utf8.getString();
//                if ("<init>".equals(value) || "<clinit>".equals(value)) {
//                    throw new ConstantPoolEntryException("Referenced method is must not be <init> or <clinit>.");
//                }
//            }
//                break;
//            default:
//                throw new ConstantPoolEntryException("Invalid reference kind: " + referenceKind);
//        }
//    }

    @Override
    public int entries() {
        return 1;
    }

    @Override
    public String toString() {
        return "ConstantMethodHandle{" +
                "referenceKind=" + referenceKind +
                ", referenceIndex=" + referenceIndex +
                '}';
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeByte(METHOD_HANDLE);
        os.writeByte(referenceKind);
        os.writeShort(referenceIndex);
    }
}
