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

import java.io.DataOutput;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.NoSuchElementException;

public abstract class AbstractInstruction implements InstructionEntry {
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

    protected abstract void sync();

    private void throwException() {
        throw new ClassFileException(String.format("Method not implemented for Instruction class: %s",
                getClass().getName()));
    };

    @Override
    public String toString() {
        return "Instruction{" +
                "opCode=" + opCode +
                ", name='" + name + '\'' +
                '}';
    }

    protected void addPriorInstruction(AbstractInstruction instruction) {
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

    @Override
    public void write(DataOutput os) throws IOException {
        // store instruction opCodeS
        os.write(opCode);
    }
}
