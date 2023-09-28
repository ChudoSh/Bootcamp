package il.co.ILRD.inner_classes;

public class Q10n11 {
    public static void main(String[] args) {
        OuterClass st = new OuterClass();
        OuterClass.InnerClass fl = st.new InnerClass();
        fl.foo1(23);
    }
}

class OuterClass {
    private final int x = 0;

    class InnerClass {
        public int x = 1;

        void foo1(int x) {
            System.out.println("x = " + x);
            System.out.println("this.x = " + this.x);
            System.out.println("OuterClass.this.x = "
                    + OuterClass.this.x);
        }
    }

//    public void foo2() {
//        class AIC {
//            public static void foo2() {
//            }
//        }
//        AIC.foo2();
//    }
}


