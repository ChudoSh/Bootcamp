package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes.Quiz7;

public class Base {
    private int member1 = 1;
    private int member2 = 2;

    public Base() {
        System.out.println("Base Ctor");
        print();
    }

    public void print() {
        System.out.println(member1 + " " + member2);
    }
}
