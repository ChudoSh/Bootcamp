package il.co.ILRD.Concurrency.ProdCons;

import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

import static java.lang.Thread.sleep;

public class MultiProMultiConNoSem {
    static int num = 10;
    private static Object lock = new Object();
    private static LinkedList<String> list = new LinkedList<>();

    public static void main(String[] args) throws InterruptedException {
        List<Thread> proList = new ArrayList<>();
        List<Thread> conList = new ArrayList<>();

        for (int i = 0; i < num; ++i) {
            proList.add(new myProducer());
            conList.add(new myConsumer());
        }

        proList.forEach(Thread::start);
        conList.forEach(Thread::start);

        proList.forEach(Thread::interrupt);
        conList.forEach(Thread::interrupt);

        for (int i = 0; i < num; ++i) {
            proList.get(i).join();
            conList.get(i).join();
        }
    }

    private static class myProducer extends Thread {
        @Override
        public void run() {
            synchronized (lock) {
                list.add("Ping");
                list.add("Pong");
            }
        }
    }

    private static class myConsumer extends Thread {
        int i = 0;

        @Override
        public void run() {
            synchronized (lock) {
                if(!list.isEmpty()) {
                    System.out.println(list.remove(++i));
                }
            }
        }
    }
}

