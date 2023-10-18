package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;

public class Staq<T> {
    private Queue<T> main;
    private Queue<T> aux;

    public Staq() {
        main = new LinkedList<>();
        aux = new LinkedList<>();
    }

    public void push(T data) {
        this.aux.add(data);

        while (!this.main.isEmpty()) {
            this.aux.add(this.main.peek());
            this.main.remove();
        }

        Queue<T> temp = this.main;
        this.main = this.aux;
        this.aux = temp;
    }

    public T pop() {
        if (this.main.isEmpty()) {
            return null;
        }

        return this.main.remove();
    }

    public T peek() {
        if (this.main.isEmpty()) {
           return null;
        }

        return this.main.peek();
    }

    public static void main(String[] args) {
        Staq<Integer> staq = new Staq<>();

        staq.push(6);
        staq.push(5);
        staq.push(4);
        staq.push(3);

        System.out.println(staq.pop());
        System.out.println(staq.pop());
        System.out.println(staq.pop());
    }
}
