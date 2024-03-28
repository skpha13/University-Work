package test.ex2;

import interfaces.ex2.Horse;

public class TestHorse {

    public static void main(String[] args) {
        Horse horse = new Horse();
        horse.move();
        System.out.println(horse.hasFur());
    }
}
