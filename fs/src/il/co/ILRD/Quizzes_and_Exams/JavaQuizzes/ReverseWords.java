package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

import java.util.Stack;

public class ReverseWords {
    public void reversePrint(String str) {
        Stack<Character> stack = new Stack<>();
        StringBuilder builder = new StringBuilder();

        for (int i = 0; i < str.length(); ++i) {
            if (' ' == str.charAt(i)) {
                this.emptyAndBuild(stack, builder);
            } else {
                stack.push(str.charAt(i));
            }
        }

        this.emptyAndBuild(stack, builder);
        System.out.println(builder);
    }

    private void emptyAndBuild(Stack<Character> s, StringBuilder builder) {
        while (!s.isEmpty()) {
            builder.append(s.pop());
        }

        builder.append(" ");
    }

    public static void main(String[] args) {
        new ReverseWords().reversePrint("Hello World");
    }
}
