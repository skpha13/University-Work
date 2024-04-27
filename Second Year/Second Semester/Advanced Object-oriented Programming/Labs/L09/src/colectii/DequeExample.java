package colectii;

import java.util.ArrayDeque;
import java.util.Deque;
import java.util.Iterator;

public class DequeExample {

    private final Deque<String> deque = new ArrayDeque<>();

    public static void main(String[] args) {
        DequeExample dequeExample = new DequeExample();

        dequeExample.addElement("el1");
        dequeExample.addElement("el2");
        dequeExample.addElement("el3");
        dequeExample.displayQueueUsingEnhancedFor();
        dequeExample.displayReverse();

        dequeExample.addFirst("el-first");
        dequeExample.addLast("el-last");
        dequeExample.displayQueueUsingEnhancedFor();
        //TODO: test more methods from Dequeue
    }

    public void addElement(String element) {
        deque.add(element);
    }

    public void addFirst(String element) {
        deque.addFirst(element);
    }

    public void addLast(String element) {
        deque.addLast(element);
    }


    private void displayQueueUsingEnhancedFor() {
        System.out.println("Display queue using enhanced for:");
        for (String s : deque) {
            System.out.println(s);
        }
    }
    private void displayQueueUsingIterator() {
        System.out.println("Display queue using Iterator:");
        for (Iterator<String> iterator = deque.iterator(); iterator.hasNext(); ) {
            System.out.println(iterator.next());
        }
    }

    private void displayReverse() {
        System.out.println("Display reverse queue using Iterator:");
        Iterator<String> dItr = deque.descendingIterator();
        while (dItr.hasNext()) {
            System.out.println(dItr.next());
        }
    }

}
