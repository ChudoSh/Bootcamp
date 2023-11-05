package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReentrantLock;

public class ThreadSafeQueue<T>{
    private final int capacity;
    private Queue<T> q;
    private Semaphore enter;
    private Semaphore exit;
    private Condition cond;

    public ThreadSafeQueue(int capacity, int numOfThreads) {
        this.capacity = capacity;
        this.q = new LinkedList<>();
        this.enter = new Semaphore(numOfThreads);
        this.exit = new Semaphore(0);
        this.cond = new ReentrantLock().newCondition();
    }

    public void enqueque(T data){
        try {
            this.enter.acquire();
            if (this.capacity == this.q.size()){
                this.cond.await();
            }

            this.q.add(data);
            this.exit.release();
            this.cond.signalAll();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

    }

    public T dequeque(){
        try {
            this.exit.acquire();
            if (this.q.isEmpty()){
                this.cond.await();
            }

            T toReturn = this.q.poll();
            this.enter.release();
            this.cond.signalAll();

            return toReturn;
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {

    }
}

