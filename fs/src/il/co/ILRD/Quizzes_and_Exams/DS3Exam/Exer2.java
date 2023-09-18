package il.co.ILRD.Quizzes_and_Exams.DS3Exam;

import java.util.Arrays;

public class Exer2 {
    public static int findTwoIntOfgivenSum(int[] arr, int sumOfTwo) {
        int start = 0;
        int end = arr.length - 1;

        Arrays.sort(arr);

        while (arr[end] > sumOfTwo) {
            --end;
        }

        while (start <= end && (arr[start] + arr[end]) != sumOfTwo) {
            if (arr[start] + arr[end] < sumOfTwo) {
                ++start;
            } else {
                --end;
            }
        }

        return (start > end) ? 0 : 1;
    }
}
