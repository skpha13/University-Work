package streams.operations;

import java.util.Arrays;
import java.util.List;
import java.util.Optional;

public class MinMaxCountExample {

    public static void main(String[] args) {
        List<Integer> list = Arrays.asList(1, 2, 3, 4, 5, 6, 7, 8, 9, 10);

        Optional<Integer> max = list.stream().max(Integer::compareTo);
        if (max.isPresent()) {
            System.out.println("Max is : " + max.get());
        }

        Optional<Integer> min = list.stream().min((i, j) -> i.compareTo(j));
        min.ifPresent(integer -> System.out.println("Min is :" + integer));


        System.out.println("Count: " + list.stream().count());

        Optional<String> opt = Optional.of("NonNullstring");
        Optional<String> nullableOpt = Optional.ofNullable(null);

        System.out.println(opt.isPresent());
        System.out.println(nullableOpt.isPresent());


    }
}
