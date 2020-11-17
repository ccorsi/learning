package org.valhalla.plogger.instrumentation.bytecode.attributes;

import com.sun.tools.javac.jvm.Code;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.DataOutput;
import java.io.IOException;
import java.util.Arrays;

public class FullFrame extends AbstractStackMapFrame {
    private final int offset;
    private final VerificationType[] locals;
    private final VerificationType[] stackItems;

    public FullFrame(ClassFile classFile, CodeAttribute code, int frameType, int offset, VerificationType[] locals, VerificationType[] stackItems) {
        super(classFile, code, frameType);
        this.offset = offset;
        this.locals = locals;
        this.stackItems = stackItems;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        super.write(os);

        os.writeShort(offset);
        os.writeShort(locals.length);
        for(VerificationType type : locals) {
            type.write(os);
        }
        os.writeShort(stackItems.length);
        for(VerificationType type : stackItems) {
            type.write(os);
        }
    }

    @Override
    public String toString() {
        return "FullFrame{" +
                "offset=" + offset +
                ", locals=" + Arrays.toString(locals) +
                ", stackItems=" + Arrays.toString(stackItems) +
                ", frameType=" + frameType +
                '}';
    }
}
