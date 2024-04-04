package test.marker;

import marker.exc.Bumblebee;
import marker.exc.NotTransformableException;
import marker.exc.TransformerLab;

public class TestTransformableClass {
    public static void main(String[] args) {

        Bumblebee bumblebee = new Bumblebee("Yellow");
        try {
            TransformerLab.transformObject(bumblebee);
            System.out.println("Bumblebee transformed successfully.");
        } catch (NotTransformableException e) {
            System.out.println("Error: " + e.getMessage());
        }
    }
}
