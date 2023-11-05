package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes.Quiz9;

import java.io.IOException;

public class q3 {
    public void foo() throws IOException {
        int count = 0; /*Local variables must be initialized!*/
        if (System.in.read() != -1)
            ++count;
        System.out.println("input has " + count + " chars.");
    }
}
