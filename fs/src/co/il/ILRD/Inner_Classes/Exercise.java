package co.il.ILRD.Inner_Classes;

public class Exercise {
    public static void main(String[] args) {
        Outer st = new Outer();
        Outer.Inner fl = st.new Inner();
        fl.foo1(23);
    }
}

class Outer {
    private final int x = 0;

    class Inner {
        public int x = 1;

        void foo1(int x) {
            System.out.println("x = " + x);
            System.out.println("this.x = " + this.x);
            System.out.println("OuterClass.this.x = "
                    + Outer.this.x);
        }
    }
}
