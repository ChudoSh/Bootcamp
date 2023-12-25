package il.co.ILRD.Quizzes_and_Exams.LeetcodeProblems;

public class WaterBuckets {
    public static void main(String[] args) {
        System.out.println(WaterBuckets.numOfBuckets(new int[]{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2,}));
    }

    public static int numOfBuckets(int[] arr) {
        int left = 0, count = 0;
        int right = 1;

        while (arr.length > right) {
            while (arr[left] > arr[right]) {
                ++right;
            }

            if (right - left > 0) {
                ++count;
            }
            left = right;
        }

        return count;
    }
}
