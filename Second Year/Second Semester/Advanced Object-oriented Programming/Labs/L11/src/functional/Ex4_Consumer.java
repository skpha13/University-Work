package functional;

import java.util.Arrays;
import java.util.function.*;

public class Ex4_Consumer {

    public static void main(String[] args) {
        printBiConsumer();
        convertToLowercase();
        printPrefix();
        printDoubleConsumer();
        printIntConsumer();
        printLongConsumer();
    }
    public static void printBiConsumer() {
        BiConsumer<String, String> echo = (x, y) -> {
            System.out.println(x);
            System.out.println(y);
        };
        echo.accept("This is first line.", "Here is another line.");
    }
    public static void convertToLowercase() {
        Consumer<String> convertToLowercase = s -> System.out.println(s.toLowerCase());
        convertToLowercase.accept("convert to ALL lowercase");
    }
    public static void printPrefix() {
        Consumer<String> sayHello = name -> System.out.println("Hello, " + name);
        for (String name : Arrays.asList("Silvia", "John", "Doe")) {
            sayHello.accept(name);
        }
    }
    public static void printDoubleConsumer() {
        DoubleConsumer echo = System.out::println;
        //echo = d -> System.out.println(d);
        echo.accept(3.3);
    }
    public static void printIntConsumer() {
        IntConsumer echo = System.out::println;
        echo.accept(3);
    }
    public static void printLongConsumer() {
        LongConsumer echo = System.out::println;
        echo.accept(34L);
    }
}
