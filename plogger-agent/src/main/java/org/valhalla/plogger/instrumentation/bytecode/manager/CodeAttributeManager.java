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

import org.valhalla.plogger.instrumentation.Logger;
import org.valhalla.plogger.instrumentation.bytecode.attributes.ClassAttribute;
import org.valhalla.plogger.instrumentation.bytecode.attributes.CodeAttribute;
import org.valhalla.plogger.instrumentation.bytecode.attributes.CodeExceptionTable;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileException;
import org.valhalla.plogger.instrumentation.bytecode.constantpool.ConstantMethodRef;
import org.valhalla.plogger.instrumentation.bytecode.constantpool.ConstantPoolEntry;
import org.valhalla.plogger.instrumentation.bytecode.constantpool.ConstantPoolEntryException;

import java.io.ByteArrayOutputStream;
import java.io.DataOutput;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.List;

import static org.valhalla.plogger.instrumentation.bytecode.manager.InstructionEntryFactory.*;

public class CodeAttributeManager implements AttributeManager {

    private final int maxLocals;
    private int maxStack;
    private final AttributeManager[] attributes;
    private final ExceptionTableManager exceptionTableManager;
    private byte[] code;
    protected int nameIndex;
    public static final String LOGGER_CLASS_NAME = Logger.class.getName().replace('.', '/');

    public CodeAttributeManager(int nameIndex, CodeAttribute codeAttribute) {
        this.nameIndex = nameIndex;
        this.maxStack = codeAttribute.getMaxStack();
        this.maxLocals = codeAttribute.getMaxLocals();
        this.code = codeAttribute.getCode();
        Collection<CodeExceptionTable> items = codeAttribute.getExceptionTables();
        this.exceptionTableManager = new ExceptionTableManager(items);
        List<ClassAttribute> attributes = codeAttribute.getCodeAttributes();
        this.attributes = new AttributeManager[attributes.size()];
        for(int idx = 0 ; idx < this.attributes.length ; idx++) {
            this.attributes[idx] = AttributeManagerFactory.create(attributes.get(idx));
        }
    }

    public CodeAttributeManager(int nameIndex, int maxStack, int maxLocals, byte[] code,
                                ExceptionTableManager exceptionTableManager, AttributeManager[] attributes) {
        this.nameIndex = nameIndex;
        this.maxLocals = maxLocals;
        this.maxStack = maxStack;
        this.code = code;
        this.exceptionTableManager = exceptionTableManager;
        this.attributes = attributes;
    }

    // This will return the current max locals for this method
    public int getMaxLocals() {
        return maxLocals;
    }

    // This will return the current max stack for this method
    public int getMaxStack() {
        return maxStack;
    }

    private static final int ACC_STATIC = 0x0008;

    private static final int JDK_5_VERSION = 49;
    private static final int JDK_6_VERSION = 50;

    public boolean instrument(ClassManager classManager, MethodManager methodManager) {
        // ok we are finally ready to instrument the method.
        // let us determine if this is a static or instance method.
        int accessFlags = methodManager.getAccessFlags();
        int majorVersion = classManager.getMajorVersion();
        if ((accessFlags & ACC_STATIC) != 0) {
            // let us determine which class version this method is part of.
            // classes generated for jdk 1.4 or earlier will require different
            // instrumentation updates than class versions for jdk 1.5 or newer.
            if (majorVersion < JDK_5_VERSION) {
                // This class file can't use the concise instruction to get
                // a reference to the class class instance.  We need to use
                // the Class.forName(<className>) method call instead.
                return instrumentJdk4VersionStaticMethod(classManager, methodManager);
            } else {
                // This class file can use the concise instruction to get
                // a reference to the class class instance.  This will make
                // the code more concise.

                // This class file may or may not contain a StackMapTable so
                // we need to worry about updating this attribute.
                return instrumentJdk5VersionStaticMethod(classManager, methodManager);
            }
        } else {
            // let us then instrument this instance method.
            // we are instrumenting a method that may or may not contain a stack map table
            return instrumentInstanceMethod(classManager, methodManager);
        }
    }

