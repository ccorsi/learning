package org.valhalla.plogger.instrumentation.bytecode.constantpool;

import jdk.vm.ci.meta.Constant;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.valhalla.plogger.instrumentation.bytecode.manager.ConstantPoolManager;

import java.io.*;

import static org.junit.jupiter.api.Assertions.*;

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

class ConstantPoolEntryTest {

    @Test
    void constantClassWrite() throws ConstantPoolEntryException, IOException {
        ConstantClass entry = new ConstantClass(1);
        executeWrite(entry,  "Returned constant pool entry was not of type constant class");
    }

    @Test
    void constantDoubleWrite() throws ConstantPoolEntryException, IOException {
        ConstantDouble entry = new ConstantDouble(new byte[] { 1, 2, 3, 4 }, new byte[] { 5, 6, 7, 8 });
        executeWrite(entry,  "Returned constant pool entry was not of type constant double");
    }

    @Test
    void constantDynamicWrite() throws ConstantPoolEntryException, IOException {
        ConstantDynamic entry = new ConstantDynamic(1,2);
        executeWrite(entry,  "Returned constant pool entry was not of type constant dynamic");
    }

    @Test
    void constantFieldRefWrite() throws ConstantPoolEntryException, IOException {
        ConstantFieldRef entry = new ConstantFieldRef(1, 2);
        executeWrite(entry,  "Returned constant pool entry was not of type constant field ref");
    }

    @Test
    void constantFloatWrite() throws ConstantPoolEntryException, IOException {
        ConstantFloat entry = new ConstantFloat(new byte[] { 1, 2, 3, 4 });
        executeWrite(entry,  "Returned constant pool entry was not of type constant float");
    }

    @Test
    void constantIntegerWrite() throws ConstantPoolEntryException, IOException {
        ConstantInteger entry = new ConstantInteger(new byte[] { 1, 2, 3, 4 });
        executeWrite(entry,  "Returned constant pool entry was not of type constant integer");
    }

    @Test
    void constantInterfaceMethodRefWrite() throws ConstantPoolEntryException, IOException {
        ConstantInterfaceMethodRef entry = new ConstantInterfaceMethodRef(1, 2);
        executeWrite(entry,  "Returned constant pool entry was not of type constant interface method ref");
    }

    @Test
    void constantInvokeDynamicWrite() throws ConstantPoolEntryException, IOException {
        ConstantInvokeDynamic entry = new ConstantInvokeDynamic(1, 2);
        executeWrite(entry,  "Returned constant pool entry was not of type constant invoke dynamic");
    }

    @Test
    void constantLongWrite() throws ConstantPoolEntryException, IOException {
        ConstantLong entry = new ConstantLong(new byte[] { 1, 2, 3, 4 }, new byte[] { 5, 6, 7, 8 });
        executeWrite(entry,  "Returned constant pool entry was not of type constant long");
    }

    @Test
    void constantMethodHandleWrite() throws ConstantPoolEntryException, IOException {
        ConstantMethodHandle entry = new ConstantMethodHandle(1, 2);
        executeWrite(entry,  "Returned constant pool entry was not of type constant method handle");
    }

    @Test
    void constantMethodRefWrite() throws ConstantPoolEntryException, IOException {
        ConstantMethodRef entry = new ConstantMethodRef(1, 2);
        executeWrite(entry,  "Returned constant pool entry was not of type constant method ref");
    }

    @Test
    void constantMethodTypeWrite() throws ConstantPoolEntryException, IOException {
        ConstantMethodType entry = new ConstantMethodType(1);
        executeWrite(entry,  "Returned constant pool entry was not of type constant method type");
    }

    @Test
    void constantModuleWrite() throws ConstantPoolEntryException, IOException {
        ConstantModule entry = new ConstantModule(1);
        executeWrite(entry,  "Returned constant pool entry was not of type constant module");
    }

    @Test
    void constantNameAndTypeWrite() throws ConstantPoolEntryException, IOException {
        ConstantNameAndType entry = new ConstantNameAndType(1,2);
        executeWrite(entry,  "Returned constant pool entry was not of type constant name and type");
    }

    @Test
    void constantPackageWrite() throws ConstantPoolEntryException, IOException {
        ConstantPackage entry = new ConstantPackage(1);
        executeWrite(entry,  "Returned constant pool entry was not of type constant package");
    }

    @Test
    void constantStringWrite() throws ConstantPoolEntryException, IOException {
        ConstantString entry = new ConstantString(1);
        executeWrite(entry,  "Returned constant pool entry was not of type constant string");
    }

    @Test
    void constantUtf8Write() throws ConstantPoolEntryException, IOException {
        byte[] bytes = "This is a simple string".getBytes();
        ConstantUtf8 entry = new ConstantUtf8(bytes.length, bytes);
        executeWrite(entry,  "Returned constant pool entry was not of type constant utf8");
    }

    private void executeWrite(ConstantPoolEntry entry, String s) throws IOException, ConstantPoolEntryException {
        Class<? extends ConstantPoolEntry> type = entry.getClass();
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        try (DataOutputStream dos = new DataOutputStream(bos)) {
            entry.write(dos);
        }
        ByteArrayInputStream bis = new ByteArrayInputStream(bos.toByteArray());
        try (DataInputStream dis = new DataInputStream(bis)) {
            entry = ConstantPoolEntryFactory.create(dis);
            Assertions.assertTrue(entry.getClass() == type,
                    s);
        }
    }

}