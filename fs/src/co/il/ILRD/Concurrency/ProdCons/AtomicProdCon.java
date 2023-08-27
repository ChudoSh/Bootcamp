package co.il.ILRD.Concurrency.ProdCons;

import java.util.concurrent.atomic.AtomicBoolean;

import static java.lang.Thread.sleep;

public class AtomicProdCon {
    private static AtomicBoolean atomicLock = new AtomicBoolean(true);

    public static void main(String[] args) throws InterruptedException {
        Thread producer = new myProducer();
        Thread consumer = new myConsumer();

        producer.start();
        consumer.start();

        sleep(500);

        producer.interrupt();
        consumer.interrupt();

        producer.join();
        consumer.join();
    }

    private static class myProducer extends Thread {
        @Override
        public void run() {
            while (!this.isInterrupted()) {
                while (atomicLock.get()) {
                    System.out.println("Ping");
                    atomicLock.set(false);
                }
            }
        }
    }

    private static class myConsumer extends Thread {
        @Override
        public void run() {
            while (!this.isInterrupted()) {
                while (!atomicLock.get()) {
                    System.out.println("Pong");
                    atomicLock.set(true);
                }
            }
        }
    }
}