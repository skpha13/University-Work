package functional;

import java.util.function.DoubleUnaryOperator;
import java.util.function.IntUnaryOperator;
import java.util.function.LongUnaryOperator;
import java.util.function.UnaryOperator;

public class Ex5_UnaryOperator {
    public static void main(String[] args) {
        double d = 3.5;
        long dd = 4;

        squareItDoubleUnaryOperator(d);
        squareItLongUnaryOperator(4);
    }

    public void convertToUppercase() {
        UnaryOperator<String> convertToUppercase = String::toUpperCase;
        String uppercase = convertToUppercase.apply("this will be all uppercase");
                System.out.println(uppercase);
    }
    public void doubleIt(int d) {
        IntUnaryOperator doubledIt = x -> x * 2;
        System.out.println(doubledIt.applyAsInt(d));
    }
    public static void squareItLongUnaryOperator(long d) {
        LongUnaryOperator squareIt = x -> x * x;
        System.out.println(squareIt.applyAsLong(d));
    }
    public static void squareItDoubleUnaryOperator(double d) {
        DoubleUnaryOperator squareIt = x -> x * x;
        System.out.println(squareIt.applyAsDouble(d));
    }
}
