package streams.practice;

import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

//Given a list of strings, write a method that returns a list of all strings that start with the letter 'a' (lower case)
// and have exactly 3 letters
public class Ex3 {

    public static void main(String[] args) {
        List<String> list = Arrays.asList("ana", "maria", "ani", "adelina", "Ana"); //2

        List<String> collect = list.stream()
                .filter(s -> s.length() == 3 && s.charAt(0) == 'a')
                .collect(Collectors.toList());

        System.out.println(collect);
    }
}
