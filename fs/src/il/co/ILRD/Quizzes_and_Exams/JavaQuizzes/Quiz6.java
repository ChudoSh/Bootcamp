package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

public class Quiz6 {
    /*
    public class Singleton<T> { // class must be declared static if all its fields and methods are static
        public static <T> Singleton<T> getInstance() {
            if (instance == null) {
                System.out.println("Create Instance");
                instance = new Singleton<T>(); //cannot instantiate the class within itself
                //cannot instantiate a static class
            }
            System.out.println("return Instance");
            return instance;
        }
        private static Singleton<T> instance = null;
    }
*/
    interface Person {
        default void sayHello() {
            System.out.println("Hello");
        }
    }

    interface Male {
        default void sayHello() {
            System.out.println("Hi");
        }
    }

    public class Sam implements Person, Male {
        @Override
        public void sayHello() {
            Person.super.sayHello();
        }
    }

//    Sam sam = new Sam();
//    sam.sayHello();
//    Sam secondSam = new Sam();
//    secondSam.sayHello();
}
