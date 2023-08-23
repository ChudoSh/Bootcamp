package co.il.ILRD.Concurrency;

import com.sun.org.apache.xerces.internal.util.SynchronizedSymbolTable;
import org.junit.jupiter.api.Test;

import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.ReentrantLock;

public class Exer2 {
    private static int nonAtomicCounter = 0;
    private static AtomicInteger atomiCounter = new AtomicInteger(0);

    public static void main(String[] args) {
        myThread first = new myThread();
        myThread second = new myThread();

        first.startThread();
        second.startThread();
    }

    private static class myThread {
        Thread someThread = new Thread() {
            @Override
            public void run() {
                final ReentrantLock lock = new ReentrantLock();
                lock.lock();
                try {
                    long start = System.currentTimeMillis();
                    for (int i = 0; i < 10000000; ++i) {
                        ++nonAtomicCounter;
                    }
                    System.out.println("This is the counter: " + nonAtomicCounter);
                    System.out.println(System.currentTimeMillis() - start + " ");
                } finally {
                    lock.unlock();
                }
            }
        };

        private void startThread() {
            someThread.start();
        }
    }

}
