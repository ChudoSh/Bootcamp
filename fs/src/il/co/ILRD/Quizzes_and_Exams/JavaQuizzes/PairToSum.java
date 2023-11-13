package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

public class PairToSum {
    public static int countPairToSum(int[] arr, int sum){
        int pairCount = 0;

        /*
        need to store the number of pairs that make up the sum in the given array.

        input:
        arr = 1, 5, 7 ,-1
        sum = 6

        output:
        (1 + 5 = 6), (7 - 1 = 6) => 2

        solutions:
            map -> store the corresponding value that completes to the sum, thus the entry will be: (key = 1, value = 6 - 1)
            how it works if there are apearences of the same numbers in the array?

        dynamic programming
            problematic for backtracking, might not meet the requirements
            that is if i 1 and a 5 somewhere in the array, how do i find them?
        */


        return  pairCount;
    }

    public static void main(String[] args) {

    }
}
