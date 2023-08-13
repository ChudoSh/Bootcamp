package co.il.ILRD.Quizzes.DS2Exam;

public class Q8 {
    public static void printAllPermutations(String str) {
        printPermutations(str, "");
    }

    private static void printPermutations(String str, String ans) {
        int j = 0;
        // If string is empty
        if (str.isEmpty()) {
            System.out.print(ans + " ");
            return;
        }


        for (int i = 0; i < str.length(); i++) {

            // ith character of str
            char ch = str.charAt(i);

            // Rest of the string after excluding
            // the ith character
            String ros = str.substring(0, i) +
                    str.substring(i + 1);

            // Recursive call, adding the extracted char to the final printed string of this specific permute
            printPermutations(ros, ans + ch);
        }
    }
}
