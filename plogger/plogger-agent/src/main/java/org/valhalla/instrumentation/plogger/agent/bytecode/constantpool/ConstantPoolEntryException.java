package org.valhalla.instrumentation.plogger.agent.bytecode.constantpool;

public class ConstantPoolEntryException extends Throwable {
    public ConstantPoolEntryException(String message) {
        super(message);
    }

    public ConstantPoolEntryException(Throwable throwable) {
        super(throwable);
    }
}
