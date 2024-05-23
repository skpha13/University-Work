package streams.practice;

import java.util.Arrays;
import java.util.List;

// find the length of the longest string from an array of strings
public class Ex5 {

    public static void main(String[] args) {
        List<String> colours = Arrays.asList("Red", "Green", "Pink"); //5

        colours.stream()
                .map(s -> s.length())
                .max((x, y) -> x.compareTo(y))
                .ifPresent(x -> System.out.println(x));
    }
}
