package il.co.ILRD.Quizzes_and_Exams.Simulations;

import org.junit.jupiter.api.Test;

import static org.junit.Assert.assertEquals;

public class CountSubArraysOfSum {
    public static int countNumOfSubArrays(int[] arr, int input) {
        int count = 0;
        int sum = 0;
        int fast = 0;
        int slow = 0;

        if (arr[0] == input) {
            sum += arr[0];
            ++count;
            ++fast;
        }

        while (slow < arr.length) {
            while (sum < input && fast < arr.length) {
                sum += arr[fast];
                ++fast;
            }

            if (sum == input) {
                ++count;
            }

            sum -= arr[slow];
            ++slow;
        }

        return count;
    }

    @Test
    void test1() {
        assertEquals(4, CountSubArraysOfSum.countNumOfSubArrays(new int[]{5, 0, 5}, 5));
    }

    @Test
    void test2() {
        assertEquals(3, CountSubArraysOfSum.countNumOfSubArrays(new int[]{1, 1, 1}, 1));
    }

    @Test
    void test3() {
        assertEquals(3, CountSubArraysOfSum.countNumOfSubArrays(new int[]{0, 0, 1}, 1));
    }

    @Test
    void test4() {
        assertEquals(1, CountSubArraysOfSum.countNumOfSubArrays(new int[]{2, 5, 3, 1, 4}, 9));
    }

}