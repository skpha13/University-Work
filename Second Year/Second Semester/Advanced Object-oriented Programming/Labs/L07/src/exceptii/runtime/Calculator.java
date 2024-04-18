package exceptii.runtime;

public class Calculator {

    public static void main(String[] args) {
        int answer = 11 / 0;
        System.out.println(answer); // se arunca ArithmeticException
    }
}
