package org.valhalla.plogger.instrumentation.bytecode.manager;
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

import org.valhalla.plogger.instrumentation.bytecode.attributes.*;
import org.valhalla.plogger.instrumentation.bytecode.classes.ClassFileException;

import java.io.DataInputStream;
import java.io.IOException;

public class StackMapFrameManagerFactory {
    public static StackMapFrameManager create(StackMapFrame stackMapFrame) {
        if (stackMapFrame instanceof SameFrame) {
            return new SameFrameManager(stackMapFrame.getOffSet());
        } else if (stackMapFrame instanceof SameExtendedFrame) {
            return new SameFrameManager(stackMapFrame.getOffSet());
        } else if (stackMapFrame instanceof SameLocals1StackItemFrame) {
            SameLocals1StackItemFrame frame = (SameLocals1StackItemFrame)stackMapFrame;
            return new SameLocalsOneStackItemFrameManager(stackMapFrame.getOffSet(),
                    VerificationTypeManagerFactory.convert(frame.getVerificationType()));
        } else if (stackMapFrame instanceof SameLocal1StackItemExtendedFrame) {
            SameLocal1StackItemExtendedFrame frame = (SameLocal1StackItemExtendedFrame)stackMapFrame;
            return new SameLocalsOneStackItemFrameManager(stackMapFrame.getOffSet() + 64,
                    VerificationTypeManagerFactory.convert(frame.getVerificationType()));
        } else if (stackMapFrame instanceof AppendFrame) {
            AppendFrame frame = (AppendFrame)stackMapFrame;
            return new AppendFrameManager(frame.getOffSet(),
                    VerificationTypeManagerFactory.convert(frame.getVerificationTypes()));
        } else if (stackMapFrame instanceof ChopFrame) {
            ChopFrame frame = (ChopFrame)stackMapFrame;
            return new ChopFrameManager(frame.getFrameType(), frame.getOffSet());
        } else if (stackMapFrame instanceof FullFrame) {
            FullFrame frame = (FullFrame)stackMapFrame;
            return new FullFrameManager(frame.getOffSet(), frame.getLocalItems(), frame.getStackItems());
        }
        return null;
    }

    public static StackMapFrameManager create(DataInputStream dis) {
        try {
            int frameType = dis.readUnsignedByte();
            if (frameType < 0) {
                throw new ClassFileException(String.format("Invalid frame type: %d", frameType));
            } else if(frameType < 64) {
                return new SameFrameManager(frameType);
            } else if(frameType < 128) {
                return new SameLocalsOneStackItemFrameManager(frameType, VerificationTypeManagerFactory.create(dis));
            } else if(frameType < 247) {
                throw new ClassFileException(String.format("No StackMapFrame defined for reserved frame type: %d", frameType));
            } else if(frameType == 247) {
                return new SameLocalsOneStackItemFrameManager(dis.readUnsignedShort(), VerificationTypeManagerFactory.create(dis));
            } else if(frameType < 251) {
                return new ChopFrameManager(frameType, dis.readUnsignedShort());
            } else if(frameType == 251) {
                return new SameFrameManager(dis.readUnsignedShort());
            } else if(frameType < 255) {
                return new AppendFrameManager(frameType, dis);
            } else if(frameType == 255) {
                return new FullFrameManager(dis);
            } else {
                throw new ClassFileException(String.format("Invalid frame type: %d", frameType));
            }
        } catch (IOException e) {
            throw new ClassFileException(e);
        }
    }

}
