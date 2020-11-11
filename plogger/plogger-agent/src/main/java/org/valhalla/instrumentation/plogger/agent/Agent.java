package org.valhalla.instrumentation.plogger.agent;

import java.lang.instrument.Instrumentation;

public class Agent {
    public static void main(String[] args) {
        System.out.println(Agent.class.getName());
    }

    public static void premain(String agentArgs, Instrumentation inst) {
        addTransformer("PreMain", agentArgs, inst);
    }

    public static void agentmain(String agentArgs, Instrumentation inst) {
        addTransformer("AgentMain", agentArgs, inst);
    }

    private static void addTransformer(String type, String agentArgs, Instrumentation inst) {
        AgentTransformer transformer = new AgentTransformer(agentArgs);
//        inst.addTransformer(transformer, true);
        inst.addTransformer(transformer);
        System.out.println(type + ": Added agent transformer: " + transformer + " for agent args: " + agentArgs);
        Runtime.getRuntime().addShutdownHook(new AgentShutdownHookThread(inst));
    }

    private static class AgentShutdownHookThread extends Thread {
        private final Instrumentation inst;
        private final Class<?>[] classes;

        public AgentShutdownHookThread(Instrumentation inst) {
            this.inst = inst;
            classes = inst.getAllLoadedClasses();
            System.out.println("ctor: Loaded classes count: " + classes.length);
        }

        @Override
        public void run() {
            System.out.println("Calling the AgentShutdownHookThread");
            System.out.println("run: Loaded classes count: " + classes.length);
            System.out.println("run: Loaded classes count: " + inst.getAllLoadedClasses().length);
        }
    }
}
