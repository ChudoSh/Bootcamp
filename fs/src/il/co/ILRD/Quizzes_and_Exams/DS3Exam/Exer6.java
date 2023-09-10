package il.co.ILRD.Quizzes_and_Exams.DS3Exam;

import java.util.Stack;

public class Exer6 {
    Stack<Integer> main;
    Stack<Integer> min;

    public void push(int value) {
        assert main.size() < main.capacity();

        if (value > main.peek()) {
            min.push(value);
        } else {
            min.push(main.peek());
        }

        main.push(value);
    }

    public int peek(){
        return main.peek();
    }

    public int pop(){
        min.pop();
        return main.pop();
    }

    public int getMin(){
        return min.peek();
    }
}
