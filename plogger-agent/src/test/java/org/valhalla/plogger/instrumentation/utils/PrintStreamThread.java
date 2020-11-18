package org.valhalla.plogger.instrumentation.utils;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class PrintStreamThread extends Thread {
    private final String prefix;
    private final InputStream is;

    public PrintStreamThread(String prefix, InputStream is) {
        super("PrintStreamThread:");
        setName(getName() + getId());
        this.prefix = prefix;
        this.is = is;
    }

    @Override
    public void run() {
        try (BufferedReader br = new BufferedReader(new InputStreamReader(is))) {
            String line = null;
            while ((line = br.readLine()) != null) {
                System.out.println(prefix + line);
            }
        } catch (IOException e) {
            e.printStackTrace(System.out);
        }
    }
}
