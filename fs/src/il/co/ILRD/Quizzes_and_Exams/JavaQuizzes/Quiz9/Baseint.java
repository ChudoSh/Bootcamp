package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes.Quiz9;

public class Baseint {
    private int member1 = 1;
    private int member2 = 2;

    public Baseint() {
        System.out.println("Base Ctor");
        printFirst();
        printSecond();
    }

    void printFirst() {
        System.out.println(member1);
    }

    private void printSecond() {
        System.out.println(member2);
    }

}

class DerivedInit extends Baseint {
    private int member3 = 3;
    private int member4 = 4;

    public DerivedInit() {
        System.out.println("Derived Ctor");
        printFirst();
        printSecond();
    }

    /*private*/ void printFirst() { /*cannot override method with different access modifier*/
        System.out.println(member3);
    }

    private void printSecond() {
        System.out.println(member4);
    }
}

class TestInit {
    public static void main(String[] args) {
        DerivedInit d = new DerivedInit();
    }
}
