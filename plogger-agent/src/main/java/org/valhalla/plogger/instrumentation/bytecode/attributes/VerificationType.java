package org.valhalla.plogger.instrumentation.bytecode.attributes;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileWriter;

public interface VerificationType extends ClassFileWriter {

    VerificationType TopVariable = new SimpleVerificationType(VerificationTypeTag.TOP, 1);
    VerificationType IntegerVariable = new SimpleVerificationType(VerificationTypeTag.INTEGER, 1);
    VerificationType FloatVariable = new SimpleVerificationType(VerificationTypeTag.FLOAT, 1);
    VerificationType DoubleVariable = new SimpleVerificationType(VerificationTypeTag.DOUBLE, 2);
    VerificationType LongVariable = new SimpleVerificationType(VerificationTypeTag.LONG, 2);
    VerificationType NullVariable = new SimpleVerificationType(VerificationTypeTag.NULL, 1);
    VerificationType UninitializedThisVariable = new SimpleVerificationType(VerificationTypeTag.UNINITIALIZED_THIS, 1);

    int tag();

    int size();

}
