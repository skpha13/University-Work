package animal;

public class Bird extends Animal {
    private String color;

    public Bird() {
        super();
        this.color = "None";
    }

    public Bird(String color) {
        this.color = color;
    }

    public Bird(String name, int noOfLegs, String color) {
        super(name, noOfLegs);
        this.color = color;
    }

    @Override
    public void move() {
        System.out.println("I can fly");
    }

    public void sing() {
        System.out.println("I can chirp");
    }

    public String getColor() {
        return color;
    }

    public void setColor(String color) {
        this.color = color;
    }
}
