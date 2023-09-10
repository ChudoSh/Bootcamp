package il.co.ILRD.Quizzes_and_Exams.DS3Exam;

public class Exer3 {
    public static boolean findCharInCharArray(char[] arr, char c) {
        int ASCII_SIZE = 256;
        boolean[] LUT = new boolean[256];

        for (char value : arr) {
            LUT[(int) value]  = true;
        }

        return LUT[(int) c];
    }

    public static void main(String[] args) {
        String str = "asdfasdfasdhggbgfhghjy";

        System.out.println(findCharInCharArray(str.toCharArray(), 'z'));
    }
}