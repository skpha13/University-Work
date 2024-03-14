package animal;

import java.util.Objects;

public class Duck extends Bird {
    private int length;

    public Duck(String name, int noOfLegs, String color, int length) {
        super(name, noOfLegs, color);
        this.length = length;
    }

    @Override
    public void move() {
        System.out.println("I can swim");
    }

    @Override
    public void sing() {
        System.out.println("I can quack");
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Duck duck = (Duck) o;
        return (length == duck.length &&
                this.getName().equals(duck.getName()) &&
                this.getNoOfLegs() == duck.getNoOfLegs() &&
                this.getColor().equals(duck.getColor()));
    }

    @Override
    public int hashCode() {
        return Objects.hash(this.getName(), this.getNoOfLegs(), length);
    }
}
