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

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileException;

import java.io.DataInputStream;
import java.io.IOException;

public class InstructionEntryFactory {

    // Control Instructions Operand Codes
    public static final int NOP = 0x00;
    public static final int ACONST_NULL = 0x01;
    public static final int ICONST_M1 = 0x02;
    public static final int ICONST_0 = 0x03;
    public static final int ICONST_1 = 0x04;
    public static final int ICONST_2 = 0x05;
    public static final int ICONST_3 = 0x06;
    public static final int ICONST_4 = 0x07;
    public static final int ICONST_5 = 0x08;
    public static final int LCONST_0 = 0x09;
    public static final int LCONST_1 = 0x0a;
    public static final int FCONST_0 = 0x0b;
    public static final int FCONST_1 = 0x0c;
    public static final int FCONST_2 = 0x0d;
    public static final int DCONST_0 = 0x0e;
    public static final int DCONST_1 = 0x0f;
    public static final int BIPUSH = 0x10;
    public static final int SIPUSH = 0x11;
    public static final int LDC = 0x12;
    public static final int LDC_W = 0x13;
    public static final int LDC2_W = 0x14;

    // Load Instructions Operand Codes
    public static final int ILOAD = 0x15;
    public static final int LLOAD = 0x16;
    public static final int FLOAD = 0x17;
    public static final int DLOAD = 0x18;
    public static final int ALOAD = 0x19;
    public static final int ILOAD_0 = 0x1a;
    public static final int ILOAD_1 = 0x1b;
    public static final int ILOAD_2 = 0x1c;
    public static final int ILOAD_3 = 0x1d;
    public static final int LLOAD_0 = 0x1e;
    public static final int LLOAD_1 = 0x1f;
    public static final int LLOAD_2 = 0x20;
    public static final int LLOAD_3 = 0x21;
    public static final int FLOAD_0 = 0x22;
    public static final int FLOAD_1 = 0x23;
    public static final int FLOAD_2 = 0x24;
    public static final int FLOAD_3 = 0x25;
    public static final int DLOAD_0 = 0x26;
    public static final int DLOAD_1 = 0x27;
    public static final int DLOAD_2 = 0x28;
    public static final int DLOAD_3 = 0x29;
    public static final int ALOAD_0 = 0x2a;
    public static final int ALOAD_1 = 0x2b;
    public static final int ALOAD_2 = 0x2c;
    public static final int ALOAD_3 = 0x2d;
    public static final int IALOAD = 0x2e;
    public static final int LALOAD = 0x2f;
    public static final int FALOAD = 0x30;
    public static final int DALOAD = 0x31;
    public static final int AALOAD = 0x32;
    public static final int BALOAD = 0x33;
    public static final int CALOAD = 0x34;
    public static final int SALOAD = 0x35;

    // Store Instructions Operand Codes
    public static final int ISTORE = 0x36;
    public static final int LSTORE = 0x37;
    public static final int FSTORE = 0x38;
    public static final int DSTORE = 0x39;
    public static final int ASTORE = 0x3a;
    public static final int ISTORE_0 = 0x3b;
    public static final int ISTORE_1 = 0x3c;
    public static final int ISTORE_2 = 0x3d;
    public static final int ISTORE_3 = 0x3e;
    public static final int LSTORE_0 = 0x3f;
    public static final int LSTORE_1 = 0x40;
    public static final int LSTORE_2 = 0x41;
    public static final int LSTORE_3 = 0x42;
    public static final int FSTORE_0 = 0x43;
    public static final int FSTORE_1 = 0x44;
    public static final int FSTORE_2 = 0x45;
    public static final int FSTORE_3 = 0x46;
    public static final int DSTORE_0 = 0x47;
    public static final int DSTORE_1 = 0x48;
    public static final int DSTORE_2 = 0x49;
    public static final int DSTORE_3 = 0x4a;
    public static final int ASTORE_0 = 0x4b;
    public static final int ASTORE_1 = 0x4c;
    public static final int ASTORE_2 = 0x4d;
    public static final int ASTORE_3 = 0x4e;
    public static final int IASTORE = 0x4f;
    public static final int LASTORE = 0x50;
    public static final int FASTORE = 0x51;
    public static final int DASTORE = 0x52;
    public static final int AASTORE = 0x53;
    public static final int BASTORE = 0x54;
    public static final int CASTORE = 0x55;
    public static final int SASTORE = 0x56;

