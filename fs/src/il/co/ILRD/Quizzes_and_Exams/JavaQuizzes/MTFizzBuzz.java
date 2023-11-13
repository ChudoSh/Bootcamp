package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class MTFizzBuzz {
    private Lock lock;
    private AtomicInteger counter;

    public MTFizzBuzz() {
        this.lock = new ReentrantLock();
        this.counter = new AtomicInteger(1);
    }

    public void fizz() {
        while (!Thread.currentThread().isInterrupted()) {
            this.lock.lock();
            if (this.counter.get() % 3 == 0 && this.counter.get() % 5 != 0) {
                System.out.println("fizz");
                this.counter.incrementAndGet();
            }
            this.lock.unlock();
        }
    }

    public void buzz() {
        while (!Thread.currentThread().isInterrupted()) {
            this.lock.lock();
            if (this.counter.get() % 3 != 0 && this.counter.get() % 5 == 0) {
                System.out.println("buzz");
                this.counter.incrementAndGet();
            }
            this.lock.unlock();
        }
    }

    public void fizzbuzz() {
        while (!Thread.currentThread().isInterrupted()) {
            this.lock.lock();
            if (this.counter.get() % 3 == 0 && this.counter.get() % 5 == 0) {
                System.out.println("fizzbuzz");
                this.counter.incrementAndGet();
            }
            this.lock.unlock();
        }
    }

    public void number() {
        while (!Thread.currentThread().isInterrupted()) {
            this.lock.lock();
            if (this.counter.get() % 3 != 0 && this.counter.get() % 5 != 0) {
                System.out.println(this.counter.get());
                this.counter.incrementAndGet();
            }
            this.lock.unlock();
        }
    }

    public static void main(String[] args) {
        List<Thread> threads = new ArrayList<>();
        MTFizzBuzz fizzBuzz = new MTFizzBuzz();

        threads.add(new Thread(fizzBuzz::fizz));
        threads.add(new Thread(fizzBuzz::buzz));
        threads.add(new Thread(fizzBuzz::fizzbuzz));
        threads.add(new Thread(fizzBuzz::number));

        for (Thread t : threads) {
            t.start();
        }

        try {
            for (Thread t : threads) {
                t.join();
            }
        } catch (InterruptedException e){
            e.printStackTrace();
        }
    }
}
