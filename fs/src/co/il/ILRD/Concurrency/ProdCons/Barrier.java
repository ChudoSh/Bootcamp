package co.il.ILRD.Concurrency.ProdCons;

import co.il.ILRD.Utils.Enums;
import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import static java.lang.Thread.sleep;


public class Barrier {
    private static final Lock lock = new ReentrantLock();
    private static Semaphore sem = new Semaphore(0);
    private static String message = null;
    private static final Condition condition = lock.newCondition();

    public static void main(String[] args) throws InterruptedException {
        Thread producer = new myProducer();
        List<Thread> conList = new ArrayList<>();

        for (int i = 0; i < Enums.MagicNumber.NUM_OF_THREADS.getValue(); ++i) {
            conList.add(new Barrier.myConsumer());
        }

        producer.start();
        conList.forEach(Thread::start);

        sleep(Enums.MagicNumber.SLEEP.getValue());

        producer.interrupt();
        conList.forEach(Thread::interrupt);

        producer.join();
        for (int i = 0; i < Enums.MagicNumber.SLEEP.getValue(); ++i) {
            conList.get(i).join();
        }
    }

    private static class myProducer extends Thread {
        static int i = 0;

        @Override
        public void run() {
            while (!Thread.currentThread().isInterrupted()){
                while (Enums.MagicNumber.SLEEP.getValue() > i) {
                    try {
                        sem.acquire();
                    } catch (InterruptedException e) {
                        Thread.currentThread().interrupt();
                    }
                    message = "This is for consumer " + i;
                    ++i;
                }
                lock.lock();
                condition.signalAll();
                lock.unlock();
            }
        }
    }

    private static class myConsumer extends Thread {
         static int i = 0;

        @Override
        public void run() {
            while (!Thread.currentThread().isInterrupted()) {
                lock.lock();
                sem.release();
                try {
                    condition.await();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
                lock.unlock();
                System.out.println(message + ":Consumer " + i + " received");
                ++i;
            }
        }
    }
}

