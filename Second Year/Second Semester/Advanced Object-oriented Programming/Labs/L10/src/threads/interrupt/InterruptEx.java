package threads.interrupt;

public class InterruptEx extends Thread {

    @Override
    public void run() {

        for (int i = 0; i < 5; i++) {
            System.out.println("[" + Thread.currentThread().getName() + "] Processing message " + i);
            if(Thread.interrupted()) {
                System.out.println("[" + Thread.currentThread().getName()+ " was interrupted by someone calling interrupt()]");
                System.out.println("[Cancelling thread " + Thread.currentThread().getName() + "]");
                break;
            }
        }
    }
}