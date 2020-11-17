package org.valhalla.plogger.instrumentation.bytecode.attributes;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileException;

import java.io.DataInputStream;
import java.io.IOException;

public class VerificationTypeFactory implements VerificationTypeTag {
    public static VerificationType create(ClassFile classFile, DataInputStream dis) throws IOException, ClassFileException {
        int tag = dis.readUnsignedByte();
        VerificationType type;

        switch(tag) {
            case TOP:
                type = VerificationType.TopVariable;
                break;
            case INTEGER:
                type = VerificationType.IntegerVariable;
                break;
            case FLOAT:
                type = VerificationType.FloatVariable;
                break;
            case DOUBLE:
                type = VerificationType.DoubleVariable;
                break;
            case LONG:
                type = VerificationType.LongVariable;
                break;
            case OBJECT:
                type = new ObjectVariable(classFile, dis.readUnsignedShort());
                break;
            case UNINITIALIZED:
                type = new UninitializedVariable(classFile, dis.readUnsignedShort());
                break;
            case UNINITIALIZED_THIS:
                type = VerificationType.UninitializedThisVariable;
                break;
            default:
                throw new ClassFileException("Unknown Verification type: " + tag);
        }

        return type;
    }
}
