package org.valhalla.plogger.instrumentation.bytecode.classes;

import java.io.DataOutput;
import java.io.IOException;

public interface ClassFileWriter {
    void write(DataOutput os) throws IOException;
}
