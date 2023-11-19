package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

import java.util.HashMap;
import java.util.Map;

public class PrintMissingElements {
    public static void printMissingElements(long[] arr, long low, long high) {
        Map<Long, Boolean> map = new HashMap<>();
        int j = 0;

        for (long i = low; i <= high; ++i) {
            map.put(i, false);
        }

        while (j < arr.length) {
            if (map.containsKey(arr[j])){
                map.put(arr[j], true);
            }
            ++j;
        }

        for (Long toPrint : map.keySet()) {
            if (!map.get(toPrint)){
                System.out.println(toPrint.longValue());
            }
        }
    }

    public static void main(String[] args) {
        printMissingElements(new long[]{8, 1, 6, 4}, 3,6);
    }
}
