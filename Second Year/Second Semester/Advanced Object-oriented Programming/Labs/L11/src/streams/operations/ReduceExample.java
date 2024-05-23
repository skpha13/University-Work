package streams.operations;

import java.util.Arrays;
import java.util.List;
import java.util.Optional;

public class ReduceExample {

    public static void main(String[] args) {
        List<String> numbers  = Arrays.asList("one", "two", "three", "four");

        Optional<String> reduced = numbers.stream()
                .reduce((s1,s2) -> s1 + "#" + s2);
        if (reduced.isPresent()) {
            System.out.println(reduced.get());
        }

    }
}
