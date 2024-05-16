package threads.join;

public class JoiningTest {
    public static void main (String[] args) {
        System.out.println("Begin main");
        // creating some threads
        ThreadJoining t1 = new ThreadJoining();
        t1.setName("one");
        ThreadJoining t2 = new ThreadJoining();
        t2.setName("two");
        ThreadJoining t3 = new ThreadJoining();
        t3.setName("three");

        // thread t1 starts
        t1.start();

        try {
            System.out.println("Current Thread: " + Thread.currentThread().getName());
            //suspenda executarea thread-ului parinte (main) pana la terminarea thread-ului curent (t1)
            t1.join();
        } catch(Exception ex) {
            System.out.println("Exception has been caught" + ex);
        }

        // t2 starts
        t2.start();

        // starts t3 after when thread t2 has died.
        try {
            System.out.println("Current Thread: " + Thread.currentThread().getName());
            //suspenda executarea thread-ului parinte (main) pana la terminarea thread-ului curent (t2)
            t2.join();
        } catch(Exception ex) {
            System.out.println("Exception has been caught" + ex);
        }

        t3.start();
        System.out.println("End main");
    }
}
