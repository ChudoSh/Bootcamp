package il.co.ILRD.concurrency;

public class SynchornizedMethod {
    private static int counter = 0;

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
        System.out.println("SynchronizedMethod; This is the counter: " + counter);
        System.out.println(System.currentTimeMillis() - start + " milliseconds");
    }

    private static class myThread {
        Thread someThread = new Thread() {
            @Override
            public synchronized void run() {
                for (int i = 0; i < 10000000; ++i) {
                    ++counter;
                }
            }
        };

        private synchronized void startThread() {
            someThread.start();
        }
        private synchronized void joinThread() throws InterruptedException {
            someThread.join();
        }
    }

}
//reentrant lock : 9 and 12 milliseconds however not completely concurrent
