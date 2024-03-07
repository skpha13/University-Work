package basics;

import java.util.Scanner;

public class ReadingScanner {

    public static void main(String[] args) {
        // The Scanner class is useful when reading values, as it has utility methods for most primitives.
        Scanner scanner;

        // It can be set to read from a specific string
        scanner = new Scanner("Old McDonald had a farm");

        // or from the System console.
        scanner = new Scanner(System.in);

        // It can read booleans
        boolean a = scanner.nextBoolean();

        // numeric types
        byte b = scanner.nextByte();
        int c = scanner.nextInt();
        double d = scanner.nextDouble();

        // whole lines of text
        String line = scanner.nextLine();

        // It can also check if the next element to be read is of a specific type (or is available, in case the file has
        // not been read fully already
        if (scanner.hasNextInt()) {
            c = scanner.nextInt();
        }
    }
}
