package org.valhalla.instrumentation.plogger.agent.bytecode.constantpool;

public interface ConstantPoolEntryTag {
    final static int UTF8 = 1;
    final static int INTEGER = 3;
    final static int FLOAT = 4;
    final static int LONG = 5;
    final static int DOUBLE = 6;
    final static int CLASS = 7;
    final static int STRING = 8;
    final static int FIELD = 9;
    final static int METHOD = 10;
    final static int INTERFACE_METHOD = 11;
    final static int NAME_AND_TYPE = 12;
    final static int METHOD_HANDLE = 15; // jdk 7
    final static int METHOD_TYPE = 16; // jdk 7
    final static int DYNAMIC = 17; // jdk 11
    final static int INVOKE_DYNAMIC = 18; // jdk 7
    final static int MODULE = 19; // jdk 9
    final static int PACKAGE = 20; // jdk 9
}
