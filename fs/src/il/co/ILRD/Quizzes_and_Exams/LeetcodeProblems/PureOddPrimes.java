package il.co.ILRD.Quizzes_and_Exams.LeetcodeProblems;

public class PureOddPrimes {
    public static long[] onlyOddDigPrimes(long n) {
        long[] result = new long[3];

        for (long i = 2; i <= n; ++i) {
            if (isPure(i)) {
                ++result[0];
                result[1] = i;
            }
        }

        ++n;

        while (!isPure(n)) {
            ++n;
        }

        result[2] = n;
        return result;
    }

    private static boolean isPure(long n) {
        long digit = 0L;

        for (long i = 2; i <= Math.sqrt(n); i++) {
            if (n % i == 0) {
                return false;
            }
        }

        while (0 != n) {
            digit = n % 10;
            if (digit % 2 == 0) {
                return false;
            }

            n /= 10;
        }
        return true;

    }
}

