package marker.exc;

public class TransformerLab implements Transformable {
    public static void transformObject(Object obj) throws NotTransformableException {
        if (obj instanceof Transformable) {
            // Implementați aici logica de transformare
            System.out.println("Transforming object...");
        } else {
            throw new NotTransformableException("Object is not transformable.");
        }
    }
}
