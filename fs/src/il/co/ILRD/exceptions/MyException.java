package il.co.ILRD.exceptions;

import java.io.IOException;

public class MyException {

    public static class MyException1 extends RuntimeException{
        public MyException1(String message){
            super(message);
        }
    }

    public static class MyException2 extends IOException {
        public MyException2(String message){
            super(message);
        }

    }

}