    // Stack Instructions Operand Codes
    public static final int POP = 0x57;
    public static final int POP2 = 0x58;
    public static final int DUP = 0x59;
    public static final int DUP_X1 = 0x5a;
    public static final int DUP_X2 = 0x5b;
    public static final int DUP2 = 0x5c;
    public static final int DUP2_X1 = 0x5d;
    public static final int DUP2_X2 = 0x5e;
    public static final int SWAP = 0x5f;

    // Math Instructions Operand Codes
    public static final int IADD = 0x60;
    public static final int LADD = 0x61;
    public static final int FADD = 0x62;
    public static final int DADD = 0x63;
    public static final int ISUB = 0x64;
    public static final int LSUB = 0x65;
    public static final int FSUB = 0x66;
    public static final int DSUB = 0x67;
    public static final int IMUL = 0x68;
    public static final int LMUL = 0x69;
    public static final int FMUL = 0x6a;
    public static final int DMUL = 0x6b;
    public static final int IDIV = 0x6c;
    public static final int LDIV = 0x6d;
    public static final int FDIV = 0x6e;
    public static final int DDIV = 0x6f;
    public static final int IREM = 0x70;
    public static final int LREM = 0x71;
    public static final int FREM = 0x72;
    public static final int DREM = 0x73;
    public static final int INEG = 0x74;
    public static final int LNEG = 0x75;
    public static final int FNEG = 0x76;
    public static final int DNEG = 0x77;
    public static final int ISHL = 0x78;
    public static final int LSHL = 0x79;
    public static final int ISHR = 0x7a;
    public static final int LSHR = 0x7b;
    public static final int IUSHR = 0x7c;
    public static final int LUSHR = 0x7d;
    public static final int IAND = 0x7e;
    public static final int LAND = 0x7f;
    public static final int IOR = 0x80;
    public static final int LOR = 0x81;
    public static final int IXOR = 0x82;
    public static final int LXOR = 0x83;
    public static final int IINC = 0x84;

    // Conversions Instructions Operand Codes
    public static final int I2L = 0x85;
    public static final int I2F = 0x86;
    public static final int I2D = 0x87;
    public static final int L2I = 0x88;
    public static final int L2F = 0x89;
    public static final int L2D = 0x8a;
    public static final int F2I = 0x8b;
    public static final int F2L = 0x8c;
    public static final int F2D = 0x8d;
    public static final int D2I = 0x8e;
    public static final int D2L = 0x8f;
    public static final int D2F = 0x90;
    public static final int I2B = 0x91;
    public static final int I2C = 0x92;
    public static final int I2S = 0x93;

    // Comparison Instructions Operand Codes
    public static final int LCMP = 0x94;
    public static final int FCMPL = 0x95;
    public static final int FCMPG = 0x96;
    public static final int DCMPL = 0x97;
    public static final int DCMPG = 0x98;
    public static final int IFEQ = 0x99;
    public static final int IFNE = 0x9a;
    public static final int IFLT = 0x9b;
    public static final int IFGE = 0x9c;
    public static final int IFGT = 0x9d;
    public static final int IFLE = 0x9e;
    public static final int IF_ICMPEQ = 0x9f;
    public static final int IF_ICMPNE = 0xa0;
    public static final int IF_ICMPLT = 0xa1;
    public static final int IF_ICMPGE = 0xa2;
    public static final int IF_ICMPGT = 0xa3;
    public static final int IF_ICMPLE = 0xa4;
    public static final int IF_ACMPEQ = 0xa5;
    public static final int IF_ACMPNE = 0xa6;

    // Control Instructions Operand Codes
    public static final int GOTO = 0xa7;
    public static final int JSR = 0xa8;
    public static final int RET = 0xa9;
    public static final int TABLESWITCH = 0xaa;
    public static final int LOOKUPSWITCH = 0xab;
    public static final int IRETURN = 0xac;
    public static final int LRETURN = 0xad;
    public static final int FRETURN = 0xae;
    public static final int DRETURN = 0xaf;
    public static final int ARETURN = 0xb0;
    public static final int RETURN = 0xb1;

