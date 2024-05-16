package threads.createandstart;

public class MyThreadTest {

    public static void main(String[] args) {
        System.out.println("Begin main");
        MyThread t = new MyThread();
        t.start();
        System.out.println("End main");
    }
}
