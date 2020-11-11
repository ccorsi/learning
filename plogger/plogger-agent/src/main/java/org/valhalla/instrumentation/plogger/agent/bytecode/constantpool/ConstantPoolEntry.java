package org.valhalla.instrumentation.plogger.agent.bytecode.constantpool;

import org.valhalla.instrumentation.plogger.agent.bytecode.classes.ClassFile;
import org.valhalla.instrumentation.plogger.agent.bytecode.classes.ClassFileWriter;

import java.io.DataOutput;
import java.io.IOException;

public interface ConstantPoolEntry extends ConstantPoolEntryTag, ClassFileWriter {

    void validate(ClassFile classFile) throws ConstantPoolEntryException;

}
