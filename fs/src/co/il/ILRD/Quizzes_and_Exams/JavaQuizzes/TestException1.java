package co.il.ILRD.Quizzes_and_Exams.JavaQuizzes;

import java.io.IOException;
public class TestException1 {
    public void start() throws IOException{
    }

    public void foo() throws NullPointerException{
    }
}

class TestException2 extends TestException1{

    public void start() {
    }

    public void foo() throws RuntimeException{
    }
}
