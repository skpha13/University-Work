package functional;

import java.util.function.BiFunction;
import java.util.function.DoubleToIntFunction;
import java.util.function.ToDoubleBiFunction;

public class Ex1_Function {

    public static void main(String[] args) {

        int multiplyTwoIntsBiFunction = multiplyTwoIntsBiFunction(12, 34);
        System.out.println(multiplyTwoIntsBiFunction);

        int toIntFunction = convertDoubleToIntFunction(234.5);
        System.out.println(toIntFunction);

        double appliedAsDouble = powerTwoIntToDoubleBiFunction(2, 3);
        System.out.println(appliedAsDouble);
    }

    public static int multiplyTwoIntsBiFunction(int i1, int i2) {
        BiFunction<Integer, Integer, Integer> multiply = (a, b) -> a * b;
        return multiply.apply(i1, i2);
    }

    public static int convertDoubleToIntFunction(double d) {
        DoubleToIntFunction doubleToInt = num -> (int) num;
        return doubleToInt.applyAsInt(d);
    }

    public static double powerTwoIntToDoubleBiFunction(int i1, int i2) {
        ToDoubleBiFunction<Integer, Integer> raisedToPower = (a, b) -> Math.pow(a, b);
        double powerRet = raisedToPower.applyAsDouble(i1, i2);
        return powerRet;
    }

}