package singleton;

public class Singleton {
    private static Singleton instance;

    private Singleton() {} // private pentru a evita instantierea

    public static Singleton getInstance() {
        if (instance == null) {
            instance = new Singleton();
        }
        return instance;
    }
}
