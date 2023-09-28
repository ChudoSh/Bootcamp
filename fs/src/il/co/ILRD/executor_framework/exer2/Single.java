/*
dev: barsh
rev: maria
status: approved
date 3.9.23
*/
package il.co.ILRD.executor_framework.exer2;

import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class Single {
    public static void main(String[] args) {
        int result = 0;
        ExecutorService secretService = Executors.newSingleThreadExecutor();
        Future<Integer> future = secretService.submit(() -> {
            int sum = 0;

            for (int i = 0; i < 20; i++) {
                sum += i;
            }

            return sum;
        });

        try {
             result = future.get();
        } catch (InterruptedException | ExecutionException e) {
            throw new RuntimeException(e);
        } finally {
            secretService.shutdown();
        }

        System.out.println("Thread incremented to tha value of " + result);

    }

}
