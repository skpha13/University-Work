package io.data_streams;

import java.io.*;

public class Main {

    public static void main(String[] args) {
        writeUsingDataOutputStream("Written using DataOutputStream");
        readUsingDataInputStream();
    }

    public static void readUsingDataInputStream() {
        try (DataInputStream dataInputStream = new DataInputStream(new
                FileInputStream("L7-dataio.txt"))) {
            while (dataInputStream.available() > 0) {
                char content = dataInputStream.readChar();
                System.out.print(content);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public static void writeUsingDataOutputStream(String text) {
        try (DataOutputStream dataOutputStream = new DataOutputStream(new
                FileOutputStream("L7-dataio.txt"))) {
            dataOutputStream.writeChars(text);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
