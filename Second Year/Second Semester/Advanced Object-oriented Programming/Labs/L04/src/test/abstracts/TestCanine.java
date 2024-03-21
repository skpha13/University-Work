package test.abstracts;

import abstracts.Canine;
import abstracts.Wolf;

public class TestCanine {
    public static void main(String[] args) {
        //Canine canine = new Canine(); // 'Canine' is abstract; cannot be instantiated
        Canine canine = new Wolf(); // initialisation through subclass constructor
        canine.makeSound();
    }
}
