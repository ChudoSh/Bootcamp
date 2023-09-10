package il.co.ILRD.Quizzes_and_Exams.DS2Exam;

public class Q8_StringPermutations {
    public static void printAllPermutations(String str) {
        printPermutations(str, "");
    }

    private static void printPermutations(String str, String ans) {

        if (str.isEmpty()) {
            System.out.println((ans));
            for (int i = 1; i < ans.length(); ++i) {
                printPermutations(ans.substring(0, ans.length() - 1), "");
            }
            return;
        }

        for (int i = 0; i < str.length(); ++i) {
            char ch = str.charAt(i);
            String result = str.substring(0, i) + str.substring(i + 1);
            printPermutations(result, ans + ch);
        }
        /*
        to ensure that each word will generate only once we will use hash table.

        Hash table will give us the possibility of checking if a word was generated in o(1),
        for each word we will insert a counter to the value of the key that generated to the permutation.
        and at the end we will go throw the hash table nd print the Strings that there value are bigger than 0.
        * */
    }

}
