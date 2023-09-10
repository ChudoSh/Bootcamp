package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

public class Quiz1 {
    static void StrEqual() {
        String s1 = "hi";
        String s2 = new String("hi");
        String s3 = "hi";

        System.out.println("=========StrEqual=========");

        if (s1 == s2) {
            System.out.println("s1 and s2 are equal");
        } else {
            System.out.println("s1 and s2 are not equal");
        }

        if (s1 == s3) {
            System.out.println("s1 and s3 are equal");
        } else {
            System.out.println("s1 and s3 are not equal");
        }
    }

    static void Increment() {
        Integer i = 10;
        Integer j = 11;
        Integer k = ++i; //INCR
        System.out.println("=========Increment=========");
        System.out.println("k == j is " + (k == j));
        System.out.println("k.equals(j) is " + k.equals(j));
    }

    static void ArrayCompare() {
        int[] arr1 = {1, 2, 3, 4, 5};
        int[] arr2 = {1, 2, 3, 4, 5};
        System.out.println("=========ArrayCompare=========");
        System.out.println("arr1 == arr2 is " + (arr1 == arr2));
        System.out.println("arr1.equals(arr2) is " + arr1.equals(arr2));
    }
    static class Overloaded {
        public static void foo(Integer i) {
            System.out.println("foo(Integer)");
        }

        public static void foo(short i) {
            System.out.println("foo(short)");
        }

        public static void foo(long i) {
            System.out.println("foo(long)");
        }

        public static void foo(int... i) {
            System.out.println("foo(int ...)");
        }
    }


    static class Point2D {
        private int x, y;

        public Point2D(int x, int y) {
            System.out.println("=========Point2D=========");
            x = x;
        }

        public String toString() {
            return ("[" + x + "," + y + "]");
        }
    }





    public static void main(String[] args) {
        Quiz1.StrEqual();
        Quiz1.ArrayCompare();
        Quiz1.Increment();
        Point2D newPoint = new Point2D(1, 5);
        System.out.println(newPoint);
    }
}


