package org.valhalla.plogger.instrumentation;

import java.lang.instrument.Instrumentation;

public class AgentMain {
    public static void premain(String argString, Instrumentation inst) {
        parseArgs(argString);
        AgentClassFileTransformer transformer = new AgentClassFileTransformer();
        inst.addTransformer(transformer);
        System.out.println("Added Agent Transformer: " + transformer);
    }

    private static String parseArgs(String args) {
        return "";
    }
}