    private boolean instrumentInstanceMethod(ClassManager classManager, MethodManager methodManager) {
        try {
            String objectType = "Ljava/lang/Object;";
            // Create the prolog instructions that are required in this case.

            // Add aload_0 instruction
            AbstractInstruction instruction = new LoadOrStoreInstruction(InstructionEntryFactory.ALOAD_0, 0,
                    1, "ALOAD_0", null);

            // Add remaining logger instructions
            addRemainingLoggerWriteInstructions(classManager, methodManager, classManager.getConstantPoolManager(),
                    instruction, objectType);
            return true;
        } catch (ConstantPoolEntryException e) {
            // TODO: Add debug option
            e.printStackTrace(System.out);
            throw new ClassFileException(e);
        }
    }

    /**
     * This method will instrument code for static methods that were generated with jdk 1.4 or older.
     * This is required because with jdk 1.4 or older we can't use the LDC instructions with a
     * ConstantClass entry.  This will cause verifications issues.  The call needs to be replaced
     * with a Class.forName("class name") call instead. Note that this is not how this was generated
     * for those versions but we are required to use this call since the generated call is not
     * necessarily go to be available.
     *
     * @param classManager
     * @param methodManager
     * @return
     */
    private boolean instrumentJdk4VersionStaticMethod(ClassManager classManager, MethodManager methodManager) {
        try {
            String objectType = "Ljava/lang/Class;";
            // Create the prolog instructions that are required in this case.
            ConstantPoolManager constantPool = classManager.getConstantPoolManager();
            ConstantPoolEntry entry = constantPool.getStringEntry("java.lang.Class");
            int index = constantPool.getEntryIndex(entry);
            // Add LDC or LDC_W instruction for the ConstantString (class name)
            AbstractInstruction instruction = addLdcInstruction(index, null);

            // Add invokestatic instruction
            entry = constantPool.getMethodRefEntry("java/lang/Class", "forName",
                    "(Ljava/lang/String;)Ljava/lang/Class;");
            index = constantPool.getEntryIndex(entry);
            // Don't reassign instruction since we are passing the first instruction to the
            // addRemainingLoggerWriteInstructions method.
            /* instruction = */ new InvokeStaticInstruction( classManager, 0, index, instruction);

            // Add remaining logger instructions
            addRemainingLoggerWriteInstructions(classManager, methodManager, constantPool, instruction, objectType);
            return true;
        } catch (ConstantPoolEntryException e) {
            // TODO: Add debug option
            e.printStackTrace(System.out);
            throw new ClassFileException(e);
        }
    }

    /*
    This will add the following instructions
        LDC or LDC_W for a ConstantClass
        LDC or LDC_W for a ConstantString
        ICONST or ICONST_<n> for the size of the Object array
        ANEWARRAY
        DUP
        ICONST_0 for the array index
        ALOAD_0  for the first parameter
        AASTORE store the first parameter in the object array
        INVOKESTATIC for the Logger.write(Class,MethodName[,Object[]])
     */

    /**
     *
     * @param classManager
     * @param methodManager
     * @return
     */
    private boolean instrumentJdk5VersionStaticMethod(ClassManager classManager, MethodManager methodManager) {
        try {
            String objectType = "Ljava/lang/Class;";
            // Create the prolog instructions that are required in this case.
            ConstantPoolManager constantPool = classManager.getConstantPoolManager();
            ConstantPoolEntry entry = constantPool.getClassEntry(classManager.getClassName());
            int index = constantPool.getEntryIndex(entry);
            // Add LDC or LDC_W instruction for the ConstantClass (class name)
            AbstractInstruction instruction = addLdcInstruction(index, null);
            // Add remaining logger instructions
            addRemainingLoggerWriteInstructions(classManager, methodManager, constantPool, instruction, objectType);
            return true;
        } catch (ConstantPoolEntryException e) {
            // TODO: Add debug option
            e.printStackTrace(System.out);
            throw new ClassFileException(e);
        }
    }

