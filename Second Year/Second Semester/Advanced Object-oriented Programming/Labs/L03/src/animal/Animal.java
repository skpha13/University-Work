package animal;

public class Animal {
    private String name;
    private int noOfLegs;

    public Animal() {
        this.name = "Unknow";
        this.noOfLegs = 0;
    }

    public Animal(String name, int noOfLegs) {
        this.name = name;
        this.noOfLegs = noOfLegs;
    }

    public String getName() {
        return name;
    }

    public int getNoOfLegs() {
        return noOfLegs;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setNoOfLegs(int noOfLegs) {
        this.noOfLegs = noOfLegs;
    }

    public void move() {
        System.out.println("I can move");;
    }

    public void eat() {
        System.out.println("I can eat");
    }

    public void eat(String food) {
        System.out.println("I eat" + food);
    }
}
