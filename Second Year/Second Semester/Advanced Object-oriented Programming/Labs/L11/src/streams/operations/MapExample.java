package streams.operations;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class MapExample {

    public static void main(String[] args)
    {
        List<String> listOfStrings = Arrays.asList("1", "2", "3", "4", "5");

        List<Integer> listOfIntegers = listOfStrings.stream()
                .map(x -> Integer.valueOf(x))
                .collect(Collectors.toList());

        System.out.println(listOfIntegers);
    }
}
