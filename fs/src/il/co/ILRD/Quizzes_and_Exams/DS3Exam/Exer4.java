package il.co.ILRD.Quizzes_and_Exams.DS3Exam;


public class Exer4 {
    public static void main(String[] args) {
        String str = "barshadkhin";

        str = rotateCharArray(str, 3);

        System.out.println(str);
    }

    public static String rotateCharArray(String str, int rotate) {
        rotate = rotate % str.length();
        if (rotate < 0) {
            rotate += str.length();
        }

        str = reverseString(str.toCharArray(), 0, str.length() - 1);
        str = reverseString(str.toCharArray(), 0, rotate - 1);

        return reverseString(str.toCharArray(), rotate, str.length() - 1);
    }

    public static String reverseString(char[] chars, int start, int end) {
        while (start < end) {
            char tmp = chars[start];
            chars[start] = chars[end];
            chars[end] = tmp;
            ++start;
            --end;
        }

        return String.copyValueOf(chars);
    }
}
