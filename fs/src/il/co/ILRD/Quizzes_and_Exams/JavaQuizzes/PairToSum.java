package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

import java.util.HashMap;

public class PairToSum {
    public static int countPairsToSum(int[] array, int targetSum) {
        HashMap<Integer, Integer> numbers = new HashMap<>();
        int pairs = 0;

        for (int num : array) {
            Integer curPairs = numbers.get(targetSum - num);

            if (null != curPairs) {
                pairs += curPairs;
            }

            incrementKey(numbers, num);
        }

        return pairs;
    }

    private static <K> void incrementKey(HashMap<K, Integer> map, K key) {
        map.putIfAbsent(key, 0);
        map.put(key, map.get(key) + 1);
    }

    public static void main(String[] args) {
        System.out.println(countPairsToSum(new int[]{1, 5, 7, -1, 5, 1, 3, 3},
                6));

    }
}
