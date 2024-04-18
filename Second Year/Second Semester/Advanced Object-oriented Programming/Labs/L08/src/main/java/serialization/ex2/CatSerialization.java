package serialization.ex2;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;

public class CatSerialization {

    public static void main(String[] args) {
        Cat cat = new Cat();
        try (ObjectOutputStream fout = new ObjectOutputStream(
                new FileOutputStream("./lab8/cat.ser"))) {
            fout.writeObject(cat);
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}
