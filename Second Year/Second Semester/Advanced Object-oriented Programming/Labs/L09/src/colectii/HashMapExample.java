package colectii;

import java.util.HashMap;
import java.util.Iterator;

public class HashMapExample {

    private final HashMap<Integer, String> namesMap = new HashMap<>();

    public static void main(String[] args) {
        HashMapExample hashMapExample = new HashMapExample();

        hashMapExample.addElement(1, "el1");
        hashMapExample.addElement(2, "el2");
        hashMapExample.addElement(5, "el3");
        hashMapExample.displayMapUsingEnhancedFor();
        System.out.println("The value for key 5 is: " + hashMapExample.getElementByKey(5));
        hashMapExample.removeElementByKey(5);
        hashMapExample.displayMapUsingIterator();
    }

    private void addElement(Integer key, String value) {
        namesMap.put(key, value);
    }

    private String getElementByKey(Integer key) {
        return namesMap.get(key);
    }

    private String removeElementByKey(Integer key) {
        return namesMap.remove(key);
    }

    private void displayMapUsingEnhancedFor() {
        System.out.println("Display map using enhanced for:");
        for (Integer key : namesMap.keySet()) {
            String value = namesMap.get(key);

            System.out.println("The key is : " + key + ", and value is : " + value);
        }
    }

    private void displayMapUsingIterator() {
        System.out.println("Display map using Iterator:");
        Iterator<Integer> iterator = namesMap.keySet().iterator();

        while (iterator.hasNext()) {
            Integer key = iterator.next();
            String value = namesMap.get(key);

            System.out.println("The key is : " + key + ", and value is : " + value);
        }
    }
}
