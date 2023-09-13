package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes.Quiz7;

public class Derived extends Base{
    private int member3 = 3;
    private int member4 = 4;

    public Derived() {
        System.out.println("Derived Ctor");
        print();
    }

    @Override
    public void print() {
        System.out.println(member3 + " " + member4);
    }
}
