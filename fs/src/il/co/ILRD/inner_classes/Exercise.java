package il.co.ILRD.inner_classes;

public class Exercise {
    public static void main(String[] args) {
        Outer st = new Outer();
        Outer.Inner fl = st.new Inner();
        Outer.Inner fsl = st.new Inner();
        fl.foo1(23);
        Outer.banana();

        if (fl.equals(fsl)){
            System.out.println("they are the same");
        }


    }
}

class Outer {
    private final int x = 0;

    public static void banana() {
        class Anonymous {
            final String something = "This is Anonymous, prepare to be cyberbullied";

            public void oof() {
                System.out.println(this.something);
            }
        }
        new Anonymous().oof();
    }

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