    /**
     * This method will combine the added Logger.write instructions with the current method byte
     * code instructions.  It will manage the update of the relevant structures that will be
     * impacted by the addition of the new prolog instruction.  This includes the update of the
     * LocalVariableTable, LocalVariableTypeTable, StackMapTable and ExceptionTable.
     *
     * @param classManager
     * @param methodManager
     * @param firstInstruction  The first instruction of the added Logger.write instructions
     */
    private void syncCombineUpdateInstructions(ClassManager classManager, MethodManager methodManager,
                                               AbstractInstruction firstInstruction) {
        // Generate the instructions for the current method
        InstructionManager instructionManager = new InstructionManager(classManager, code);

        // Determine the prolog stack size.
        int stack = 0;
        AbstractInstruction instr = firstInstruction;
        while(instr != null) {
            stack += instr.stack();
            instr = instr.getNext();
            if (stack > this.maxStack) {
                // need to update the stack size since we require more than is going to be available
                this.maxStack = stack;
            }
        }

        // NOTE: no need to update the max locals since we don't add any locals to the method

        // Get a copy of the LocalVariableTable, StackMapTable, LocalVariableTypeTable
        LocalVariableTableManager localVariableTableManager = getLocalVariableTableManager();
        LocalVariableTypeTableManager localVariableTypeTableManager = getLocalVariableTypeTableManager();
        StackMapTableManager stackMapTableManager = getStackMapTableManager();

        // Get the first current instruction
        AbstractInstruction instruction = (AbstractInstruction) instructionManager.getFirstInstruction();
        // Call the sync method to allow the different structures to sync with each other.
        for(int pos = 0 ; instruction != null ; instruction = instruction.getNext()) {
            instruction.sync(); // synchronize the current instruction
            exceptionTableManager.sync(instruction, pos);
            if (localVariableTableManager != null) {
                localVariableTableManager.sync(instruction, pos);
            }
            if (localVariableTypeTableManager != null) {
                localVariableTypeTableManager.sync(instruction, pos);
            }
            if (stackMapTableManager != null) {
                stackMapTableManager.sync(instruction, pos);
            }
            pos += instruction.size(); // increment the position for the next instruction
        }

        // Combined the instructions
        instructionManager.instrument(firstInstruction, "<init>".equals(methodManager.getName()));

        instruction = instructionManager.getFirstInstruction();

        // Call the update method to allow the different structures to apply changes to their
        // structures.
        for(int pos = 0 ; instruction != null ; instruction = instruction.getNext()) {
            instruction.update(pos); // send each instruction its new position
            pos += instruction.size(); // increment the position for the next instruction
        }

        // Generate the new byte code array that includes the injected byte code.
        code = instructionManager.getCode();
    }

    public StackMapTableManager getStackMapTableManager() {
        return getAttributeManager(StackMapTableManager.class);
    }

    public LocalVariableTableManager getLocalVariableTableManager() {
        return getAttributeManager(LocalVariableTableManager.class);
    }

    public LocalVariableTypeTableManager getLocalVariableTypeTableManager() {
        return getAttributeManager(LocalVariableTypeTableManager.class);
    }

    private <E extends AttributeManager> E getAttributeManager(Class<E> classType) {
        for(AttributeManager attributeManager : attributes) {
            if (attributeManager != null && classType.isInstance(attributeManager)) {
                return classType.cast(attributeManager);
            }
        }
        return null;
    }

    private AbstractInstruction addLdcInstruction(int index, AbstractInstruction instruction) {
        if (index > 255) {
            return new ThreeByteInstruction(InstructionEntryFactory.LDC_W, (index / 256) >> 8,
                    index % 256, 1, "LDC_W", instruction);
        } else {
            return new TwoByteInstruction(InstructionEntryFactory.LDC, index, 1, "LDC",
                    instruction);
        }
    }

