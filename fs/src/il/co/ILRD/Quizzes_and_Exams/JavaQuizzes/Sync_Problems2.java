package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Sync_Problems2 {
    private Semaphore sem;
    private final Lock lock;
    private final int MAX_READERS;

    public Sync_Problems2(int maxReaders) {
        this.sem = new Semaphore(maxReaders);
        this.MAX_READERS = maxReaders;
        this.lock = new ReentrantLock();
    }

    public void startRead() {
        try {
            lock.lock();
            sem.acquire();
            lock.unlock();
        } catch (InterruptedException e) {
            sem.release();
        }
    }

    public void endRead() {
        lock.lock();
        sem.release();

        if (sem.availablePermits() == 0) {
            lock.unlock();
        }
    }

    public void startWrite() {
        try {
            lock.lock();

            while (sem.availablePermits() < MAX_READERS) {
                lock.newCondition().await();
            }

            sem.acquire(MAX_READERS);

        } catch (InterruptedException e) {
            sem.release(MAX_READERS);
            lock.unlock();
        }
    }

    public void endWrite() {
        lock.unlock();
    }
}
