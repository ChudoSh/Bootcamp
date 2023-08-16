package co.il.ILRD.Generics;

import java.util.ArrayList;

public class Exercises {
    public static void main(String[] args) {
        ArrayList<Integer> i = new ArrayList<>();
        ArrayList<Character> c = new ArrayList<>();
        ArrayList<String> s = new ArrayList<>();

        i.add(5);
        c.add('c');
        s.add("nice");

        printArray(i);
        printArray(c);
        printArray(s);

        FooReference<Integer> newInt = new FooReference<>();
        newInt.setT(4);
        System.out.println(newInt.getClass().getName());
        System.out.println(newInt.getT());
    }

    public static void printArray(ArrayList<?> toPrint){
        System.out.println(toPrint.toString());
    }

    public static class FooReference<T>{
        private T t;

        public T getT() {
            return this.t;
        }

        public void setT(T t) {
            this.t = t;
        }
    }
}
