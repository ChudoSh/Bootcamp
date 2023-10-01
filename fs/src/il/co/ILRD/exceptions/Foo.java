package il.co.ILRD.exceptions;

import java.io.IOException;


public class Foo {
    private static void foo1() throws IOException {
        return;
    }

    private static void foo2() {
        throw new NullPointerException();
    }

    private static void foo3() throws MyException.MyException1 {
        throw new MyException.MyException1("This is MyException1");
    }

    private static void foo4() throws MyException.MyException2 {
        throw new MyException.MyException2("This is MyException2");
    }

    public static void main(String[] args) throws MyException.MyException2 {
        byte[] b = new byte[100];

//        try {
//            b[101] = 1;
//        } catch (ArrayIndexOutOfBoundsException e){
//            printStackTrace();
//        }  finally {
//            foo3();
//        }

        try {
            throw new MyException.MyException1("Meh");
        }catch (Exception e){
            e.printStackTrace();
        }
    }
}
