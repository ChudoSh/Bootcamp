//package co.il.ILRD.Quizzes_and_Exams.JavaExam.Q35;
//
//class C {
//    private String s = "123";
//
//    class C1 {
//        private C c = new C();
//        private static String str = "hello world"; //cannot have a static in field inside inner classes
//
//        private void foo() {
//            s = "456";
//            System.out.println(str);
//        }
//    }
//
//    class C2 {
//        private C1 c1 = new C1();
//
//        private void foo2() {
//            c1.c.s = "abc";
//        }
//    }
//
//    private static class C3 {
//        private int i = 3;//must be static
//
//        static void foo() {
//            this.i = 5;
//        }
//    }
//
//    void foo2() {
//        private static String s1 = "hello"; //cant have access modifiers for a local variable
//    }
//}
//
//public class Main {
//    public static void main(String[] args) {
//        C.C2 c2 = new C.C2(); // ???
//        C.C3 c3 = new C.C3();//cant instantiate a static class
//    }