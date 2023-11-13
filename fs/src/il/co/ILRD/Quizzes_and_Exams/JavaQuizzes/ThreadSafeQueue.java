package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.Semaphore;

public class ThreadSafeQueue<T>{
    private final int capacity;
    private Queue<T> q;
    private Semaphore enter;
    private Semaphore exit;

    public ThreadSafeQueue(int capacity, int numOfThreads) {
        this.capacity = capacity;
        this.q = new LinkedList<>();
        this.enter = new Semaphore(numOfThreads);
        this.exit = new Semaphore(0);
    }

    public void enqueque(T data){
        try {
            this.enter.acquire();
            if (this.q.size() < this.capacity){
                this.q.add(data);
            }
            this.exit.release();
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }

    }

    public T dequeque(){
        try {
            T toReturn = null;

            this.exit.acquire();
            if (!this.q.isEmpty()){
                toReturn = this.q.poll();
            }
            this.enter.release();

            return toReturn;
        } catch (InterruptedException e) {
            throw new RuntimeException(e);
        }
    }

    public static void main(String[] args) {

    }
}

