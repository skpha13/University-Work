package threads.interrupt;

public class InterruptingThread {
    public static void main(String[] args)  {
        System.out.println(Thread.currentThread().getName() + " thread started");
        InterruptEx threadEx = new InterruptEx();
        threadEx.setName("threadEx");
        threadEx.start();
        threadEx.interrupt(); // calling interrupt() method
        System.out.println(Thread.currentThread().getName() + " thread finished");
    }
}
