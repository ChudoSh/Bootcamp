package il.co.ILRD.Quizzes_and_Exams.DS3Exam;


import java.util.Stack;

public class Exer7 {
    public static void main(String[] args) {
       String str = "(({}))";

        System.out.println(isParanCorrect(str));
    }

    public static int isParanCorrect(String expression){
        Stack<Character> stack = new Stack<>();
        int SUCCESS = 1;
        int FAIL = 0;

        for (char c: expression.toCharArray()){
            if (isLeft(c)){
                stack.push(c);
            } else if (isRight(c)){
                if (stack.isEmpty() || !isPair(stack.peek(), c)){
                    return FAIL;
                }
                stack.pop();
            }
        }

        return SUCCESS;
    }

    public static boolean isLeft(char c){
        return '(' == c || '[' == c || '{' == c || '<' == c;
    }
    public static boolean isRight(char c){
        return ')' == c || ']' == c || '}' == c || '>' == c;
    }
    public static boolean isPair(char l, char r){
       switch (l){
           case '(':
               return ')' == r;
           case '[':
               return ']' == r;
           case '{':
               return '}' == r;
           case '<':
               return '>' == r;
           default:
               return false;
       }
    }
}
