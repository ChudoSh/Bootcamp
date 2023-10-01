package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.atomic.AtomicInteger;

public class Sync_Problems1 {

    private AtomicInteger cnt;
    private final Lock lock;

    public Sync_Problems1() {
        this.cnt = new AtomicInteger(0);
        this.lock = new ReentrantLock();
    }

    public void startRead() {
        // Acquire the lock to ensure that no writers are writing.
        lock.lock();

        // Increment the counter to indicate that there is one more reader.
        cnt.incrementAndGet();

        // Release the lock to allow other readers to start reading.
        lock.unlock();
    }

    public void endRead() {
        // Decrement the counter to indicate that there is one fewer reader.
        cnt.decrementAndGet();
    }

    public void startWrite() {
        // Acquire the lock to ensure that no other readers or writers are accessing the data.
        try {
            lock.lock();

            while (cnt.get() > 0) {
                Thread.currentThread().sleep(1);
            }
        } catch (InterruptedException e) {
            lock.unlock();
        }
        // Wait until there are no more readers.
    }

    public void endWrite() {
        // Release the lock to allow other readers and writers to access the data.
        lock.unlock();
    }
}
