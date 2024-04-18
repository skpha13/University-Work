package io.files;

import java.io.File;
import java.io.IOException;

public class Main {

    public static void main(String[] args) {
        File dir = createDirectory("lab7_dir_test");
        createFile(dir, "file1.txt");
        createFile(dir, "file2.txt");
        listFiles(dir);
    }

    private static void listFiles(File dir) {
        File[] files = dir.listFiles();
        for (File file : files) {
            System.out.println(file.getName());
        }
    }

    private static void createFile(File dir, String fileName) {
        String path = dir.getPath() + File.separator + fileName;
        File file = new File(path);
        try {
            if (!file.exists()) {
                file.createNewFile();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static File  createDirectory(String directoryName)  {
        File dir = new File(directoryName);
        boolean mkdir = dir.mkdir();
        if (mkdir) {
            System.out.println("Directory: " + directoryName + " created");
        } else {
            throw new RuntimeException("Cannot create directory "+ directoryName);
        }

        return dir;
    }

}
