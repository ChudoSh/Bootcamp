package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

import java.util.*;

public class FirstNonDuplicate {
    private static final Deque<Long> s = new ArrayDeque<>();
    private static final Map<Long, Integer> map = new HashMap<>();

    public static void input(long num) {
        if (null == map.putIfAbsent(num, 1)) {
            s.addLast(num);
            return;
        }

        int count = map.get(num) + 1;
        map.put(num,count);
        if (2 == count){
            s.remove(num);
        }

    }

    public static Long output() {
        if (!s.isEmpty()){
            return s.getFirst();
        }

        return 0L;
    }

    public static void print() {
        System.out.println(s);
    }

    public static void main(String[] args) {
        long[] arr = new long[]{1, 2, 2, 3, 3, 4, 1, 1, 1, 4, 5};
        for (long num : arr) {
            input(num);
        }

        print();
    }
}