public class Quiz1{
    void StrEqual() {
        String s1 = "hi";
        String s2 = new String("hi");
        String s3 = "hi";

        System.out.println("=========Q1=========");

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
     void Increment() {
        Integer i = 10;
        Integer j = 11;
        Integer k = ++i; //INCR
        System.out.println("=========Q3=========");
        System.out.println("k == j is " + (k == j));
        System.out.println("k.equals(j) is " + k.equals(j));
    }
    void ArrayCompare() {
        int[] arr1 = {1, 2, 3, 4, 5};
        int[] arr2 = {1, 2, 3, 4, 5};
        System.out.println("=========Q4=========");
        System.out.println("arr1 == arr2 is " + (arr1 == arr2));
        System.out.println("arr1.equals(arr2) is " + arr1.equals(arr2));
        }
    class OverLoaded() {
        public void foo(Integer i) {System.out.println("foo(Integer)");}
        public void foo(short i) {System.out.println("foo(short)");}
        public void foo(long i) {System.out.println("foo(long)");}
        public void foo(int ... i) {System.out.println("foo(int ...)");}
    }
    class Point2D() {
        private int x, y;
        public Point2D(int x, int y) {
            x = x;
        }
        public String toString() {
            return ("[" + x + "," + y + "]");
        }
    }

    public static void main(String[] args) {

    }
}


