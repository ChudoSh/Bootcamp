package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class ProducerConsumer {
    private final Semaphore sem;
    private final ReentrantLock lock;
    private final Condition con;
    private final int numOfProducers;
    private AtomicInteger atomic;

    public ProducerConsumer(int numOfProducers) {
        this.sem = new Semaphore(numOfProducers);
        this.numOfProducers = numOfProducers;
        this.lock = new ReentrantLock();
        this.con = lock.newCondition();
        this.atomic = new AtomicInteger();
    }

    public void producer() {
        try {
            while (!Thread.currentThread().isInterrupted()) {
                while (this.numOfProducers != this.sem.availablePermits()) {
                    this.lock.lock();
                    this.sem.acquire();

                    System.out.println(this.atomic.incrementAndGet());

                    while (0 == sem.availablePermits()) {
                        con.await();
                    }

                    this.lock.unlock();
                }
            }
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

    public void consumer() {
        while (!Thread.currentThread().isInterrupted()) {
            while (this.numOfProducers == this.sem.availablePermits()) {
                this.lock.lock();

                System.out.println(this.atomic.getAndAdd(-10));

                this.sem.release(this.numOfProducers);
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
