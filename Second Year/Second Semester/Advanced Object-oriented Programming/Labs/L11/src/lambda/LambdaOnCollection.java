package lambda;

import java.util.ArrayList;
import java.util.List;

public class LambdaOnCollection {
    public static void main(String[] args) {
        List<String> colors = new ArrayList<>();
        colors.add("Red");
        colors.add("Green");
        colors.add("Blue");
        colors.add("Yellow");
        colors.add("Pink");
        colors.forEach(color -> System.out.println(color));
    }
}
