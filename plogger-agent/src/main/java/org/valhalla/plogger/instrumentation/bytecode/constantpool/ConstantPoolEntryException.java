package org.valhalla.plogger.instrumentation.bytecode.constantpool;

public class ConstantPoolEntryException extends Throwable {
    public ConstantPoolEntryException(String message) {
        super(message);
    }

    public ConstantPoolEntryException(Throwable throwable) {
        super(throwable);
    }
}
