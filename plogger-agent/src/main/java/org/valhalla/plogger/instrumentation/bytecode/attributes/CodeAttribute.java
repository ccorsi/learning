package org.valhalla.plogger.instrumentation.bytecode.attributes;

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;

import java.io.ByteArrayOutputStream;
import java.io.DataOutput;
import java.io.DataOutputStream;
import java.io.IOException;
import java.util.Arrays;

public class CodeAttribute implements ClassAttribute {
    private final int nameIndex;
    private final int maxStack;
    private final ClassAttribute[] attributes;
    private final CodeExceptionTable[] exceptions;
    private final byte[] code;
    private final int maxLocals;
    private final ClassFile classFile;

    @Override
    public String toString() {
        return "CodeAttribute{" +
                "nameIndex=" + nameIndex +
                ", maxStack=" + maxStack +
                ", attributes=" + Arrays.toString(attributes) +
                ", exceptions=" + Arrays.toString(exceptions) +
                ", code=" + Arrays.toString(code) +
                ", maxLocals=" + maxLocals +
                '}';
    }

    public CodeAttribute(ClassFile classFile, int nameIndex, int maxStack, int maxLocals, byte[] code, CodeExceptionTable[] exceptions, ClassAttribute[] attributes) {
        this.classFile = classFile;
        this.nameIndex = nameIndex;
        this.maxStack = maxStack;
        this.maxLocals = maxLocals;
        this.code = code;
        this.exceptions = exceptions;
        this.attributes = attributes;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        ByteArrayOutputStream bos = new ByteArrayOutputStream();
        DataOutputStream dos = new DataOutputStream(bos);
        dos.writeShort(maxStack);
        dos.writeShort(maxLocals);
        dos.writeInt(code.length);
        dos.write(code);
        dos.writeShort(exceptions.length);
        for( CodeExceptionTable exception : exceptions) {
            exception.write(dos);
        }
        dos.writeShort(attributes.length);
        for (ClassAttribute attribute : attributes) {
            attribute.write(dos);
        }

        dos.close();

        byte[] bytes = bos.toByteArray();

        os.writeShort(nameIndex);
        os.writeInt(bytes.length);
        os.write(bytes);

    }

    public StackMapTable getStackMapTable() {
        StackMapTable table = null;

        for (ClassAttribute attribute : attributes) {
            if (attribute instanceof StackMapTable) {
                table = (StackMapTable) attribute;
                break;
            }
        }

        return table;
    }
}
