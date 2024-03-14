package animal;

public class Ape extends Animal {
    private String size;

    public Ape() {
        super();
        this.size = "None";
    }

    public Ape(String size) {
        this.size = size;
    }

    public Ape(String name, int noOfLegs, String size) {
        super(name, noOfLegs);
        this.size = size;
    }

    @Override
    public void move() {
        System.out.println("I can jump");
    }

    public String getSize() {
        return size;
    }

    public void setSize(String size) {
        this.size = size;
    }
}
