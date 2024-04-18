package exceptii;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

public class Try {

    public static void main(String[] args) {
        // 1. nu putem avea try simplu -> 'catch' or 'finally' expected
        /*try {
            // try block
        }*/

        // 2. try-catch
        try {
            System.out.println("2.try block");
        } catch (Exception e) {
            // handle exception
        }

        // 3. try-finally
        try {
            System.out.println("3. try block");
        } finally {
            System.out.println("3. finally block");
        }

        // 4. try-catch-finally
        try {
            System.out.println("4. try block");
        } catch (Exception e) {
            System.out.println("4. catch block");
        } finally {
            System.out.println("4. finally block");
        }

        // 5. multiple catch
        try {
            System.out.println("5. calling methodThrowingException method");
            methodThrowingException();
        } catch (FileNotFoundException e) {
            System.out.println("5. FileNotFoundException catch block");
        } catch (IOException e) {
            System.out.println("5. IOException catch block");
        }

        // 6. multi-catch
        try {
            System.out.println(Integer.parseInt(args[1]));
        } catch (ArrayIndexOutOfBoundsException | NumberFormatException e) {
            System.out.println("6. Missing or invalid input");
        }

        // 7. try-with-resources - inchide automat resursele (ce implementeaza AutoCloseable) dechise in clauza try
        try (FileInputStream is = new FileInputStream("myfile.txt")) {
            System.out.println("7.try block");
            // Read file data
        } catch (IOException e) {
            System.out.println("7. catch block");
            e.printStackTrace();
        }

    }

    public static void methodThrowingException() throws IOException {
        throw new IOException();
    }

}
