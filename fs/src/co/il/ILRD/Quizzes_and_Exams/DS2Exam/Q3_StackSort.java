package co.il.ILRD.Quizzes_and_Exams.DS2Exam;

import java.util.Stack;

public class Q3_StackSort {
    public static Stack<Integer> sortStack(Stack<Integer> toSort){
        Stack<Integer> aux_stack = new Stack<Integer>();
        int temp = 0;

        while (!toSort.isEmpty()){

            temp = toSort.pop();

            while (!aux_stack.isEmpty() && aux_stack.peek() < temp ){
                toSort.push( aux_stack.pop());
            }

            aux_stack.push(temp);
        }

        return aux_stack;
    }
}
