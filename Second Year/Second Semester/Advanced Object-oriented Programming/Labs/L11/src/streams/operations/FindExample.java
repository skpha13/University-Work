package streams.operations;

import java.util.Arrays;
import java.util.List;
import java.util.Optional;

public class FindExample {

    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

        Optional<Integer> first = list.stream()
                .filter(n -> n % 2 == 0)
                .findFirst();

        if (first.isPresent()) {
            System.out.println(first.get());
        }

        list = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

        Optional<Integer> any = list.stream()
                .filter(n -> n % 2 == 0)
                .findAny();

        if (any.isPresent()) {
            System.out.println(any.get());
        }
    }
}
