package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

public class Quiz3 {
    public Quiz3() {
        System.out.println("constructor called");
    }

    static {
        System.out.println("static initializer called");
    }

    {
        System.out.println("instance initializer called");
    }

    public static void main (String[]args){
        new Quiz3();
        new Quiz3();
    }
}
