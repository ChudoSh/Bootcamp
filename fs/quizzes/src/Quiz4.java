public class Quiz4 {
    static class Base1 {
        public Base1() {
            System.out.println("Base");
        }
    }

    static class Derived1 extends Base1 {
        public Derived1() {
            System.out.println("Derived");
        }
    }

    static class DeriDerived1 extends Derived1 {
        public DeriDerived1() {
            System.out.println("DeriDerived");
        }
    }

    static class Base2 {
        public Base2() {
            System.out.print("Base ");
        }

        public Base2(String s) {
            System.out.print("Base: " + s);
        }
    }

    static class Derived2 extends Base2 {
        public Derived2(String s) {
            super(); // Stmt-1
            super(s); // Stmt-2
            System.out.print("Derived ");
        }
    }

    static class Base3 {
        public void test() {

        }
    }

    static class Derived3 extends Base3 {
        public void test() {
            System.out.println("Base3");
        }
    }

    static class DeriDerived3 extends Base3 {
        public void test() {
            System.out.println("Base 3-2");
        }
    }


    public static void main(String[] args) {
        Derived1 b = new DeriDerived1();
        Base2 a = new Derived2("Hello ");
        Base3 c = new Derived3();
//        ((DeriDerived3) c).test();
    }
}
