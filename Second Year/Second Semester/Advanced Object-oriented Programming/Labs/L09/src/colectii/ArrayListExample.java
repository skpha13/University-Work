package colectii;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

public class ArrayListExample {

    private final List<String> names = new ArrayList<>();
    public static void main(String[] args) {
        ArrayListExample arrayListExamples = new ArrayListExample();

        arrayListExamples.addNameElement("John");
        arrayListExamples.addNameElement("Mark");
        arrayListExamples.addNameElement("Tom");
        arrayListExamples.displayListUsingSimpleFor();
        arrayListExamples.removeNameElement(2);
        arrayListExamples.displayListUsingEnhancedFor();
        arrayListExamples.updateNameElement(1, "Ingrid");
        arrayListExamples.displayListUsingIterator();
        //TODO: test more methods from List
    }

    private void addNameElement(String name) {
        // add elements to the list
        names.add(name);
    }

    private void updateNameElement(int index, String name) {
        // update element at given index with given value
        names.set(index, name);
    }

    private void removeNameElement(int index) {
        // remove element with given index from the list
        names.remove(index);
    }

    private void displayListUsingSimpleFor() {
        System.out.println("Display list using simple for:");
        for (int i = 0; i < names.size(); i++) {
            System.out.println(names.get(i));
        }
    }

    private void displayListUsingEnhancedFor() {
        System.out.println("Display list using enhanced for:");
        for (String name : names) {
            System.out.println(name);
        }
    }

    private void displayListUsingIterator() {
        System.out.println("Display list using Iterator:");
        Iterator<String> iterator = names.iterator();

        while (iterator.hasNext()) {
            System.out.println(iterator.next());
        }
    }
}
