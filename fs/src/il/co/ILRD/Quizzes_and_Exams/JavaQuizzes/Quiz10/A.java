package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes.Quiz10;

public class A implements Runnable {
    public void run() {
        System.out.println(Thread.currentThread().getName());
    }
}

class B implements Runnable {
    public void run() {
        new A().run();
        new Thread(new A(), "name_thread2").run();
        new Thread(new A(), "name_thread3").start();
    }
}

class Main {
    public static void main(String[] args) {
        new Thread(new B(), "name_thread1").start();
    }
}