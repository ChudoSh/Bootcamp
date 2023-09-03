/*
dev: barsh
rev: maria
status:
date 3.9.23
*/
package co.il.ILRD.ExecutorFramework.Exer1;


import java.util.concurrent.ExecutionException;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;

public class Exer1 {
    public static void main(String args[]) throws InterruptedException {
        int beforeReturn = 2000;
        int busyWait = 200;
        ExecutorService secretService = Executors.newSingleThreadExecutor();
        Future<String> future = secretService.submit(() ->
        {
            Thread.sleep(beforeReturn);
            return "Damn Bar, back at it again to the future";
        });

        while (!future.isDone()) {
            System.out.println("Returning from the past");
            Thread.sleep(busyWait);
        }

        System.out.println("The Dolorian has arrived");
        try {
            String result = future.get();
            System.out.println(result);
        } catch (InterruptedException | ExecutionException e){
            e.printStackTrace();
        } finally {
            secretService.shutdown();
        }

    }
}
