package serialization.ex1;

import java.io.FileOutputStream;
import java.io.IOException;
import java.io.ObjectOutputStream;

public class ObjectUidSerialization {

    public static void main(String[] args) {
        ObjectWithSerialVersionUID obj  = new ObjectWithSerialVersionUID("Maria", 25);
        try (ObjectOutputStream fout = new ObjectOutputStream(
                new FileOutputStream("./lab8/objectUid.ser"))) {
            fout.writeObject(obj);
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}
