package org.valhalla.multijar4j;

public class Main {
    public static void main(String args[]) {
        System.out.println("Simple example of loading version specific classes");
        VersionSpecificClass instance = new VersionSpecificClass();
        instance.printVersion();
    }
}
