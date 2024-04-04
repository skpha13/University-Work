package test.enums;

import enums.Anotimp;

public class TestAnotimp {
    public static void main(String[] args) {
        // apeluri ale metodelor values(), name(), ordinal()
        for (Anotimp anotimp: Anotimp.values()) {
            System.out.println(anotimp.name() + " " + anotimp.ordinal());
        }

        // apel al metodei valueOf()
        Anotimp a = Anotimp.valueOf("VARA");
        //Anotimp b = Anotimp.valueOf("vara"); // IllegalArgumentException: No enum constant enums.Anotimp.vara

        // folosirea enumerarilor in switch statement
        Anotimp anotimp = Anotimp.TOAMNA;
        switch (anotimp) {
            case Anotimp.IARNA: // folosim IARNA si nu Anotimp.IARNA deoarece compilatorul stie deja ca singura posibila potrivire este valoarea IARNA a enumerarii
                System.out.println("Putem merge la ski!");
                break;
            case TOAMNA:
                System.out.println("Putem merge la scoala!");
                break;
            default:
                System.out.println("Putem sta in casa!");

        }

    }
}