    private void addRemainingLoggerWriteInstructions(ClassManager classManager, MethodManager methodManager,
                                                     ConstantPoolManager constantPool, AbstractInstruction instruction,
                                                     String objectType) throws ConstantPoolEntryException {

        // Keep a reference to the first instruction, needed later to combine the prolog with the current
        // instructions of the method.
        AbstractInstruction firstInstruction = instruction;
        String methodName = methodManager.getName();
        if ("<init>".equals(methodName)) {
            // constructor method
            String className = classManager.getClassName();
            methodName = className.substring(className.lastIndexOf('/') + 1);
        } else if ("<clinit>".equals(methodName)) {
            // class static method
            methodName = "static";
        }
        ConstantPoolEntry entry = constantPool.getStringEntry(methodName);
        int index = constantPool.getEntryIndex(entry);
        // Add LDC or LDC_W instruction for the ConstantString (method name)
        instruction = addLdcInstruction(index, instruction);

        // Determine how many parameters are passed to the method.
        MethodSignature signature = new MethodSignature(methodManager.getSignature());
        int args = signature.size();
//        System.out.println(String.format("Creating a new array of size %d for method %s with signature %s",
//                args, methodManager.getName(), methodManager.getSignature()));
        if(args > 0) {
            instruction = addConstantIntegerInstruction(instruction, args);
            entry = constantPool.getClassEntry("java/lang/Object");
            index = constantPool.getEntryIndex(entry);
            // Add anewarray instruction of Object types
            instruction = new ANewArrayInstruction(index, instruction);
            // Add parameter values to the created array
            Slot slot = new Slot((methodManager.getAccessFlags() & ACC_STATIC) != 0 ? 0 : 1);
            for (int arg  = 0 ; arg < args ; arg++) {
                // Add dup instruction for the object array
                instruction = new StaticInstruction(InstructionEntryFactory.DUP, 1, "DUP",
                        instruction);
                // Add array index
                instruction = addConstantIntegerInstruction(instruction, arg);
                // Add parameter instruction
                instruction = signature.createInstruction(classManager, methodManager, arg, slot, instruction);
                // Add aastore instruction
                instruction = new LoadOrStoreArrayReferenceInstruction(InstructionEntryFactory.AASTORE,
                        -3, "AASTORE", instruction);
            }
            // Add invokestatic instruction for Logger.write([Class|Object], methodName, Object[])
            entry = constantPool.getMethodRefEntry(LOGGER_CLASS_NAME, "write",
                    String.format("(%sLjava/lang/String;[Ljava/lang/Object;)V", objectType));
            index = constantPool.getEntryIndex(entry);
            instruction = new InvokeStaticInstruction( classManager, -3, index, instruction);
        } else {
            // Add the call to Logger.write(Class,methodName)
            entry = constantPool.getMethodRefEntry(LOGGER_CLASS_NAME, "write",
                    String.format("(%sLjava/lang/String;)V", objectType));
            index = constantPool.getEntryIndex(entry);
            // Add invokestatic instruction for Logger.write([Class|Object], methodName);
            instruction = new InvokeStaticInstruction( classManager, -2, index, instruction);
        }
        syncCombineUpdateInstructions(classManager, methodManager, firstInstruction);
    }

    private AbstractInstruction addConstantIntegerInstruction(AbstractInstruction instruction, int value) {
        if (value > 5) {
            // Add bipush <i> instruction
            instruction = new TwoByteInstruction(InstructionEntryFactory.BIPUSH, value, 1,
                    "BIPUSH", instruction);
        } else {
            // Add a iconst_<n> instruction
            instruction = new StaticInstruction(InstructionEntryFactory.ICONST_0 + value, 1,
                    String.format("ICONST_%d", value), instruction);
        }
        return instruction;
    }

    public byte[] getCode() {
        return this.code; // TODO: this should not be accessible since it can potentially cause issues but at
                          //  the moment this is used only for testing purposes.
    }

    @Override
    public String toString() {
        return "CodeAttributeManager{" +
                "maxLocals=" + maxLocals +
                ", maxStack=" + maxStack +
                ", attributes=" + Arrays.toString(attributes) +
                ", exceptionTableManager=" + exceptionTableManager +
                ", code=" + Arrays.toString(code) +
                ", nameIndex=" + nameIndex +
                '}';
    }

    private static class MethodSignature {

        private final List<ParameterInstruction> parameters;

        public MethodSignature(String signature) {
            int start = signature.indexOf('(') + 1;
            int end = signature.indexOf(')');
            parameters = new ArrayList<ParameterInstruction>();
            while( start < end ) {
                switch(signature.charAt(start++)) {
                    case 'J': // long
                        parameters.add(ParameterInstruction.LongParameter);
                        break;
                    case 'I': // int
                        parameters.add(ParameterInstruction.IntegerParameter);
                        break;
                    case 'F': // float
                        parameters.add(ParameterInstruction.FloatParameter);
                        break;
                    case 'D': // double
                        parameters.add(ParameterInstruction.DoubleParameter);
                        break;
                    case 'V': // void
                        parameters.add(ParameterInstruction.VoidParameter);
                        break;
                    case 'S': // short
                        parameters.add(ParameterInstruction.ShortParameter);
                        break;
                    case 'C': // char
                        parameters.add(ParameterInstruction.CharParameter);
                        break;
                    case 'B': // byte
                        parameters.add(ParameterInstruction.ByteParameter);
                        break;
                    case 'Z': // boolean
                        parameters.add(ParameterInstruction.BooleanParameter);
                        break;
                    case '[': // array type
                        int cnt = start;
                        while (signature.charAt(cnt) == '[') cnt++;
                        String arrayClassName = null;
                        switch(signature.charAt(cnt)) {
                            case 'Z': case 'B': case 'S': case 'I': case 'J': case 'F': case 'D':
                                start = cnt + 1;
                                break;
                            case 'L':
                                arrayClassName = signature.substring(cnt, signature.indexOf(';', cnt));
                                start = cnt + arrayClassName.length() + 1;
                                break;
                        }
                        parameters.add(new ClassParameter(arrayClassName));
                        break;
                    case 'L':
                        String className = signature.substring(start, signature.indexOf(';', start));
                        start += className.length() + 1;
                        parameters.add(new ClassParameter(className));
                        break;
                }
            }
        }

