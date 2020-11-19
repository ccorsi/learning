package org.valhalla.plogger.instrumentation.bytecode.attributes;

/*
MIT License

Copyright (c) 2020 Claudio Corsi

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 */

import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFile;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileException;

import java.io.DataInputStream;
import java.io.IOException;

public class StackMapFrameFactory {
    public static StackMapFrame createStackMapFrame(ClassFile classFile, CodeAttribute code, DataInputStream dis) throws IOException, ClassFileException {
        int frameType = dis.readUnsignedByte();
        StackMapFrame frame = null;
        if (frameType >= 0 && frameType < 64) {
            // same frame
            frame = new SameFrame(classFile, code, frameType);
        } else if (frameType > 63 && frameType < 128) {
            // same locals 1 stack item frame
            VerificationType verificationType = VerificationTypeFactory.create(classFile, dis);
            frame = new SameLocals1StackItemFrame(classFile, code, frameType, verificationType);
        } else if (frameType > 127 && frameType < 247) {
            // reserved for future features
            throw new ClassFileException("StackMapFrame tag: " + frameType + " not implemented");
        } else if (frameType == 247) {
            // same locals 1 stack item extended frame
            int offset = dis.readUnsignedShort();
            VerificationType verificationType = VerificationTypeFactory.create(classFile, dis);
            frame = new SameLocal1StackItemExtendedFrame(classFile, code, frameType, offset, verificationType);
        } else if (frameType > 247 && frameType < 251) {
            // chop frame
            int offset = dis.readUnsignedShort();
            frame = new ChopFrame(classFile, code, frameType, offset);
        } else if (frameType == 251) {
            // same extended frame
            int offset = dis.readUnsignedShort();
            frame = new SameExtendedFrame(classFile, code, frameType, offset);
        } else if (frameType > 251 && frameType < 255) {
            // append frame
            int offset = dis.readUnsignedShort();
            VerificationType[] verificationTypes = new VerificationType[frameType - 251];
            for(int idx = 0 ; idx < verificationTypes.length ; idx++) {
                verificationTypes[idx] = VerificationTypeFactory.create(classFile, dis);
            }
            frame = new AppendFrame(classFile, code, frameType, offset, verificationTypes);
        } else if (frameType == 255) {
            // full frame
            int offset = dis.readUnsignedShort();
            int size = dis.readUnsignedShort();
            VerificationType[] locals = new VerificationType[size];
            for (int idx = 0 ; idx < size ; idx++) {
                locals[idx] = VerificationTypeFactory.create(classFile, dis);
            }
            size = dis.readUnsignedShort();
            VerificationType[] stackItems = new VerificationType[size];
            for (int idx = 0 ; idx < size ; idx++) {
                stackItems[idx] = VerificationTypeFactory.create(classFile, dis);
            }
            frame = new FullFrame(classFile, code, frameType, offset, locals, stackItems);
        } else {
            // invalid value raise exception
            throw new ClassFileException("Invalid StackMapFrame tag: " + frameType);
        }
        return frame;
    }
}
