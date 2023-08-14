package co.il.ILRD.Quizzes_and_Exams.DS2Exam;

public class Q7_ReverseString {

    public static String reverseString(String str) {
        StringBuilder reversed = new StringBuilder();

        for(int i = str.length() - 1; i >= 0; --i){
            reversed.append(str.charAt(i));
        }

        return reversed.toString();
    }
}
