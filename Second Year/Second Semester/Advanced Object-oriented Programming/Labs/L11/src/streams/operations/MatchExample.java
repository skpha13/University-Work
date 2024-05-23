package streams.operations;

import java.util.stream.Stream;

public class MatchExample {

    public static void main(String[] args) {
        Stream<String> stream = Stream.of("one", "two", "three", "four");
        boolean anyMatch = stream.anyMatch(s -> s.contains("four"));
        System.out.println(anyMatch);

        stream = Stream.of("four", "four", "four", "four");
        boolean allMatch = stream.allMatch(s -> s.contains("four"));
        System.out.println(allMatch);

        stream = Stream.of("one", "two", "three", "four");
        boolean noneMatch = stream.noneMatch(s -> s.contains("seven"));
        System.out.println(noneMatch);

    }
}
