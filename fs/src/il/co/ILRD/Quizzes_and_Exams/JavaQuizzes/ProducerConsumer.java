package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class ProducerConsumer {
    private final Semaphore proSem;
    private final Semaphore conSem;
    private final ReentrantLock lock;
    private final Condition con;
    private final int numOfProducers;
    private final AtomicInteger atomic;

    public ProducerConsumer(int numOfProducers) {
        this.proSem = new Semaphore(numOfProducers);
        this.conSem = new Semaphore(0);
        this.numOfProducers = numOfProducers;
        this.lock = new ReentrantLock();
        this.con = lock.newCondition();
        this.atomic = new AtomicInteger();
    }

    public void producer() {
        try {
            while (!Thread.currentThread().isInterrupted()) {
                while (0 != this.proSem.availablePermits()) {
                    this.lock.lock();
                    this.proSem.acquire();
                    this.conSem.release();

                    System.out.println(Thread.currentThread() + " this is producer " + this.atomic.incrementAndGet());

                    if (this.lock.isLocked()) {
                        System.out.println("locked");
                    } else {
                        System.out.println("not Locked");
                    }

                    while(this.numOfProducers != this.conSem.availablePermits()){
                        this.con.await();
                    }

                    this.lock.unlock();
                    System.out.println(Thread.currentThread() + " im here");
                }

                System.out.println("after a while");
            }
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

    public void consumer() {
        while (!Thread.currentThread().isInterrupted()) {
            while (this.numOfProducers == this.conSem.availablePermits()) {
                this.lock.lock();
                this.atomic.set(0);

                System.out.println(Thread.currentThread() + " this is consumer " + this.atomic.get());

                try {
                    this.conSem.acquire(this.numOfProducers);
                    this.proSem.release(this.numOfProducers);
                    System.out.println("this is consumer sem: " + this.conSem.availablePermits() + " this is producer sem: " + this.proSem.availablePermits());
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }

                this.con.signalAll();
                this.lock.unlock();
            }
        }
    }

    public static void main(String[] args) {
        int numProducers = 10;
        ProducerConsumer pc = new ProducerConsumer(numProducers);
        Thread consumer = new Thread(pc::consumer);
        List<Thread> producers = new ArrayList<>();

        for (int i = 0; i < numProducers; ++i) {
            producers.add(new Thread(pc::producer));
        }

        consumer.start();
        for (int i = 0; i < numProducers; ++i) {
            producers.get(i).start();
        }

        try {
            consumer.join();
            for (Thread thread : producers) {
                thread.join();
            }
        } catch (InterruptedException e) {
            throw new RuntimeException();
        }
    }
}
