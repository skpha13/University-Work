package functional;

import java.util.function.*;

public class Ex2_Predicate {

    public static void main(String[] args) {
        System.out.println("5 is even: " + isEvenPredicate(5));
        System.out.println("3 > 4: " + whichIsBiggerBiPredicate(3, 4));
        System.out.println("7.2 is positive: " + isPositiveDoublePredicate(7.2));
        System.out.println("-3 is negative: " + isNegativeIntPredicate(-3));
    }

    public static boolean isEvenPredicate(int nr) {
        Predicate<Integer> isEven = s -> s % 2 == 0;
        return isEven.test(nr);
    }

    public static boolean whichIsBiggerBiPredicate(int n1, int n2) {
        BiPredicate<Integer, Integer> isBigger = (x, y) -> x > y;
        return isBigger.test(n1, n2);
    }

    public static boolean isPositiveDoublePredicate(double n) {
        DoublePredicate isPositive = x -> x > 0;
        return isPositive.test(n);
    }
    public static boolean isNegativeIntPredicate(int n1) {
        IntPredicate isNegative = x -> x < 0;
        return isNegative.test(n1);
    }

}