package co.il.ILRD.Quizzes_and_Exams.JavaExam.Q29;

public class SubClass extends SuperClass {
    int intSubClass = 100;

    {
        System.out.println("1. instance initializer called of SubClass");
        System.out.println(intSubClass);
    }

    public SubClass() {

        System.out.println("constructor called of SubClass");
        System.out.println(intSubClass);
        intSubClass *= 2;
    }

    static {
        System.out.println("1. static initializer called of SubClass");
    }

    {
        System.out.println("2. instance initializer called of SubClass");
    }

    static {
        System.out.println("2. static initializer called of SubClass");
    }

    public static void main(String[] args) {
        new SubClass();
        new SubClass();
    }
}