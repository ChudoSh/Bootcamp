/*
Dev: BarSh
Rev: Daniel
Date: 30.8.23
Status: Approved
*/

package main.java.waitable_queue;

import java.util.Comparator;
import java.util.PriorityQueue;
import java.util.concurrent.Semaphore;

public class SemWaitableQueue<E> {
    private final Semaphore semaphore;
    private final Object lock;
    private PriorityQueue<E> queue;

    public SemWaitableQueue(int capacity) {
        this(null, capacity);
    }

    public SemWaitableQueue(Comparator<E> comparator, int capacity) {
        assert 0 < capacity;

        this.semaphore = new Semaphore(0);
        this.queue = new PriorityQueue<>(capacity, comparator);
        this.lock = new Object();
    }

    public boolean enqueue(E element) {
        semaphore.release();
        synchronized (this.lock) {
            return queue.add(element);
        }
    }

    public E dequeue() {
        try {
            semaphore.acquire();
            synchronized (this.lock) {
                return queue.poll();
            }
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            throw new RuntimeException(e);
        }
    }

    public boolean remove(E element) {
        boolean result;
        synchronized (this.lock) {
            result = queue.remove(element);
        }
        try {
            if (result) {
                semaphore.acquire();
            }
            return result;
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            throw new RuntimeException();
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
