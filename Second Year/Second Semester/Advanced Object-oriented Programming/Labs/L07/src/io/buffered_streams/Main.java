package io.buffered_streams;

import java.io.*;

public class Main {
    public static void main(String[] args) {
        readUsingBufferedInputStream();
        writeUsingBufferedOutputStream("BufferedOutputStream text");
        readUsingBufferedReader();
        writeUsingBufferedWriter("BufferedWriter text");
    }


    public static void readUsingBufferedInputStream() {
        try (BufferedInputStream bufferedInputStream = new
                BufferedInputStream(
                new FileInputStream("lab7/src/io/buffered_streams/input_BufferedInputStream.txt"))) {
            while (bufferedInputStream.available() > 0) {
                int read = bufferedInputStream.read();
                System.out.print((char) read);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void writeUsingBufferedOutputStream(String text) {
        try (BufferedOutputStream output = new BufferedOutputStream(
                new FileOutputStream("output.txt"))) {
            output.write(text.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void readUsingBufferedReader() {
        try (BufferedReader buffer = new BufferedReader(new
                FileReader("lab7/src/io/buffered_streams/input_BufferedReader.txt"))) {
            String line = buffer.readLine();
            while (line != null) {
                System.out.println(line);
                line = buffer.readLine();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void writeUsingBufferedWriter(String text) {
        try (BufferedWriter buffer = new BufferedWriter(new
                FileWriter("output.txt"))) {
            buffer.write(text);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
