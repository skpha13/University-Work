package test.immutability;

import immutability.Birthday;
import immutability.ImmutablePerson;

public class TestImmutablePerson {
    public static void main(String[] args) {
        Birthday birthday = new Birthday();
        birthday.setMonth("June");
        birthday.setDay(5);
        ImmutablePerson person = new ImmutablePerson("Mihai", birthday);
        System.out.println(person);

        birthday.setMonth("December");
        System.out.println(person);
    }
}
