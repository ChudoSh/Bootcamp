package il.co.ILRD.Quizzes_and_Exams.DS3Exam;

public class Exer8 {
    public static void main(String[] args) {
        System.out.println(multiply(5, 3));
        System.out.println(increment(5));
    }

    public static int multiply(int a, int b) {
        if (1 == b){
            return a;
        }

        return a + multiply(a, --b);
    }

    public static int increment(int a) {
        return incrementRec(a, 1);
    }

    private static int incrementRec(int a, int one) {
        if (0 == (a & one)){
            return (a ^ one);
        }

        a ^= one;
        one <<= 1;

        return incrementRec(a, one);
    }
}
