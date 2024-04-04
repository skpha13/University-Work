package enums;


/**
 * Enum care ajuta o gradina zoologica sa tina evidenta traficului de vizitatori pe sezon/anotimp
 */
public enum Season {
    WINTER("Low"), SPRING("Medium"), SUMMER("High"), FALL("Medium");

    // variabila de instanta (private final - ca proprietatile enumerarii sa nu poata fi modificare)
    private final String expectedVisitors;


    //constructor
    Season(String expectedVisitors) {
        this.expectedVisitors = expectedVisitors;
    }


    // metoda de instanta
    public void printExpectedVisitors() {
        System.out.println(expectedVisitors);
    }
}
