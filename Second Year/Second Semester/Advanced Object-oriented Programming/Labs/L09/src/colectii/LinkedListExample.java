package colectii;

import java.util.Arrays;
import java.util.Collections;
import java.util.LinkedList;
import java.util.ListIterator;

public class LinkedListExample {

    private final LinkedList<String> linkedList = new LinkedList<>();

    public static void main(String[] args) {
        LinkedListExample linkedListExample = new LinkedListExample();
        linkedListExample.addElement("lk1");
        linkedListExample.addElement("lk2");
        linkedListExample.addElement("lk3");
        linkedListExample.addElement("lk4");
        linkedListExample.addElement("lk5");
        System.out.println("Element at index 1: " + linkedListExample.getElementAtIndex(1));
        linkedListExample.reverseOrder();
        linkedListExample.displayLinkedListUsingIterator();
        linkedListExample.removeElementBy(2);
        linkedListExample.displayLinkedLisUsingEnhancedFor();
        linkedListExample.removeElementBy("lk2");
        linkedListExample.displayLinkedLisUsingEnhancedFor();
        System.out.println("First element: " + linkedListExample.getFirst());
        System.out.println("Last element: " + linkedListExample.getLast());

    }

    private void addElement(String element) {
        //Add elements
        linkedList.add(element);
    }

    private void removeElementBy(int index) {
        //Remove element by index
        System.out.println("Remove element by index "+ index);
        linkedList.remove(index);
    }

    private void removeElementBy(String value) {
        System.out.println("Remove element by value "+ value);
        //Remove element by value
        linkedList.remove(value);
    }

    private String getFirst() {
        // Return first element
        return linkedList.getFirst();
    }

    private String getLast() {
        // Return last element
        return linkedList.getLast();
    }

    private String getElementAtIndex(int index) {
        // Return element at index
        return linkedList.get(index);
    }

    private void displayLinkedListUsingIterator() {
        System.out.println("Display linkedList using Iterator:");
        ListIterator<String> iterator = linkedList.listIterator();
        while (iterator.hasNext()) {
            System.out.println(iterator.next());
        }
    }

    private void displayLinkedLisUsingEnhancedFor() {
        System.out.println("Display linkedList using enhanced for:");
        for (String s : linkedList) {
            System.out.println(s);
        }
    }

    private String[] getLinkedListAsArray() {
        String[] array = new String[linkedList.size()];
        return linkedList.toArray(array);
    }

    private LinkedList<String> getArrayAsLinkedList(String[] array) {
        LinkedList<String> linkedListNew = new LinkedList<>(Arrays.asList(array));
        return linkedListNew;
    }

    private void sort() {
        Collections.sort(linkedList);
    }

    private void reverseOrder() {
        Collections.sort(linkedList, Collections.reverseOrder());
    }
}
