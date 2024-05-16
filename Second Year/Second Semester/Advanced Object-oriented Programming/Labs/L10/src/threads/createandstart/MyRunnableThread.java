package threads.createandstart;

public class MyRunnableThread implements Runnable {
    @Override
    public void run() {
        System.out.println("Hello from MyRunnableThread!");
    }
}
