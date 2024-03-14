import animal.Animal;
import animal.Duck;

public class Main {
    public static void main(String[] args) {
        Animal a = new Duck("ducky", 2, "white", 2);

        System.out.println(a.getClass());
    }
}