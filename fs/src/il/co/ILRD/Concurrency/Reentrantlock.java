package il.co.ILRD.Concurrency;

import java.util.concurrent.locks.ReentrantLock;

public class Reentrantlock {
    private static int nonAtomicCounter = 0;

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
        System.out.println("SynchronizedMethod; This is the counter: " + nonAtomicCounter );
        System.out.println(System.currentTimeMillis() - start + " milliseconds");
    }

    private static class myThread {
        Thread someThread = new Thread() {
            @Override
            public void run() {
                final ReentrantLock lock = new ReentrantLock();
                lock.lock();
                try {
                    for (int i = 0; i < 10000000; ++i) {
                        ++nonAtomicCounter;
                    }
                } finally {
                    lock.unlock();
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
