package test.ex1;

import interfaces.ex1.Animal;
import interfaces.ex1.Cat;
import interfaces.ex1.Chicken;

public class TestEx1 {

    public static void main(String[] args) {
        Cat cat = new Cat();
        System.out.println("I am a " + cat.getName());
        cat.eat();
        cat.printNoOfLegs();

        Chicken chicken = new Chicken();
        System.out.println("I am a " + chicken.getName());
        chicken.eat();
        chicken.printNoOfLegs();

        //static method from interface call
        Animal.makeNoise();
    }
}
