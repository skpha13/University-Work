package interfaces.ex1;

public class Chicken implements Animal {

    int noOfLegs = 2;       //this does not override the 'noOfLegs' from the interface!

    @Override
    public String getName() {
        return "chicken";
    }

    @Override
    public void eat() {
        System.out.println("I eat grains!");
    }

    // optional override
    /*@Override
    public void printNoOfLegs() {
        System.out.println("I have " + noOfLegs + " legs");
    }*/




}
