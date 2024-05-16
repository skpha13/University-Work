package threads.deadlock;

public class Deadlock {
    public static final String resource1 = "r1";
    public static final String resource2 = "r2";

    public static void main(String[] args) {
        t1.start();
        t2.start();
    }

    private static Thread t1 = new Thread() {
        public void run() {
            synchronized (resource1) {
                System.out.println("Thread 1: Holding lock 1...");
                try {
                    Thread.sleep(10);
                } catch (InterruptedException e) {
                }
                System.out.println("Thread 1: Waiting for lock 2...");
                synchronized (resource2) {
                    System.out.println("Thread 1: Holding lock 1 & 2...");
                }
            }
        }
    };

    private static Thread t2 = new Thread() {
        public void run() {
            synchronized (resource2) {
                System.out.println("Thread 2: Holding lock 2...");
                try {
                    Thread.sleep(10);
                } catch (InterruptedException e) {
                }
                System.out.println("Thread 2: Waiting for lock 1...");
                synchronized (resource1) {
                    System.out.println("Thread 2: Holding lock 1 & 2...");
                }
            }
        }
    };

    /*Solution: use the same order in both threads:
    synchronized (resource1)
    synchronized (resource2)
    .......................
    synchronized (resource1)
    synchronized (resource2)*/
}
