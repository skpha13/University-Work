package io.char_streams;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class Main {

    public static void main(String [] args) {
        readUsingFileReader();
        writeUsingFileWriter("Written using FileWriter");

    }

    public static void readUsingFileReader() {
        try (FileReader fileReader = new FileReader("lab7/L7-input.txt")){
            int content;
            while ((content = fileReader.read()) != -1) {
                System.out.print((char) content);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public static void writeUsingFileWriter(String text) {
        try (FileWriter fileWriter = new FileWriter("output.txt")) {
            fileWriter.write(text);
            fileWriter.append("-");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
