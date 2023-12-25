/*
Dev: BarSh
Rev: Daniel
Date: 30.8.23
Status: Approved
*/
package waitable_queue;


import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class CondWaitableQueue<E> {
    private static ReentrantLock lock;
    private static Condition condition;
    private final PriorityQueue<E> queue;
    private final int capacity;

    public CondWaitableQueue(int capacity) {
        this(null, capacity);
    }

    public CondWaitableQueue(Comparator<E> comparator, int capacity) {
        lock = new ReentrantLock();
        condition = lock.newCondition();
        this.queue = new PriorityQueue<>(capacity ,comparator);
        this.capacity = capacity;
    }

    public boolean enqueue(E element) {
        try {
            lock.lock();
            while (this.capacity == queue.size()){
                condition.await();
            }
            return queue.add(element);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            throw new RuntimeException(e);
        } finally {
            condition.signalAll();
            lock.unlock();
        }
    }

    public E dequeue() {
        try {
            lock.lock();
            while (queue.isEmpty()){
                condition.await();
            }
            return queue.remove();
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            throw new RuntimeException(e);
        } finally {
            condition.signalAll();
            lock.unlock();
        }
    }

    public boolean remove(E element) {
        try {
            lock.lock();
            return queue.remove(element);
        } finally {
            lock.unlock();
        }
    }

    public int size() {
        return queue.size();
    }

    public E peek() {
        return queue.peek();
    }

    public boolean isEmpty() {
        return queue.isEmpty();
    }
}
