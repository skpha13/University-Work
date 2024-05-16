package threads.synchronize;

public class TestCounter {

    public static void main(String[] args) {
        SynchronizedCounter counter = new SynchronizedCounter();
        Thread thread1 = new Thread(counter);
        Thread thread2 = new Thread(counter);
        thread1.start();
        thread2.start();
    }
}
