package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

import java.util.*;

public class FirstNonDuplicate {
    private static final Queue<Long> q = new LinkedList<>();
    private static final Map<Long, Integer> map = new HashMap<>();

    public static void input(long num) {
        if (null == map.putIfAbsent(num, 0)) {
            map.put(num, 1);
            q.add(num);
            return;

        }
        q.remove();
        q.add(q.peek());
    }

    public static Long output() {
        return q.peek();
    }

    public static void print() {
        for (Long num : q) {
            System.out.println(num);
        }
    }

    public static void main(String[] args) {
        long[] arr = new long[]{1, 2, 2, 3, 3, 4, 1, 1, 1, 4, 5};
        for (long num : arr) {
            input(num);
        }

        print();
    }
}