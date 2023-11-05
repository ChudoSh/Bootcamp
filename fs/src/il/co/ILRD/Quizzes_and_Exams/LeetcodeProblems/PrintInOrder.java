package il.co.ILRD.Quizzes_and_Exams.LeetcodeProblems;

import il.co.ILRD.concurrency.Reentrantlock;

import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class PrintInOrder {
    private final Lock lockA = new ReentrantLock();
    private final Lock lockB = new ReentrantLock();
    private final Lock lockC = new ReentrantLock();

    public PrintInOrder() {
    }

    public void first() throws InterruptedException {
        this.lockA.lock();
        this.lockB.lock();
        this.lockC.lock();
        System.out.println("first");
        this.lockA.unlock();
        this.lockB.unlock();
        this.lockC.unlock();
    }

    public void second() {
        this.lockA.lock();
        this.lockB.lock();
        this.lockC.lock();
        System.out.println("second");
        this.lockA.unlock();
        this.lockB.unlock();
        this.lockC.unlock();
    }

    public void third() {
        this.lockA.lock();
        this.lockB.lock();
        this.lockC.lock();
        System.out.println("third");
        this.lockA.unlock();
        this.lockB.unlock();
        this.lockC.unlock();
    }
}

