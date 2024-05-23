package streams.practice;

import java.util.Arrays;
import java.util.List;
import java.util.OptionalDouble;

// Write a method that returns the average of a list of integers.
public class Ex1 {

    public static void main(String[] args) {
        List<Integer> ints = Arrays.asList(1, 2, 3, 4, 5);

        int sum = ints.stream().mapToInt(i -> i).sum();
        long count = ints.stream().count();

        System.out.println(sum / count);

        OptionalDouble average = ints.stream().mapToInt(i -> i).average();

        if (average.isPresent()) {
            System.out.println("Average is " + average.getAsDouble());
        } else {
            System.out.println("Cannot compute average");
        }
    }
}
