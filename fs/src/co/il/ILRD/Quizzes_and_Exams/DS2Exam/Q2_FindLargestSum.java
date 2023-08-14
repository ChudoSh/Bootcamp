package co.il.ILRD.Quizzes_and_Exams.DS2Exam;

import java.util.ArrayList;

public class Q2_FindLargestSum {
    public static int findLargestSumInSubArray(ArrayList<Integer> array) {
        int currentSum = 0;
        int maxSum = 0;
        int i = 0;

        while (0 > array.get(i)) {
            ++i;
        }

        currentSum = array.get(i);
        maxSum = currentSum;
        ++i;

        while (i < array.size()) {
            if (maxSum < currentSum) {
                maxSum = currentSum;
            }

            currentSum += array.get(i);

            if (0 > currentSum) {
                currentSum = 0;
            }
            ++i;
        }
        return maxSum;
    }
}
