package threads.join;

class ThreadJoining extends Thread {
    @Override
    public void run() {
        for (int i = 0; i < 2; i++) {
            try {
                Thread.sleep(1000);
                System.out.println("Current Thread: " + Thread.currentThread().getName());
            } catch (Exception ex) {
                System.out.println("Exception has been caught" + ex);
            }
            System.out.println("iteration: " + i);
        }
    }
}