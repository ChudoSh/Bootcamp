package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

import java.util.Stack;

public class ExpressionTree {
    Stack<Character> tree;
    String expression;

    public ExpressionTree(String expression) {
        this.tree = new Stack<>();
        this.expression = expression;
    }

    public double calculate() {
        Node temp, v1, v2;
        Stack<Node> stack = new Stack<>();

        for (char ch : this.expression.toCharArray()){

        }

        return 0.0;
    }

    private boolean isOperator(char c) {
        return '+' == c || '-' == c || '*' == c || '/' == c;
    }
    private static class Node{
        char value;
        Node right, left;

        public Node(char value){
            this.value = value;

        }
    }

}
// +,3,*,+,2,5,9