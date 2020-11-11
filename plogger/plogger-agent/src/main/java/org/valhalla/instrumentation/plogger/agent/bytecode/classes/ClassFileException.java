package org.valhalla.instrumentation.plogger.agent.bytecode.classes;

public class ClassFileException extends Throwable {
    public ClassFileException(String message) {
        super(message);
    }

    public ClassFileException(Throwable throwable) {
        super(throwable);
    }

    public ClassFileException(String message, Throwable throwable) {
        super(message, throwable);
    }
}