    // Reference Instructions Operand Codes
    public static final int GETSTATIC = 0xb2;
    public static final int PUTSTATIC = 0xb3;
    public static final int GETFIELD = 0xb4;
    public static final int PUTFIELD = 0xb5;
    public static final int INVOKEVIRTUAL = 0xb6;
    public static final int INVOKESPECIAL = 0xb7;
    public static final int INVOKESTATIC = 0xb8;
    public static final int INVOKEINTERFACE = 0xb9;
    public static final int INVOKEDYNAMIC = 0xba;
    public static final int NEW = 0xbb;
    public static final int NEWARRAY = 0xbc;
    public static final int ANEWARRAY = 0xbd;
    public static final int ARRAYLENGTH = 0xbe;
    public static final int ATHROW = 0xbf;
    public static final int CHECKCAST = 0xc0;
    public static final int INSTANCEOF = 0xc1;
    public static final int MONITORENTER = 0xc2;
    public static final int MONITOREXIT = 0xc3;

    // Extended Instructions Operand Codes
    public static final int WIDE = 0xc4;
    public static final int MULTIANEWARRAY = 0xc5;
    public static final int IFNULL = 0xc6;
    public static final int IFNONNULL = 0xc7;
    public static final int GOTO_W = 0xc8;
    public static final int JSR_W = 0xc9;

    // Reserved Instructions Operand Codes
    public static final int BREAKPOINT = 0xca;
    public static final int IMPDEP1 = 0xfe;
    public static final int IMPDEP2 = 0xff;
    public static final int END = 0x100; // Used to point to the last element.

