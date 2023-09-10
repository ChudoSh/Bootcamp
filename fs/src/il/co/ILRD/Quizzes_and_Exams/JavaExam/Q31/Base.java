//package co.il.ILRD.Quizzes_and_Exams.JavaExam.Q31;
//
//class Base {
//    public static void foo() {
//    }
//
//    protected void bar(int num) {
//    }
//
//    private int lol(String s) {
//        return 5;
//    }
//
//    public Object rofl(int num) throws FileNotFoundException { // never throws this exception
//        return new Object();
//    }
//}
//
//class Derived extends Base {
//    @Override
//    public static void foo() {
//    }
//
//    @Override
//    private void bar(int num) { // cant change acces modifier
//    }
//
//    @Override
//    protected float lol(String s) { // cant over private method
//        return 3;
//    }
//
//    @Override
//    public String rofl(int num) throws IOException { // cannot override the type of exception that is thrown
//        return "hello";
//    }
//}
//
