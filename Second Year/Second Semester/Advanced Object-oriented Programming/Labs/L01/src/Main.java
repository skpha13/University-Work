import java.util.Scanner;

public class Main {
    static long factorial(int n) {
        long result = 1;
        for (int i=1; i<=n; i++) {
            result *= i;
        }

        return result;
    }

    public static void main(String[] args) {
        Scanner read = new Scanner(System.in);
        System.out.println("Enter number: ");
        int n = read.nextInt();
        read.close();

        System.out.println("Rezultat: " + factorial(n));
    }
}