package co.il.ILRD.Concurrency.ProdCons;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

import static java.lang.Thread.sleep;


public class Barrier {
    static final int numOfThreads = 10;
    static final int barrierNum = 5;
    static final int sleepingTime = 600;
    private static final Lock lock = new ReentrantLock();
    private static Semaphore sem = new Semaphore(0);
    private static LinkedList<String> message = new LinkedList<>();
    private static final Condition condition = lock.newCondition();

    public static void main(String[] args) throws InterruptedException {
        Thread proList = new myProducer();
        List<Thread> conList = new ArrayList<>();

        for (int i = 0; i < numOfThreads; ++i) {
            conList.add(new Barrier.myConsumer());
        }

        proList.start();
        conList.forEach(Thread::start);

        sleep(sleepingTime);

        proList.interrupt();
        conList.forEach(Thread::interrupt);

        proList.join();
        for (int i = 0; i < numOfThreads; ++i) {
            conList.get(i).join();
        }
    }

    private static class myProducer extends Thread {
        static int i = 0;

        @Override
        public void run() {
            while (barrierNum != sem.availablePermits()) {
                try {
                    sem.acquire();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
                message.add("This is for consumer " + i);
                ++i;
            }
            lock.lock();
            condition.signalAll();
            lock.unlock();
        }
    }

    private static class myConsumer extends Thread {
         static int i = 0;

        @Override
        public void run() {
            if (barrierNum != sem.availablePermits()) {
                lock.lock();
                sem.release();
                try {
                    condition.await();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                }
                System.out.println(message.remove() + ":Consumer " + i + " received");
                ++i;
                lock.unlock();
            }
        }
    }
}

