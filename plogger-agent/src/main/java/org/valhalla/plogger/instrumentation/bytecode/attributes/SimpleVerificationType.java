package org.valhalla.plogger.instrumentation.bytecode.attributes;

import java.io.DataOutput;
import java.io.IOException;

public class SimpleVerificationType implements VerificationType, VerificationTypeTag {
    private final int tag;
    private final int size;

    public SimpleVerificationType(int tag, int size) {
        this.tag = tag;
        this.size = size;
    }

    @Override
    public int tag() {
        return tag;
    }

    @Override
    public int size() {
        return size;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.write(tag);
    }

    @Override
    public String toString() {
        String tagName = "n/a";
        switch(tag) {
            case TOP:
                tagName = "top";
                break;
            case INTEGER:
                tagName = "int";
                break;
            case FLOAT:
                tagName = "float";
                break;
            case LONG:
                tagName = "long";
                break;
            case DOUBLE:
                tagName = "double";
                break;
            case NULL:
                tagName = "null";
                break;
            case UNINITIALIZED_THIS:
                tagName = "uninitialized this";
                break;
        }
        return "VerificationType{" +
                "tag=" + tagName +
                ", size=" + size +
                '}';
    }
}