    public static InstructionEntry create(ClassManager classManager, int opCode, DataInputStream dis, int pos, InstructionEntry entry) throws IOException {
        switch(opCode) {
            // Constant instructions
            case NOP:
                return new StaticInstruction(opCode, 0, "NOP", entry);
            case ACONST_NULL:
                return new StaticInstruction(opCode, 1, "ACONST_NULL", entry);
            case ICONST_M1:
                return new StaticInstruction(opCode, 1, "ICONST_M1", entry);
            case ICONST_0:
                return new StaticInstruction(opCode, 1, "ICONST_0", entry);
            case ICONST_1:
                return new StaticInstruction(opCode, 1, "ICONST_1", entry);
            case ICONST_2:
                return new StaticInstruction(opCode, 1, "ICONST_2", entry);
            case ICONST_3:
                return new StaticInstruction(opCode, 1, "ICONST_3", entry);
            case ICONST_4:
                return new StaticInstruction(opCode, 1, "ICONST_4", entry);
            case ICONST_5:
                return new StaticInstruction(opCode, 1, "ICONST_5", entry);
            case LCONST_0:
                return new StaticInstruction(opCode, 1, "LCONST_0", entry);
            case LCONST_1:
                return new StaticInstruction(opCode, 1, "LCONST_1", entry);
            case FCONST_0:
                return new StaticInstruction(opCode, 1, "FCONST_0", entry);
            case FCONST_1:
                return new StaticInstruction(opCode, 1, "FCONST_1", entry);
            case FCONST_2:
                return new StaticInstruction(opCode, 1, "FCONST_2", entry);
            case DCONST_0:
                return new StaticInstruction(opCode, 1, "DCONST_0", entry);
            case DCONST_1:
                return new StaticInstruction(opCode, 1, "DCONST_1", entry);
            case BIPUSH:
                return new TwoByteInstruction(opCode, dis.read(), 1, "BIPUSH", entry);
            case SIPUSH:
                return new ThreeByteInstruction(opCode, dis.read(), dis.read(), 1, "SIPUSH",
                        entry);
            case LDC:
                return new TwoByteInstruction(opCode, dis.read(), 1, "LDC", entry);
            case LDC_W:
                return new ThreeByteInstruction(opCode, dis.read(), dis.read(), 1, "LDC_W",
                        entry);
            case LDC2_W:
                return new ThreeByteInstruction(opCode, dis.read(), dis.read(), 1, "LDC2_W",
                        entry);
            // Load instructions
            case ILOAD:
                return new LoadOrStoreInstruction(opCode, dis.read(), 1, "ILOAD", entry);
            case LLOAD:
                return new LoadOrStoreInstruction(opCode, dis.read(), 1,"LLOAD", entry);
            case FLOAD:
                return new LoadOrStoreInstruction(opCode, dis.read(), 1, "FLOAD", entry);
            case DLOAD:
                return new LoadOrStoreInstruction(opCode, dis.read(), 1, "DLOAD", entry);
            case ALOAD:
                return new LoadOrStoreInstruction(opCode, dis.read(), 1, "ALOAD", entry);
            case ILOAD_0:
                return new LoadOrStoreInstruction(opCode, 0, 1, "ILOAD_0", entry);
            case ILOAD_1:
                return new LoadOrStoreInstruction(opCode, 1, 1, "ILOAD_1", entry);
            case ILOAD_2:
                return new LoadOrStoreInstruction(opCode, 2, 1, "ILOAD_2", entry);
            case ILOAD_3:
                return new LoadOrStoreInstruction(opCode, 3, 1, "ILOAD_3", entry);
            case LLOAD_0:
                return new LoadOrStoreInstruction(opCode, 0, 1, "LLOAD_0", entry);
            case LLOAD_1:
                return new LoadOrStoreInstruction(opCode, 1, 1, "LLOAD_1", entry);
            case LLOAD_2:
                return new LoadOrStoreInstruction(opCode, 2, 1, "LLOAD_2", entry);
            case LLOAD_3:
                return new LoadOrStoreInstruction(opCode, 3, 1, "LLOAD_3", entry);
            case FLOAD_0:
                return new LoadOrStoreInstruction(opCode, 0, 1, "FLOAD_0", entry);
            case FLOAD_1:
                return new LoadOrStoreInstruction(opCode, 1, 1, "FLOAD_1", entry);
            case FLOAD_2:
                return new LoadOrStoreInstruction(opCode, 2, 1, "FLOAD_2", entry);
            case FLOAD_3:
                return new LoadOrStoreInstruction(opCode, 3, 1, "FLOAD_3", entry);
            case DLOAD_0:
                return new LoadOrStoreInstruction(opCode, 0, 1, "DLOAD_0", entry);
            case DLOAD_1:
                return new LoadOrStoreInstruction(opCode, 1, 1, "DLOAD_1", entry);
            case DLOAD_2:
                return new LoadOrStoreInstruction(opCode, 2, 1, "DLOAD_2", entry);
            case DLOAD_3:
                return new LoadOrStoreInstruction(opCode, 3, 1, "DLOAD_3", entry);
            case ALOAD_0:
                return new LoadOrStoreInstruction(opCode, 0, 1,  "ALOAD_0", entry);
            case ALOAD_1:
                return new LoadOrStoreInstruction(opCode, 1, 1, "ALOAD_1", entry);
            case ALOAD_2:
                return new LoadOrStoreInstruction(opCode, 2, 1, "ALOAD_2", entry);
            case ALOAD_3:
                return new LoadOrStoreInstruction(opCode, 3, 1, "ALOAD_3", entry);
            case IALOAD:
                return new LoadOrStoreArrayReferenceInstruction(opCode, -1, "IALOAD", entry);
            case LALOAD:
                return new LoadOrStoreArrayReferenceInstruction(opCode, -1, "LALOAD", entry);
            case FALOAD:
                return new LoadOrStoreArrayReferenceInstruction(opCode, -1, "FALOAD", entry);
            case DALOAD:
                return new LoadOrStoreArrayReferenceInstruction(opCode, -1, "DALOAD", entry);
            case AALOAD:
                return new LoadOrStoreArrayReferenceInstruction(opCode, -1, "AALOAD", entry);
            case BALOAD:
                return new LoadOrStoreArrayReferenceInstruction(opCode, -1, "BALOAD", entry);
            case CALOAD:
                return new LoadOrStoreArrayReferenceInstruction(opCode, -1, "CALOAD", entry);
            case SALOAD:
                return new LoadOrStoreArrayReferenceInstruction(opCode, -1, "SALOAD", entry);
            // Store instructions
            case ISTORE:
                return new LoadOrStoreInstruction(opCode, dis.read(), -1, "ISTORE", entry);
            case LSTORE:
                return new LoadOrStoreInstruction(opCode, dis.read(), -1, "LSTORE", entry);
            case FSTORE:
                return new LoadOrStoreInstruction(opCode, dis.read(), -1, "FSTORE", entry);
            case DSTORE:
                return new LoadOrStoreInstruction(opCode, dis.read(), -1, "DSTORE", entry);
            case ASTORE:
                return new LoadOrStoreInstruction(opCode, dis.read(), -1, "ASTORE", entry);
            case ISTORE_0:
                return new LoadOrStoreInstruction(opCode, 0, -1, "ISTORE_0", entry);
            case ISTORE_1:
                return new LoadOrStoreInstruction(opCode, 1, -1, "ISTORE_1", entry);
            case ISTORE_2:
                return new LoadOrStoreInstruction(opCode, 2, -1, "ISTORE_2", entry);
            case ISTORE_3:
                return new LoadOrStoreInstruction(opCode, 3, -1, "ISTORE_3", entry);
            case LSTORE_0:
                return new LoadOrStoreInstruction(opCode, 0, -1, "LSTORE_0", entry);
            case LSTORE_1:
                return new LoadOrStoreInstruction(opCode, 1, -1, "LSTORE_1", entry);
            case LSTORE_2:
                return new LoadOrStoreInstruction(opCode, 2, -1, "LSTORE_2", entry);
            case LSTORE_3:
                return new LoadOrStoreInstruction(opCode, 3, -1, "LSTORE_3", entry);
            case FSTORE_0:
                return new LoadOrStoreInstruction(opCode, 0, -1, "FSTORE_0", entry);
            case FSTORE_1:
                return new LoadOrStoreInstruction(opCode, 1, -1, "FSTORE_1", entry);
            case FSTORE_2:
                return new LoadOrStoreInstruction(opCode, 2, -1, "FSTORE_2", entry);
            case FSTORE_3:
                return new LoadOrStoreInstruction(opCode, 3, -1, "FSTORE_3", entry);
            case DSTORE_0:
                return new LoadOrStoreInstruction(opCode, 0, -1, "DSTORE_0", entry);
            case DSTORE_1:
                return new LoadOrStoreInstruction(opCode, 1, -1, "DSTORE_1", entry);
            case DSTORE_2:
                return new LoadOrStoreInstruction(opCode, 2, -1, "DSTORE_2", entry);
            case DSTORE_3:
                return new LoadOrStoreInstruction(opCode, 3, -1, "DSTORE_3", entry);
            case ASTORE_0:
                return new LoadOrStoreInstruction(opCode, 0, -1, "ASTORE_0", entry);
            case ASTORE_1:
                return new LoadOrStoreInstruction(opCode, 1, -1, "ASTORE_1", entry);
            case ASTORE_2:
                return new LoadOrStoreInstruction(opCode, 2, -1, "ASTORE_2", entry);
            case ASTORE_3:
                return new LoadOrStoreInstruction(opCode, 3, -1, "ASTORE_3", entry);
            case IASTORE:
                return new LoadOrStoreArrayReferenceInstruction(opCode, -3, "IASTORE", entry);
            case LASTORE:
                return new LoadOrStoreArrayReferenceInstruction(opCode, -3, "LASTORE", entry);
            case FASTORE:
                return new LoadOrStoreArrayReferenceInstruction(opCode, -3, "FASTORE", entry);
            case DASTORE:
                return new LoadOrStoreArrayReferenceInstruction(opCode, -3, "DASTORE", entry);
            case AASTORE:
                return new LoadOrStoreArrayReferenceInstruction(opCode, -3, "AASTORE", entry);
            case BASTORE:
                return new LoadOrStoreArrayReferenceInstruction(opCode, -3, "BASTORE", entry);
            case CASTORE:
                return new LoadOrStoreArrayReferenceInstruction(opCode, -3, "CASTORE", entry);
            case SASTORE:
                return new LoadOrStoreArrayReferenceInstruction(opCode, -3, "SASTORE", entry);
            // Stack instructions
            case POP:
                return new StaticInstruction(opCode, -1, "POP", entry);
            case POP2:
                return new Pop2Instruction(pos, entry);
            case DUP:
                return new StaticInstruction(opCode, 1, "DUP", entry);
            case DUP_X1:
                return new StaticInstruction(opCode, 1, "DUP_X1", entry);
            case DUP_X2:
                return new StaticInstruction(opCode, 1, "DUP_X2", entry);
            case DUP2:
                return new Dup2Instruction(pos, entry);
            case DUP2_X1:
                return new Dup2x1Instruction(pos, entry);
            case DUP2_X2:
                return new Dup2x2Instruction(pos, entry);
            case SWAP:
                return new StaticInstruction(opCode, 0, "SWAP", entry);
            // Math instructions
            case IADD:
                return new StaticInstruction(opCode, -1, "IADD", entry);
            case LADD:
                return new StaticInstruction(opCode, -1, "LADD", entry);
            case FADD:
                return new StaticInstruction(opCode, -1, "FADD", entry);
            case DADD:
                return new StaticInstruction(opCode, -1, "DADD", entry);
            case ISUB:
                return new StaticInstruction(opCode, -1, "ISUB", entry);
            case LSUB:
                return new StaticInstruction(opCode, -1, "LSUB", entry);
            case FSUB:
                return new StaticInstruction(opCode, -1, "FSUB", entry);
            case DSUB:
                return new StaticInstruction(opCode, -1, "DSUB", entry);
            case IMUL:
                return new StaticInstruction(opCode, -1, "IMUL", entry);
            case LMUL:
                return new StaticInstruction(opCode, -1, "LMUL", entry);
            case FMUL:
                return new StaticInstruction(opCode, -1, "FMUL", entry);
            case DMUL:
                return new StaticInstruction(opCode, -1, "DMUL", entry);
            case IDIV:
                return new StaticInstruction(opCode, -1, "IDIV", entry);
            case LDIV:
                return new StaticInstruction(opCode, -1, "LDIV", entry);
            case FDIV:
                return new StaticInstruction(opCode, -1, "FDIV", entry);
            case DDIV:
                return new StaticInstruction(opCode, -1, "DDIV", entry);
            case IREM:
                return new StaticInstruction(opCode, -1, "IREM", entry);
            case LREM:
                return new StaticInstruction(opCode, -1, "LREM", entry);
            case FREM:
                return new StaticInstruction(opCode, -1, "FREM", entry);
            case DREM:
                return new StaticInstruction(opCode, -1, "DREM", entry);
            case INEG:
                return new StaticInstruction(opCode, 0, "INEG", entry);
            case LNEG:
                return new StaticInstruction(opCode, 0, "LNEG", entry);
            case FNEG:
                return new StaticInstruction(opCode, 0, "FNEG", entry);
            case DNEG:
                return new StaticInstruction(opCode, 0, "DNEG", entry);
            case ISHL:
                return new StaticInstruction(opCode, -1, "ISHL", entry);
            case LSHL:
                return new StaticInstruction(opCode, -1, "LSHL", entry);
            case ISHR:
                return new StaticInstruction(opCode, -1, "ISHR", entry);
            case LSHR:
                return new StaticInstruction(opCode, -1, "LSHR", entry);
            case IUSHR:
                return new StaticInstruction(opCode, -1, "IUSHR", entry);
            case LUSHR:
                return new StaticInstruction(opCode, -1, "LUSHR", entry);
            case IAND:
                return new StaticInstruction(opCode, -1, "IAND", entry);
            case LAND:
                return new StaticInstruction(opCode, -1, "LAND", entry);
            case IOR:
                return new StaticInstruction(opCode, -1, "IOR", entry);
            case LOR:
                return new StaticInstruction(opCode, -1, "LOR", entry);
            case IXOR:
                return new StaticInstruction(opCode, -1, "IXOR", entry);
            case LXOR:
                return new StaticInstruction(opCode, -1, "LXOR", entry);
            case IINC:
                return new IINCInstruction(dis.read(), dis.read(), entry);
            // Conversion instructions
            case I2L:
                return new StaticInstruction(opCode, 0, "I2L", entry);
            case I2F:
                return new StaticInstruction(opCode, 0, "I2F", entry);
            case I2D:
                return new StaticInstruction(opCode, 0, "I2D", entry);
            case L2I:
                return new StaticInstruction(opCode, 0, "L2I", entry);
            case L2F:
                return new StaticInstruction(opCode, 0, "L2F", entry);
            case L2D:
                return new StaticInstruction(opCode, 0, "L2D", entry);
            case F2I:
                return new StaticInstruction(opCode, 0, "F2I", entry);
            case F2L:
                return new StaticInstruction(opCode, 0, "F2L", entry);
            case F2D:
                return new StaticInstruction(opCode, 0, "F2D", entry);
            case D2I:
                return new StaticInstruction(opCode, 0, "D2I", entry);
            case D2L:
                return new StaticInstruction(opCode, 0, "D2L", entry);
            case D2F:
                return new StaticInstruction(opCode, 0, "D2F", entry);
            case I2B:
                return new StaticInstruction(opCode, 0, "I2B", entry);
            case I2C:
                return new StaticInstruction(opCode, 0, "I2C", entry);
            case I2S:
                return new StaticInstruction(opCode, 0, "I2S", entry);
            // Comparison instructions
            case LCMP:
                return new StaticInstruction(opCode, -1, "LCMP", entry);
            case FCMPL:
                return new StaticInstruction(opCode, -1, "FCMPL", entry);
            case FCMPG:
                return new StaticInstruction(opCode, -1, "FCMPG", entry);
            case DCMPL:
                return new StaticInstruction(opCode, -1, "DCMPL", entry);
            case DCMPG:
                return new StaticInstruction(opCode, -1, "DCMPG", entry);
            case IFEQ:
                return new IfInstruction(opCode, -1, "IFEQ", dis.readUnsignedShort(), entry);
            case IFNE:
                return new IfInstruction(opCode, -1, "IFNE", dis.readUnsignedShort(), entry);
            case IFLT:
                return new IfInstruction(opCode, -1, "IFLT", dis.readUnsignedShort(), entry);
            case IFGE:
                return new IfInstruction(opCode, -1, "IFGE", dis.readUnsignedShort(), entry);
            case IFGT:
                return new IfInstruction(opCode, -1, "IFGT", dis.readUnsignedShort(), entry);
            case IFLE:
                return new IfInstruction(opCode, -1, "IFLE", dis.readUnsignedShort(), entry);
            case IF_ICMPEQ:
                return new IfInstruction(opCode, -2, "IF_ICMPEQ", dis.readUnsignedShort(),
                        entry);
            case IF_ICMPNE:
                return new IfInstruction(opCode, -2, "IF_ICMPNE", dis.readUnsignedShort(),
                        entry);
            case IF_ICMPLT:
                return new IfInstruction(opCode, -2, "IF_ICMPLT", dis.readUnsignedShort(),
                        entry);
            case IF_ICMPGE:
                return new IfInstruction(opCode, -2, "IF_ICMPGE", dis.readUnsignedShort(),
                        entry);
            case IF_ICMPGT:
                return new IfInstruction(opCode, -2, "IF_ICMPTGT", dis.readUnsignedShort(),
                        entry);
            case IF_ICMPLE:
                return new IfInstruction(opCode, -2, "IF_ICMPLE", dis.readUnsignedShort(),
                        entry);
            case IF_ACMPEQ:
                return new IfInstruction(opCode, -2, "IF_ACMPEQ", dis.readUnsignedShort(),
                        entry);
            case IF_ACMPNE:
                return new IfInstruction(opCode, -2, "IF_ACMPNE", dis.readUnsignedShort(),
                        entry);
            // Control instructions
            case GOTO:
                return new GotoInstruction(opCode, 0, "GOTO", dis.readShort(), entry);
            case JSR:
                return new JsrInstruction(opCode, "JSR", dis.readShort(), entry);
            case RET:
                return new RetInstruction(opCode, dis.readUnsignedByte(), entry);
            case TABLESWITCH:
                return TableSwitchInstruction.create(dis, pos, entry);
            case LOOKUPSWITCH:
                return LookupSwitchInstruction.create(dis, pos, entry);
            case IRETURN:
                return new ReturnInstruction(opCode, -1, "IRETURN", entry);
            case LRETURN:
                return new ReturnInstruction(opCode, -1, "LRETURN", entry);
            case FRETURN:
                return new ReturnInstruction(opCode, -1, "FRETURN", entry);
            case DRETURN:
                return new ReturnInstruction(opCode, -1, "DRETURN", entry);
            case ARETURN:
                return new ReturnInstruction(opCode, -1, "ARETURN", entry);
            case RETURN:
                return new ReturnInstruction(opCode, 0, "RETURN", entry);
            // Reference instructions
            case GETSTATIC:
                return new FieldInstruction(opCode, 1, "GETSTATIC", dis.readUnsignedShort(),
                        entry);
            case PUTSTATIC:
                return new FieldInstruction(opCode, -1, "PUTSTATIC", dis.readUnsignedShort(),
                        entry);
            case GETFIELD:
                return new FieldInstruction(opCode, 0, "GETFIELD", dis.readUnsignedShort(),
                        entry);
            case PUTFIELD:
                return new FieldInstruction(opCode, -2, "PUTFIELD", dis.readUnsignedShort(),
                        entry);
            case INVOKEVIRTUAL:
                return new InvokeVirtualInstruction(dis.readUnsignedShort(), entry);
            case INVOKESPECIAL:
                return new InvokeSpecialInstruction(classManager, dis.readUnsignedShort(), entry);
            case INVOKESTATIC:
                return new InvokeStaticInstruction(classManager, dis.readUnsignedShort(), entry);
            case INVOKEINTERFACE:
                return new InvokeInterfaceInstruction(dis.readUnsignedShort(), dis.readUnsignedByte(), dis.read(),
                        entry);
            case INVOKEDYNAMIC:
                return new InvokeDynamicInstruction(dis.readUnsignedShort(), dis.readUnsignedShort(), entry);
            case NEW:
                return new NewInstruction(dis.readUnsignedShort(), entry);
            case NEWARRAY:
                return new NewArrayInstruction(dis.readUnsignedByte(), entry);
            case ANEWARRAY:
                return new ANewArrayInstruction(dis.readUnsignedShort(), entry);
            case ARRAYLENGTH:
                return new StaticInstruction(opCode, 0, "ARRAYLENGTH", entry);
            case ATHROW:
                return new StaticInstruction(opCode, 0, "ATHROW", entry);
            case CHECKCAST:
                return new CheckCastInstruction(dis.readUnsignedShort(), entry);
            case INSTANCEOF:
                return new InstanceOfInstruction(dis.readUnsignedShort(), entry);
            case MONITORENTER:
                return new StaticInstruction(opCode, -1, "MONITORENTER", entry);
            case MONITOREXIT:
                return new StaticInstruction(opCode, -1, "MONITOREXIT", entry);
            // Extended instructions
            case WIDE:
                return WideInstructionFactory.create(dis, entry);
            case MULTIANEWARRAY:
                return new MultiANewArrayInstruction(dis.readUnsignedShort(), dis.readUnsignedByte(), entry);
            case IFNULL:
                return new IfInstruction(opCode, -1, "IFNULL", dis.readShort(), entry);
            case IFNONNULL:
                return new IfInstruction(opCode, -1, "IFNONNULL", dis.readShort(), entry);
            case GOTO_W:
                return new GotoWInstruction(opCode, 0, "GOTO_W", dis.readInt(), entry);
            case JSR_W:
                return new JsrWInstruction(opCode, "JSR_W", dis.readInt(), entry);
            // Reserved instructions
            case BREAKPOINT:
                return new StaticInstruction(opCode, 0, "BREAKPOINT", entry);
            case IMPDEP1:
                return new StaticInstruction(opCode, 0, "IMPDEP1", entry);
            case IMPDEP2:
                return new StaticInstruction(opCode, 0, "IMPDEP2", entry);
            default:
                throw new ClassFileException(String.format("Unknown operand code: %d", opCode));
        }
    }
}
