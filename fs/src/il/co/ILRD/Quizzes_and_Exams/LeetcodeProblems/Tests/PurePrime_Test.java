package il.co.ILRD.Quizzes_and_Exams.LeetcodeProblems.Tests;

import il.co.ILRD.Quizzes_and_Exams.LeetcodeProblems.PureOddPrimes;
import org.junit.Test;

import static org.junit.Assert.assertArrayEquals;

public class PurePrime_Test {
    @Test
    public void test1() {
        assertArrayEquals(new long[]{7, 19, 31}, PureOddPrimes.onlyOddDigPrimes(20));
    }

    @Test
    public void test2() {
        assertArrayEquals(new long[]{9, 37, 53}, PureOddPrimes.onlyOddDigPrimes(40));
    }

    @Test
    public void test3() {
        assertArrayEquals(new long[]{10, 53, 59}, PureOddPrimes.onlyOddDigPrimes(55));
    }

    @Test
    public void test4() {
        assertArrayEquals(new long[]{11, 59, 71}, PureOddPrimes.onlyOddDigPrimes(60));
    }

    @Test
    public void test5() {
        assertArrayEquals(new long[]{15, 97, 113}, PureOddPrimes.onlyOddDigPrimes(100));
    }

}
