package threads.createandstart;

public class MyRunnableThreadTest {
    public static void main(String[] args) {
        System.out.println("Begin main");
        MyRunnableThread runnableThread = new MyRunnableThread();
        new Thread(runnableThread).start();
        System.out.println("End main!");
    }
}
