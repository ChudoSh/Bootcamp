package il.co.ILRD.concurrency.prodecers_consumers;

import java.util.concurrent.Semaphore;

import static java.lang.Thread.sleep;

public class TwoSem {
    public static void main(String[] args) throws InterruptedException {
        Semaphore enter = new Semaphore(1);
        Semaphore exit = new Semaphore(1);

        Thread producer = new Thread(() -> {
            while (!Thread.currentThread().isInterrupted()){
                try {
                    enter.acquire();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    throw new RuntimeException(e);
                }
                System.out.println("Ping");
                exit.release();
            }

        });
        Thread consumer = new Thread(() -> {
            while (!Thread.currentThread().isInterrupted()){
                try {
                    exit.acquire();
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    throw new RuntimeException(e);
                }
                System.out.println("Pong");
                enter.release();
            }

        });

        producer.start();
        consumer.start();

        sleep(500);

        producer.interrupt();
        consumer.interrupt();

        producer.join();
        consumer.join();
    }
}
