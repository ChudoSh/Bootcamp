package il.co.ILRD.concurrency;

public class SynchronizedBlock {
    private static Integer counter = 0;

    public static void main(String[] args) {
        myThread first = new myThread();
        myThread second = new myThread();

        long start = System.currentTimeMillis();
        first.startThread();
        second.startThread();
        try {
            second.joinThread();
            first.joinThread();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
        System.out.println("SynchronizedMethod; This is the counter: " + counter );
        System.out.println(System.currentTimeMillis() - start + " milliseconds");

    }

    private static class myThread {
        Thread someThread = new Thread() {
            @Override
            public void run() {
                synchronized (this) {
                    for (int i = 0; i < 10000000; ++i) {
                        ++counter;
                    }
                }
            }
        };

        private void startThread() {
            someThread.start();
        }

        private void joinThread() throws InterruptedException {
            someThread.join();
        }
    }
}