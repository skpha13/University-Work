package test;

import animal.Animal;
import animal.Bird;
import animal.Ape;

public class TestPolymorphism {
    public static void main(String[] args) {
        Animal a1 = new Animal();
        Animal a2 = new Ape( "gorilla", 2, "big");
        Animal a3 = new Bird( "sparrow", 2, "gray");

        moveAndEat(a1);
        moveAndEat(a2);
        moveAndEat(a3);
    }

    public static void moveAndEat(Animal animal) {
        animal.move();
        animal.eat();
    }
}
