package io.byte_streams;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class Main {

    public static void main(String[] args) {
        readUsingFileOutputStream("lab7/L7-input.txt");

        writeUsingFileOutputStream("L7-output.txt", "This is a text");
        writeUsingFileOutputStream("./lab7/L7-output.txt", "This is another text");

        writeUsingFileOutputStream("./lab7/L7-output-append.txt", "First line \n", true);
        writeUsingFileOutputStream("./lab7/L7-output-append.txt", "Second line \n", true);
    }


    public static void readUsingFileOutputStream(String fileName) {
        try (FileInputStream in = new FileInputStream(fileName)) {
            int c;
            while ((c = in.read()) != -1) {
                System.out.print((char) c);
            }
        } catch (IOException e) {
            System.out.println("Cannot read file");
        }
    }

    public static void writeUsingFileOutputStream(String fileName, String text)  {
        writeUsingFileOutputStream(fileName, text, false);
    }

    public static void writeUsingFileOutputStream(String fileName, String text, Boolean append)  {
        try (FileOutputStream out = new FileOutputStream(fileName, append)) {
            out.write(text.getBytes());
        } catch (IOException e) {
            System.out.println("Cannot write to file");
        }
    }
}
