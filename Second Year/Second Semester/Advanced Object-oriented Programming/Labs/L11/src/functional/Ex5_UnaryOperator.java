package functional;

import java.util.function.DoubleUnaryOperator;
import java.util.function.IntUnaryOperator;
import java.util.function.LongUnaryOperator;
import java.util.function.UnaryOperator;

public class Ex5_UnaryOperator {

    public void convertToUppercase() {
        UnaryOperator<String> convertToUppercase = String::toUpperCase;
        String uppercase = convertToUppercase.apply("this will be all uppercase");
                System.out.println(uppercase);
    }
    public void doubleIt(int d) {
        IntUnaryOperator doubledIt = x -> x * 2;
        System.out.println(doubledIt.applyAsInt(d));
    }
    public void squareItLongUnaryOperator() {
        LongUnaryOperator squareIt = x -> x * x;
        System.out.println(squareIt.applyAsLong(12));
    }
    public void squareItDoubleUnaryOperator() {
        DoubleUnaryOperator squareIt = x -> x * x;
        System.out.println(squareIt.applyAsDouble(12));
    }
}
