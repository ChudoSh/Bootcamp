package co.il.ILRD.DS2Exam;

import java.util.Stack;

public class Q10 {
    private static void sortStackRec(Stack<Integer> s, int x)
    {
        // Base case: Either stack is empty or newly
        // inserted item is greater than top (more than all
        // existing)
        if (s.isEmpty() || x < s.peek()) {
            s.push(x);
            return;
        }

        // If top is greater, remove the top item and recur
        int temp = s.pop();
        sortStackRec(s, x);

        // Put back the top item removed earlier
        s.push(temp);
    }

    // Method to sort stack
    public static void sortStack(Stack<Integer> s)
    {
        // If stack is not empty
        if (!s.isEmpty()) {
            // Remove the top item
            int x = s.pop();

            // Sort remaining stack
            sortStack(s);

            // Push the top item back in sorted stack
            sortStackRec(s, x);
        }
    }
}
