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
import org.valhalla.plogger.instrumentation.bytecode.instructions.AbstractInstruction;
import org.valhalla.plogger.instrumentation.bytecode.instructions.EndInstruction;
import org.valhalla.plogger.instrumentation.bytecode.instructions.InstructionEntry;
import org.valhalla.plogger.instrumentation.bytecode.instructions.InstructionEntryFactory;

import java.io.*;

/**
 * This is the instruction manager class that does the bulk of the work to manage
 * how each instruction is generated and updated during the process of instrumenting
 * the code.
 *
 * This manager needs to understand what types of instructions it will be creating
 * and how they are impacted by changes to the instruction code.  It should be able
 * to handle the following cases:
 *
 *  - exception table
 *  - branch instructions
 *      - if statements
 *      - goto statements
 *      - switch statements
 *  - stack map table updates
 *  - local variable table
 *  - local variable type table
 *  - line number table (not required but come be useful)
 *
 *  The above should be managed by those features and the instruction manager should
 *  provide a listener mechanism that those features can use to be updated whenever
 *  those instructions are being updated.  I wonder if we should create a normalize
 *  method that will be called when we are done updating the instructions.  This
 *  method will then give the different instruction entry the ability to updating
 *  its internal values that can then be used to generate the new byte code array.
 *
 *  This will create an instruction entry manager for each instruction.  Each instruction
 *  will contain the following information:
 *
 *      - opCode
 *      - operand stack effects (this can be static or dynamic)
 *      - instruction size (number of bytes that this instruction will require)
 */
public class InstructionManager {
    private final ClassManager classManager;
    private AbstractInstruction headInstruction;
    private byte[] code;

    public InstructionManager(ClassManager classManager, byte[] code) {
        this.classManager = classManager;
        this.code = code;
    }

    public boolean instrument(AbstractInstruction instruction, boolean isConstructor) {
        loadInstructions();
        AbstractInstruction firstInstruction = null;
        if (isConstructor) {
            // We need to add the instructions after the first instance of the invokespecial
            // instruction.
            AbstractInstruction invokeSpecialInstruction = headInstruction;
            while (invokeSpecialInstruction != null && invokeSpecialInstruction.opCode() != InstructionEntryFactory.INVOKESPECIAL) {
                invokeSpecialInstruction = invokeSpecialInstruction.getNext();
            }
            if (invokeSpecialInstruction == null || invokeSpecialInstruction.opCode() != InstructionEntryFactory.INVOKESPECIAL) {
                throw new ClassFileException("Did not find the invokespecial instruction");
            }
            // Get a reference to the next instruction after the invokespecial instruction
            AbstractInstruction nextInstruction = invokeSpecialInstruction.getNext();
            // Add the make invokespecial instruction be prior to the instructions
            instruction.addPriorInstruction(invokeSpecialInstruction);
            // Get a reference to the last instruction of the injecting byte code.
            while (instruction.getNext() != null) {
                instruction = instruction.getNext();
            }
            // Make the next instruction after the invokespecial instruction be the last added instruction
            nextInstruction.addPriorInstruction(instruction);
        } else {
            // Append the current set of instructions with the passed instructions
            AbstractInstruction current = instruction;
            while (current.getNext() != null) {
                current = current.getNext();
            }
            headInstruction.addPriorInstruction(current);
            headInstruction = instruction;
        }
        return true;
    }

    private void loadInstructions() {
        if (headInstruction == null) {
            int cnt = 0;
            try (DataInputStream dis = new DataInputStream(new ByteArrayInputStream(code))) {
                int pos = 0;
                InstructionEntry entry = null;
                InstructionEntry prior = null;
                for (int opCode = dis.read(); opCode > -1; opCode = dis.read()) {
                    // Process the instruction and add it to the instructions list...
                    entry = InstructionEntryFactory.create(classManager, opCode, dis, pos, prior);
                    if (headInstruction == null) {
                        headInstruction = (AbstractInstruction)entry;
                    }
                    pos += entry.size();
                    prior = entry;
                    cnt++;
                }
                entry = new EndInstruction(entry);
                cnt++;
            } catch (IOException e) {
                throw new ClassFileException(e);
            }
            try {
                for (AbstractInstruction entry = headInstruction; entry != null; entry = entry.getNext()) {
                    // Synchronize the instructions by passing the entries to each instruction
                    // This is to allow the different instructions to sync themselves with
                    // other instructions that require syncing.
                    entry.sync();
                    if (cnt < 0) throw new ClassFileException("Infinite loop issue.");
                    cnt--;
                }
            } catch (ClassFileException e) {
                // TODO: Make these conditional
                int pos = 0;
                for (AbstractInstruction entry = headInstruction ; entry != null ; entry = entry.getNext()) {
                    System.out.println(String.format("%-5d: %s", pos, entry));
                    pos += entry.size();
                }
                throw e;
            }
        }
    }

    public AbstractInstruction getFirstInstruction() {
        loadInstructions();
        return this.headInstruction;
    }

    public byte[] getCode() {
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        try (DataOutputStream dos = new DataOutputStream(bos)) {
            for (AbstractInstruction instruction = headInstruction; instruction != null;
                 instruction = instruction.getNext()) {
                instruction.write(dos);
            }
        } catch (IOException e) {
            throw new ClassFileException(e);
        }
        return bos.toByteArray();
    }
}
