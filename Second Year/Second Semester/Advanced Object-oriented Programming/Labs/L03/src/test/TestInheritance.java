package test;

import animal.Animal;
import animal.Ape;

public class TestInheritance {

    public static void main(String[] args) {
        Animal animal = new Animal("dog", 4);
        animal.move();

        Ape ape = new Ape("gorrila", 2, "big");
        ape.move();
    }

}
