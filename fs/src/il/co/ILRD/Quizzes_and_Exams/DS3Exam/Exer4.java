package il.co.ILRD.Quizzes_and_Exams.DS3Exam;


public class Exer4 {
    public static void main(String[] args) {
        String str = "barshadkhin";

        str = rotateCharArray(str, 3);
//        str = rotateCharArray(str, 4, true);

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


//        return (rotateLeft) ? rotateCharArrayLeft(str, shift) : rotateCharArrayRight(str, shift);
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

//    private static String rotateCharArrayLeft(String str, int shift) {
//    }
//        Deque<Character> deq = new ArrayDeque<>();
//
//        for (char c : str.toCharArray()) {
//            deq.add(c);
//        }
//
//        if (shift > str.length()) {
//            shift = shift % str.length();
//        }
//
//        for (int i = 0; i < shift; ++i) {
//            char temp = deq.removeFirst();
//            deq.addLast(temp);
//        }
//
//        return deq.toString();
//    }
//
//    private static String rotateCharArrayRight(String str, int shift) {
//        Deque<Character> deq = new ArrayDeque<>();
//
//        for (char c : str.toCharArray()) {
//            deq.add(c);
//        }
//
//        if (shift > str.length()) {
//            shift = shift % str.length();
//        }
//
//        for (int i = 0; i < shift; ++i) {
//            char temp = deq.removeLast();
//            deq.addFirst(temp);
//        }
//
//        return deq.toString();
//    }
}
