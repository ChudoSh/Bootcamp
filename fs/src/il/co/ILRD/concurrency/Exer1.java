package il.co.ILRD.concurrency;

public class Exer1 {
    public static void main(String[] args) {
        MyThread myThread = new MyThread();
        Thread someThread = new Thread(() -> System.out.println("System thread"));

        myThread.start();
        someThread.start();

    }

    public static class MyThread extends Thread {

        @Override
        public void run(){
            System.out.println("MyThread running");
        }
    }
}
