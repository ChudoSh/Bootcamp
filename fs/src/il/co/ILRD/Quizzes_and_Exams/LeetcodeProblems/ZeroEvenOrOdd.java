package il.co.ILRD.Quizzes_and_Exams.LeetcodeProblems;

import java.util.LinkedList;
import java.util.Queue;
import java.util.concurrent.Semaphore;
import java.util.concurrent.atomic.AtomicInteger;

public class ZeroEvenOrOdd {
    private int numberToPrint;
    private Queue<IntConsumer> q = new LinkedList<>();


    public ZeroEvenOrOdd(int n) {
        this.numberToPrint = n;
    }

    // printNumber.accept(x) outputs "x", where x is an integer.
    public void zero(IntConsumer printNumber) throws InterruptedException {

    }

    public void even(IntConsumer printNumber) throws InterruptedException {

    }

    public void odd(IntConsumer printNumber) throws InterruptedException {

    }
}

class IntConsumer {
    public void accept(int n) {
        System.out.println();
    }
}