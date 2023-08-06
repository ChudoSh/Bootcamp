package co.il.ILRD.Quizzes;

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
