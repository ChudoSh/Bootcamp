import java.io.*;

public class Find2MissingNums {
// Java Program to find 2 Missing
// Numbers using O(1) extra space

    // Returns the sum of the array
    static int getSum(int arr[], int size) {
        int sum = 0;
        for (int i = 0; i < size; i++)
            sum += arr[i];
        return sum;
    }

    // Function to find two missing
// numbers in range [1, n]. This
// function assumes that size of
// array is n-2 and all array
// elements are distinct
    static void findTwoMissingNumbersMath(int arr[], int size) {
        int sumSmallerHalf = 0;
        int sumGreaterHalf = 0;
        int avg = 0;
        // Sum of 2 Missing Numbers
        int sum = (size * (size + 1)) / 2 - getSum(arr, size - 2);

        // Find average of two elements
        avg = (sum / 2);

        // Find sum of elements smaller
        // than average (avg) and sum of
        // elements greater than average (avg)
        for (int i = 0; i < size - 2; i++) {
            if (arr[i] <= avg)
                sumSmallerHalf += arr[i];
            else
                sumGreaterHalf += arr[i];
        }

        System.out.println("Two Missing " + "Numbers are");

        // The first (smaller) element =
        // (sum of natural numbers upto
        // avg) - (sum of array elements
        // smaller than or equal to avg)
        int totalSmallerHalf = (avg *
                (avg + 1)) / 2;
        System.out.println(totalSmallerHalf -
                sumSmallerHalf);

        // The first (smaller) element =
        // (sum of natural numbers from
        // avg+1 to n) - (sum of array
        // elements greater than avg)
        System.out.println(((size * (size + 1)) / 2 -
                totalSmallerHalf) -
                sumGreaterHalf);
    }

    static void findTwoMissingNumbersXor(int arr[], int n) {

        int XOR = arr[0];
        for (int i = 1; i < n - 2; i++)
            XOR ^= arr[i];
        for (int i = 1; i <= n; i++)
            XOR ^= i;

        // Now XOR has XOR of two missing elements.
        // Any set bit in it must be set in one missing
        // and unset in other missing number

        // Get a set bit of XOR (We get the rightmost
        // set bit)
        int set_bit_no = XOR & ~(XOR - 1);

        // Now divide elements in two sets by comparing
        // rightmost set bit of XOR with bit at same
        // position in each element.
        int x = 0, y = 0; // Initialize missing numbers
        for (int i = 0; i < n - 2; i++) {
            if ((arr[i] & set_bit_no) > 0)

                /*XOR of first set in arr[] */
                x = x ^ arr[i];
            else
                /*XOR of second set in arr[] */
                y = y ^ arr[i];
        }

        for (int i = 1; i <= n; i++) {
            if ((i & set_bit_no) > 0)

                /* XOR of first set in arr[] and
                   {1, 2, ...n }*/
                x = x ^ i;
            else
                /* XOR of second set in arr[] and
                    {1, 2, ...n } */
                y = y ^ i;
        }

        System.out.println("Two Missing Numbers are ");
        System.out.println(x + " " + y);
    }

    public static void main(String[] args) {
        int arr[] = {1, 3, 5, 6};

// Range of numbers is 2
// plus size of array
        int n = arr.length;

        findTwoMissingNumbersXor(arr, n);
    }
}


