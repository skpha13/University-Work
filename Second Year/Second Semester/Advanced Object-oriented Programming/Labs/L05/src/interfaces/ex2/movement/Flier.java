package interfaces.ex2.movement;

public interface Flier extends BaseMovement {

    @Override
    default void move() {
        System.out.println("I can fly!");
    }
}
