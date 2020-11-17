package org.valhalla.plogger.instrumentation.bytecode.constantpool;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileWriter;

public interface ConstantPoolEntry extends ConstantPoolEntryTag, ClassFileWriter {

    void validate() throws ConstantPoolEntryException;

    int entries();

}
