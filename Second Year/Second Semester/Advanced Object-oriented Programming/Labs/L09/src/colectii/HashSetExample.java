package colectii;

import java.util.HashSet;
import java.util.Iterator;

public class HashSetExample {

    private final HashSet<String> hashSet = new HashSet<>();

    public static void main(String[] args) {

        HashSetExample hashSetExample = new HashSetExample();

        hashSetExample.addElement("el1");
        hashSetExample.addElement("el2");
        hashSetExample.addElement("el3");
        hashSetExample.displayElementsUsingEnhancedFor();
        hashSetExample.displayElementsUsingIterator();
        System.out.println(hashSetExample.containsElement("el2"));
        hashSetExample.removeElement("el2");
        System.out.println(hashSetExample.containsElement("el2"));
        hashSetExample.displayElementsUsingEnhancedFor();
        hashSetExample.convertHashSetToArray();
    }

    private void addElement(String element) {
        hashSet.add(element);
    }

    private void removeElement(String element) {
        hashSet.remove(element);
    }

    private boolean containsElement(String element) {
        return hashSet.contains(element);
    }

    private void displayElementsUsingIterator() {
        System.out.println("Display set using Iterator:");
        Iterator<String> iterator = hashSet.iterator();

        while (iterator.hasNext()) {
            String value = iterator.next();

            System.out.println("Value: " + value);
        }
    }

    private void displayElementsUsingEnhancedFor() {
        System.out.println("Display set using enhanced for:");
        for (String value : hashSet) {
            System.out.println("Value: " + value);
        }
    }

    private String[] convertHashSetToArray() {
        String[] newArray = new String[hashSet.size()];
        return hashSet.toArray(newArray);
    }
}
