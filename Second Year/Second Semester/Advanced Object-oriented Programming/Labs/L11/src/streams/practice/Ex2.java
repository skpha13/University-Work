package streams.practice;

import java.util.Arrays;
import java.util.List;

//Write a method that converts all strings in a list to their upper case.
public class Ex2 {

    public static void main(String[] args) {
        List<String> colours = Arrays.asList("red", "green", "blue");

        colours.stream()
                .map(String::toUpperCase)
                .forEach(System.out::println);
    }
}
