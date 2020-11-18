package org.valhalla.plogger.instrumentation.utils;

import org.junit.jupiter.api.Assertions;

import java.io.File;
import java.io.FileFilter;

public class Utils {
    public static String getJavaCommand() {
        final String javaExecutableName = "java" + ((File.separatorChar == '\\') ? ".exe" : "");
        String javaHome = System.getProperty("java.home");
        File dir = new File(javaHome);
        File[] dirs = dir.listFiles(new FileFilter() {
            @Override
            public boolean accept(File file) {
                return "bin".equals(file.getName());
            }
        });

        Assertions.assertNotNull(dirs, "No bin directories were found");

        for (File file : dirs) {
            File[] javas = file.listFiles(
                    new FileFilter() {
                        @Override
                        public boolean accept(File file) {
                            return javaExecutableName.equals(file.getName());
                        }
                    }
            );
            if (javas != null && javas.length > 0) {
                return javas[0].getAbsolutePath();
            }
        }

        return Assertions.fail("No Java Command found for java.home: " + javaHome);
    }
}
