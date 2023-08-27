//package co.il.ILRD.Quizzes_and_Exams.JavaExam.Q30;
//
//class F<T> {
//    T t1;
//    static T t = new T(); //cant instance a generic type
//    class G {
//        T t3;
//        void foo () {
//            System.out.println (t3); // will print null
//        }
//    }
//    static class H<J> {
//        T t; //must be static
//        static J j;
//        private void foo (T t) { // must be static
//            System.out.println (t);
//        }
//        public static void foo2 (J j) {
//            T t;
//            this.t = new T(); // cant instantiate a generic type
//            System.out.println (i); // what is i
//        }
//    }
//
//    class MyClass <? extends T> { //cant create a generic bound inside an inner class?
//        public void foo () {
//            T t;
//            System.out.println ("hi", t ); // t is not initialized
//        }
//    }
//
//} // class F<T>
