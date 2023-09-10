package il.co.ILRD.Quizzes_and_Exams.DS3Exam;

import java.util.Deque;
import java.util.ArrayDeque;


public class Exer4 {
    public static void main(String[] args) {
        String str = "barshadkhin";

        str = rotateCharArray(str, 15, false);
//        str = rotateCharArray(str, 4, true);

        System.out.println(str);
    }

    public static String rotateCharArray(String str, int shift, boolean rotateLeft) {
        return (rotateLeft) ? rotateCharArrayLeft(str, shift) : rotateCharArrayRight(str, shift);
    }

    private static String rotateCharArrayLeft(String str, int shift) {
        Deque<Character> deq = new ArrayDeque<>();

        for (char c : str.toCharArray()) {
            deq.add(c);
        }

        if (shift > str.length()) {
            shift = shift % str.length();
        }

        for (int i = 0; i < shift; ++i) {
            char temp = deq.removeFirst();
            deq.addLast(temp);
        }

        return deq.toString();
    }

    private static String rotateCharArrayRight(String str, int shift) {
        Deque<Character> deq = new ArrayDeque<>();

        for (char c : str.toCharArray()) {
            deq.add(c);
        }

        if (shift > str.length()) {
            shift = shift % str.length();
        }

        for (int i = 0; i < shift; ++i) {
            char temp = deq.removeLast();
            deq.addFirst(temp);
        }

        return deq.toString();
    }
}
