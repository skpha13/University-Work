package functional;

import java.util.function.BinaryOperator;
import java.util.function.DoubleBinaryOperator;
import java.util.function.IntBinaryOperator;
import java.util.function.LongBinaryOperator;

public class Ex6_BinaryOperator {

    public void add() {
        BinaryOperator<Integer> add = (a, b) -> a + b;
        Integer sum = add.apply(10, 12);
        System.out.println(sum.intValue());
    }
    public void addNumbers() {
        IntBinaryOperator add2 = (a, b) -> a + b;
        int sum = add2.applyAsInt(10, 12);
        System.out.println(sum);
    }
    public void multiplyNumbers() {
        LongBinaryOperator add2 = (a, b) -> a * b;
        long product = add2.applyAsLong(10, 12);
        System.out.println(product);
    }
    public void powerToNumber() {
        DoubleBinaryOperator add2 = (a, b) -> Math.pow(a, b);
        double powerRet = add2.applyAsDouble(10, 2);
        System.out.println(powerRet);
    }

}
