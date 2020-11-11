module plogger.agent {
    requires java.instrument;
    // Would these be a problem if we don't export the agent transformer?  I don't think so.
    // exports org.valhalla.instrumentation.plogger.agent.AgentTransformer;
}