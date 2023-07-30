public class StrEqual {
    //1
    public static void main(String[] args) {
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
}
