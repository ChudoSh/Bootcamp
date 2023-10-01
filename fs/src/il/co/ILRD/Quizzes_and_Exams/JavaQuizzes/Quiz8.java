package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

public class Quiz8 {
    // 1.
    class A<T> {
        public void foo(Object o) {
        }

//        public void foo(T t) { what if T is of type Object
//        }
    }

    //2.
    class B<T> {
        public void foo(Object o) {
        }

        public <Z extends Number> void foo(Z t) {
        }
    }

    //3
    class C<T extends Number> {
        public void foo(Object o) {
        }

        public void foo(T t) {
        }
    }
}
