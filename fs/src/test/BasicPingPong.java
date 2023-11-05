package test;

import java.util.concurrent.Semaphore;
import java.util.concurrent.TimeUnit;

public class BasicPingPong {
    private final TimeUnit unit = TimeUnit.SECONDS;
    private final long end = System.currentTimeMillis() + unit.toMillis(1);
    private final Semaphore enterSem = new Semaphore(1);
    private final Semaphore exitSem = new Semaphore(0);

    public void ping() {
        while (!Thread.currentThread().isInterrupted()) {
            while (System.currentTimeMillis() <= end) {
                try {
                    this.enterSem.acquire();
                    System.out.println("ping");
                    this.exitSem.release();
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }

    public void pong() {
        while (!Thread.currentThread().isInterrupted()) {
            while (System.currentTimeMillis() <= end) {
                try {
                    this.exitSem.acquire();
                    System.out.println("pong");
                    this.enterSem.release();
                } catch (InterruptedException e) {
                    throw new RuntimeException(e);
                }
            }
        }
    }

    public void run() {
        Thread pinging = new Thread(this::ping);
        Thread ponging = new Thread(this::pong);

        pinging.start();
        ponging.start();

        try {
            pinging.join();
            ponging.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        new BasicPingPong().run();
    }
}
