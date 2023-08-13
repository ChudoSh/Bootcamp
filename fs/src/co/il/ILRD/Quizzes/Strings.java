package co.il.ILRD.Quizzes;

public class Strings {
    public static void reverseString(String str) {
        for (int c = str.length() - 1; c >= 0; --c) {
            System.out.print(str.charAt(c));
        }
        System.out.println(" ");
    }

    public static boolean isPalindrome(String str) {
        int i = str.length() - 1;
        int j = 0;

        while ((j <= i) && (str.charAt(i) == str.charAt(j))) {
            ++j;
            --i;
        }

        return str.charAt(i) == str.charAt(j);
    }

    public static void printAllPermutations(String str) {
        printPermutations(str, "");
    }

    private static void printPermutations(String str, String ans) {

        // If string is empty
        if (str.length() == 0) {
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

    public static void main(String[] args) {
        reverseString("banana");
        System.out.println(isPalindrome("2222"));
        printAllPermutations("bar");
    }
}
