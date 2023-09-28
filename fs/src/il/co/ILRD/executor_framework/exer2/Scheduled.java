/*
dev: barsh
rev: maria
status: approved
date 3.9.23
*/
package il.co.ILRD.executor_framework.exer2;

import java.util.concurrent.*;

public class Scheduled {
    public static void main(String args[]) throws InterruptedException {
        CountDownLatch lock = new CountDownLatch(3);

        ScheduledExecutorService executor = Executors.newScheduledThreadPool(5);
        ScheduledFuture<?> future = executor.scheduleAtFixedRate(() -> {
            System.out.println("Scheduled executor");
            lock.countDown();
        }, 500, 100, TimeUnit.MILLISECONDS);

        lock.await(1000, TimeUnit.MILLISECONDS);
        executor.shutdown();
    }
}