        public int size() {
            return parameters.size();
        }

        public AbstractInstruction createInstruction(ClassManager classManager, MethodManager methodManager, int arg, Slot slot, AbstractInstruction instruction) {
            return parameters.get(arg).createInstruction(classManager, methodManager, slot, instruction);
        }

        private static interface ParameterInstruction {
            ParameterInstruction LongParameter = new AbstractParameterInstruction(2) {
                @Override
                public AbstractInstruction createInstruction(ClassManager classManager, MethodManager methodManager, Slot slot, AbstractInstruction instruction) {
                    return addPrimitiveInstruction(classManager, slot,"java/lang/Long", "(J)Ljava/lang/Long;",  LLOAD, InstructionEntryFactory.LLOAD_0,
                            "LLOAD", instruction);
                }
            };
            ParameterInstruction IntegerParameter = new AbstractParameterInstruction(2) {
                @Override
                public AbstractInstruction createInstruction(ClassManager classManager, MethodManager methodManager, Slot slot, AbstractInstruction instruction) {
                    return addPrimitiveInstruction(classManager, slot, "java/lang/Integer", "(I)Ljava/lang/Integer;",  InstructionEntryFactory.ILOAD, InstructionEntryFactory.ILOAD_0,
                            "ILOAD", instruction);
                }
            };
            ParameterInstruction FloatParameter = new AbstractParameterInstruction(2) {
                @Override
                public AbstractInstruction createInstruction(ClassManager classManager, MethodManager methodManager, Slot slot, AbstractInstruction instruction) {
                    return addPrimitiveInstruction(classManager, slot, "java/lang/Float", "(F)Ljava/lang/Float;", InstructionEntryFactory.FLOAD, InstructionEntryFactory.FLOAD_0,
                            "FLOAD", instruction);
                }
            };
            ParameterInstruction DoubleParameter = new AbstractParameterInstruction(2) {
                @Override
                public AbstractInstruction createInstruction(ClassManager classManager, MethodManager methodManager, Slot slot, AbstractInstruction instruction) {
                    return addPrimitiveInstruction(classManager, slot, "java/lang/Double", "(D)Ljava/lang/Double;", InstructionEntryFactory.DLOAD, InstructionEntryFactory.DLOAD_0,
                            "DLOAD", instruction);
                }
            };
            ParameterInstruction ShortParameter = new AbstractParameterInstruction(1) {
                @Override
                public AbstractInstruction createInstruction(ClassManager classManager, MethodManager methodManager, Slot slot, AbstractInstruction instruction) {
                    return addPrimitiveInstruction(classManager, slot, "java/lang/Short", "(S)Ljava/lang/Short;", InstructionEntryFactory.ILOAD, InstructionEntryFactory.ILOAD_0,
                            "ILOAD", instruction);
                }
            };
            ParameterInstruction ByteParameter = new AbstractParameterInstruction(1) {
                @Override
                public AbstractInstruction createInstruction(ClassManager classManager, MethodManager methodManager, Slot slot, AbstractInstruction instruction) {
                    return addPrimitiveInstruction(classManager, slot, "java/lang/Byte", "(B)Ljava/lang/Byte;", InstructionEntryFactory.ILOAD, InstructionEntryFactory.ILOAD_0,
                            "ILOAD", instruction);
                }
            };
            ParameterInstruction CharParameter = new AbstractParameterInstruction(1) {
                @Override
                public AbstractInstruction createInstruction(ClassManager classManager, MethodManager methodManager, Slot slot, AbstractInstruction instruction) {
                    return addPrimitiveInstruction(classManager, slot, "java/lang/Character", "(C)Ljava/lang/Character;", InstructionEntryFactory.ILOAD, InstructionEntryFactory.ILOAD_0,
                            "ILOAD", instruction);
                }
            };
            ParameterInstruction BooleanParameter = new AbstractParameterInstruction(1) {
                @Override
                public AbstractInstruction createInstruction(ClassManager classManager, MethodManager methodManager,
                                                             Slot slot, AbstractInstruction instruction) {
                    return addPrimitiveInstruction(classManager, slot, "java/lang/Boolean",
                            "(Z)Ljava/lang/Boolean;", InstructionEntryFactory.ILOAD,
                            InstructionEntryFactory.ILOAD_0, "ILOAD", instruction);
                }
            };
            ParameterInstruction VoidParameter = new AbstractParameterInstruction(0) {
                @Override
                public AbstractInstruction createInstruction(ClassManager classManager, MethodManager methodManager, Slot slot, AbstractInstruction instruction) {
                    return instruction;
                }
            };

