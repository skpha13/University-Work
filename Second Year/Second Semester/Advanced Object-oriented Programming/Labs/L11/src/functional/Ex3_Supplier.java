package functional;

import java.util.function.*;

public class Ex3_Supplier {

    public static void main(String[] args) {
        System.out.println("getAsBoolean: " + getAsBoolean());
        System.out.println("getAsDouble: " + getAsDouble());
        System.out.println("getAsInt: " + getAsInt());
        System.out.println("getAsLong: " + getAsLong());
        System.out.println("asString: " + asString(false));
    }

    public static boolean getAsBoolean() {
        BooleanSupplier booleanSupplier = () -> true;
        return booleanSupplier.getAsBoolean();
    }
    public static double getAsDouble() {
        DoubleSupplier pi = () -> Math.PI;
        return pi.getAsDouble();
    }
    public static int getAsInt() {
        IntSupplier maxInteger = () -> Integer.MAX_VALUE;
        return maxInteger.getAsInt();
    }
    public static long getAsLong() {
        LongSupplier maxLongValue = () -> Long.MAX_VALUE;
        return maxLongValue.getAsLong();
    }
    public static String asString(boolean empty) {
        Supplier<String> message = () -> {
            if (empty) {
                return "";
            } else {
                return "Get a string";
            }
        };
        return message.get();
    }
}
