package test.immutability;

import immutability.Birthday;
import immutability.MutablePerson;

public class TestMutablePerson {
    public static void main(String[] args) {
        Birthday birthday = new Birthday();
        birthday.setMonth("June");
        birthday.setDay(5);
        MutablePerson person = new MutablePerson("Mihai", birthday);
        System.out.println(person);

        birthday.setMonth("December");
        System.out.println(person);
    }
}