            int size();

            AbstractInstruction createInstruction(ClassManager classManager, MethodManager methodManager, Slot slot,
                                                  AbstractInstruction instruction);

            abstract class AbstractParameterInstruction implements ParameterInstruction {
                private final int size;

                AbstractParameterInstruction(int size) {
                    this.size = size;
                }

                @Override
                public int size() {
                    return size;
                }

                protected AbstractInstruction addPrimitiveInstruction(ClassManager classManager, Slot slot,
                                                                      String className, String signature,
                                                                      int defaultOpCode, int startOpCode, String prefix,
                                                                      AbstractInstruction instruction) {
                    int opCode;
                    String name;
                    if (slot.get() > 3) {
                        opCode = defaultOpCode;
                        name = prefix;
                    } else {
                        opCode = startOpCode + slot.get();
                        name = String.format("%s_%d", prefix, slot.get());
                    }
                    int operandStackChange = (defaultOpCode == LLOAD || defaultOpCode == LSTORE ||
                            defaultOpCode == DLOAD || defaultOpCode == DSTORE) ? 2 : 1;
                    instruction = new LoadOrStoreInstruction(opCode, slot.get(), operandStackChange, name, instruction);
                    slot.add(size);
                    // add invokestatic instruction
                    try {
                        ConstantPoolManager constantPoolManager = classManager.getConstantPoolManager();
                        ConstantMethodRef entry = constantPoolManager.getMethodRefEntry(className, "valueOf", signature);
                        int index = constantPoolManager.getEntryIndex(entry);
                        return new InvokeStaticInstruction( classManager, 0, index, instruction);
                    } catch (ConstantPoolEntryException e) {
                        e.printStackTrace(System.out); // TODO: find a better solution
                        throw new ClassFileException(e); // TODO: we need a better solution
                    }

                }

            }
        }

        private class ClassParameter implements ParameterInstruction {
            private final String className;

            public ClassParameter(String className) {
                this.className = className;
            }

            @Override
            public int size() {
                return 1;
            }

            @Override
            public AbstractInstruction createInstruction(ClassManager classManager, MethodManager methodManager, Slot slot, AbstractInstruction instruction) {
                int currentSlot = slot.get();
                int opCode;
                String name;
                if (currentSlot > 3) {
                    opCode = InstructionEntryFactory.ALOAD;
                    name = "ALOAD";
                } else {
                    opCode = InstructionEntryFactory.ALOAD_0 + currentSlot;
                    name = String.format("%s_%d", "ALOAD", currentSlot);
                }
                slot.add(1);
                return new LoadOrStoreInstruction(opCode, currentSlot, 1, name, instruction);
            }

        }
    }

    private class Slot {
        private int slot;

        Slot(int slot) {
            this.slot = slot;
        }

        public int get() {
            return slot;
        }

        public void add(int size) {
            slot += size;
        }
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeShort(nameIndex);
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        try (DataOutputStream dos = new DataOutputStream(bos)) {
            dos.writeShort(maxStack);
            dos.writeShort(maxLocals);
            dos.writeInt(code.length);
            dos.write(code);
            exceptionTableManager.write(dos);
            dos.writeShort(attributes.length);
            for(AttributeManager attributeManager : attributes) {
                attributeManager.write(dos);
            }
        }
        byte[] data = bos.toByteArray();
        os.writeInt(data.length);
        os.write(data);
    }
}
