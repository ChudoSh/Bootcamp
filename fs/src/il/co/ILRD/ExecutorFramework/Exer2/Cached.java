/*
dev: barsh
rev: maria
status: approved
date 3.9.23
*/
package il.co.ILRD.ExecutorFramework.Exer2;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;


import java.util.concurrent.atomic.AtomicInteger;


public class Cached {
    public static void main(String args[]) throws InterruptedException {
        AtomicInteger result = new AtomicInteger();
        int size = 3;
        ExecutorService secretService = Executors.newCachedThreadPool();
        Future<Integer> future;
        secretService.submit(result::incrementAndGet);
        secretService.submit(result::incrementAndGet);
        future = secretService.submit(result::incrementAndGet);

        try {
            System.out.println("Thread incremented to tha value of " + future.get());
        } catch (InterruptedException | ExecutionException e) {
            throw new RuntimeException(e);
        } finally {
            secretService.shutdown();
        }
    }
}
