package co.il.ILRD.Quizzes_and_Exams.JavaQuizzes;

import java.util.ArrayList;
import java.util.List;

import static co.il.ILRD.Quizzes_and_Exams.JavaQuizzes.Quiz5.Test.func;

interface SomeInterface {
    default void foo() {
        System.out.println("my foo");
    }
}

public class Quiz5 {
    public static class SomeClass implements SomeInterface {
        public void foo() {
            System.out.println("my new foo!");
        }
    }

    public void main(String[] args) {
        SomeClass sc = new SomeClass();
        sc.foo();
        System.out.println(func());
    }
    public static class Test {

        static int x = 5;

        static int func() {
//            static int x = 10;
            return --Test.x;
        }
    }

}