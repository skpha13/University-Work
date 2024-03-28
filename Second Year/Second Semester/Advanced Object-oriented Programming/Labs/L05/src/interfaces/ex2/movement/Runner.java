package interfaces.ex2.movement;

public interface Runner extends BaseMovement {

    @Override
    default void move() {
        System.out.println("I can run!");
    }
}
