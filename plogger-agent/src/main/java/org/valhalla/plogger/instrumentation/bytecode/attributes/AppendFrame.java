package org.valhalla.plogger.instrumentation.bytecode.attributes;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.ByteArrayOutputStream;
import java.io.DataOutput;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.Arrays;

public class AppendFrame extends AbstractStackMapFrame {
    private final int offset;
    private final VerificationType[] verificationTypes;

    public AppendFrame(ClassFile classFile, CodeAttribute code, int frameType, int offset, VerificationType[] verificationTypes) {
        super(classFile, code, frameType);
        this.offset = offset;
        this.verificationTypes = verificationTypes;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        super.write(os);

        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        DataOutputStream dos = new DataOutputStream(bos);

        try {
            for(VerificationType type : verificationTypes) {
                type.write(dos);
            }
        } finally {
            dos.close();
        }

        byte[] bytes = bos.toByteArray();

        os.writeInt(bytes.length);
        os.write(bytes);
    }

    @Override
    public String toString() {
        return "AppendFrame{" +
                "offset=" + offset +
                ", verificationTypes=" + Arrays.toString(verificationTypes) +
                ", frameType=" + frameType +
                '}';
    }
}
