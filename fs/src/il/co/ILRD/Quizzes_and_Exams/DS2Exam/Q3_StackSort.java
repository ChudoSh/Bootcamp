package il.co.ILRD.Quizzes_and_Exams.DS2Exam;

import java.util.Stack;

public class Q3_StackSort {
    public static Stack<Integer> sortStack(Stack<Integer> toSort){
        Stack<Integer> auxStack = new Stack<>();
        int temp = 0;

        while (!toSort.isEmpty()){

            temp = toSort.pop();

            while (!auxStack.isEmpty() && auxStack.peek() < temp ){
                toSort.push( auxStack.pop());
            }

            auxStack.push(temp);
        }

        return auxStack;
    }
}
