package org.valhalla.plogger.instrumentation.bytecode.instructions;
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
import org.valhalla.plogger.instrumentation.bytecode.constantpool.*;
import org.valhalla.plogger.instrumentation.bytecode.manager.ConstantPoolManager;

import java.io.DataOutput;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.NoSuchElementException;

public abstract class AbstractInstruction implements InstructionEntry {
    protected static final Debug debug = Debug.getDebug("instruction");

    private final int opCode;
    private final String name;
    private AbstractInstruction next;
    private AbstractInstruction prior;
    private List<InstructionListener> listeners;

    protected AbstractInstruction(int opCode, String name, InstructionEntry entry) {
        this.opCode = opCode;
        this.name = name;
        this.prior = this.next = null;
        addPriorInstruction((AbstractInstruction) entry);
    }

    @Override
    public int opCode() {
        return opCode;
    }

    @Override
    public String name() {
        return name;
    }

    @Override
    public abstract int stack();

    public void sync() {

    }

    private void throwException() {
        throw new ClassFileException(String.format("Method not implemented for Instruction class: %s",
                getClass().getName()));
    };

    /**
     * This method will determine the operand stack size of the passed AbstractConstantRef
     * constant pool entry index.  It will then return the total change that this call will
     * have on the operand stack.
     *
     * @param constantPoolIndex An entry index into the constant pool
     * @param operandStack The initial size of the operand stack size
     * @return The total impact on the operand stack for the given constant ref
     */
    protected final int calculateOperandStack(ConstantPoolManager constantPoolManager, int constantPoolIndex,
                                              int operandStack) {
        String signature;
        int nameAndTypeIndex;
        ConstantPoolEntry entry = constantPoolManager.getEntry(constantPoolIndex);
        if (entry instanceof AbstractConstantRef) {
            AbstractConstantRef abstractConstantRef = (AbstractConstantRef)entry;
            nameAndTypeIndex = abstractConstantRef.getNameAndTypeIndex();
        } else if (entry instanceof AbstractConstantDynamic){
            AbstractConstantDynamic abstractConstantDynamic = (AbstractConstantDynamic)entry;
            nameAndTypeIndex = abstractConstantDynamic.getNameAndTypeIndex();
        } else {
            throw new ClassFileException(String.format("Unable to determine constant pool entry type at %d for type %s",
                    constantPoolIndex, entry));
        }
        ConstantNameAndType constantNameAndType = constantPoolManager.getEntry(nameAndTypeIndex);
        int descriptorIndex = constantNameAndType.getDescriptorIndex();
        ConstantUtf8 string = constantPoolManager.getEntry(descriptorIndex);
        signature = string.getString();
        int pos = signature.indexOf('(') + 1;
        for( ; pos < signature.length() && signature.charAt(pos) != ')' ; pos++) {
            switch(signature.charAt(pos)) {
                case 'Z': // boolean
                case 'B': // byte
                case 'S': // short
                case 'I': // int
                case 'F': // float
                case 'C': // char
                    operandStack--;
                    break;
                case 'J': // long
                case 'D': // double
                    operandStack -= 2;
                    break;
                case 'L': // Object
                    operandStack--;
                    while( signature.charAt(pos) != ';' ) pos++;
                    break;
                case '[': // array type structure
                    operandStack--;
                    while ( signature.charAt(pos) == '[' ) pos++;
                    if (signature.charAt(pos) == 'L')
                        while ( signature.charAt(pos) != ';' ) pos++;
                    break;
                case 'V': // void
                    break;
                default:
                    throw new ClassFileException(String.format("Invalid type: %s at %d", signature.charAt(pos), pos));
            }
        }
        pos++; // increment past ) character
        if (pos < signature.length()) {
            switch (signature.charAt(pos)) {
                case 'Z': // boolean
                case 'B': // byte
                case 'S': // short
                case 'I': // int
                case 'F': // float
                case 'C': // char
                case 'L': // Object
                case '[': // array type structure
                    operandStack++;
                    break;
                case 'J': // long
                case 'D': // double
                    operandStack += 2;
                    break;
                case 'V': // void
                    break;
            }
        }

        return operandStack;
    }

    @Override
    public String toString() {
        return "Instruction{" +
                "opCode=" + opCode +
                ", name='" + name + '\'' +
                '}';
    }

    public final void addPriorInstruction(AbstractInstruction instruction) {
        if (instruction != null) {
            instruction.next = this;
        }
        prior = instruction;
    }

    public AbstractInstruction getNext() {
        return next;
    }

    public AbstractInstruction getPrior() {
        return prior;
    }

    public Iterator<AbstractInstruction> iterator() {
        return new Iterator<AbstractInstruction>() {
            private AbstractInstruction current = AbstractInstruction.this;
            @Override
            public boolean hasNext() {
                return current != null;
            }

            @Override
            public AbstractInstruction next() {
                if (current == null) {
                    throw new NoSuchElementException("No elements left");
                }
                AbstractInstruction next = current;
                current = current.next;
                return next;
            }

            @Override
            public void remove() {
                // do nothing
            }
        };
    }

    public void addListener(InstructionListener instructionListener) {
        if (listeners == null)
            listeners = new ArrayList<>();

        listeners.add(instructionListener);
    }

    public void update(int pos) {
        // Each instruction will notify the listeners
        if (listeners != null) {
            for(InstructionListener listener : listeners) {
                listener.event(this, pos);
            }
        }
    }

    protected AbstractInstruction getOffsetInstruction(int offset) {
        int current = 0;
        AbstractInstruction instruction = this;

        if (offset < 0) {
            do {
                instruction = instruction.getPrior();
                if (instruction == null) {
                    break; // break out of the loop
                }
                current -= instruction.size();
            } while ( current > offset);
        } else {
            for (; instruction != null && current < offset; instruction = instruction.getNext() ) {
                current += instruction.size();
            }
        }

        if (current != offset) {
            throw new ClassFileException(String.format("No instruction with offset %d found from instruction %s",
                    offset, this));
        }
        return instruction;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        // store instruction opCodeS
        os.write(opCode);
    }
}
