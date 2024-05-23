package streams.practice;

import java.util.Arrays;
import java.util.List;

//Write a method that returns a comma-separated string based on a given list of integers.
// Each element should be preceded by the letter 'e' if the number is even, and preceded by the letter 'o'
// if the number is odd. For example, if the input list is (3,44), the output should be 'o3,e44'.
public class Ex4 {

    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(3, 44);

        list.stream()
                .map(s -> s % 2 == 0 ? "e" + s : "o" + s)
                .reduce((s1, s2) -> s1 + "," + s2)
                .ifPresent(System.out::println);

    }
}
