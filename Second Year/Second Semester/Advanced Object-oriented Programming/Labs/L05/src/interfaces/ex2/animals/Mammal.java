package interfaces.ex2.animals;

public interface Mammal extends BaseAnimal {

    default boolean hasFur() {
        return true;
    }
}
