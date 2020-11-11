package org.valhalla.instrumentation.plogger.agent.bytecode.attributes;

import java.io.DataOutput;
import java.io.IOException;

public class DefaultAttribute implements ClassAttribute {
    private final byte[] data;
    private final int nameIndex;

    public DefaultAttribute(int nameIndex, byte[] data) {
        this.nameIndex = nameIndex;
        this.data = data;
    }

    @Override
    public void write(DataOutput os) throws IOException {
        os.writeShort(nameIndex);
        os.writeLong(data.length);
        os.write(data);
    }
}
