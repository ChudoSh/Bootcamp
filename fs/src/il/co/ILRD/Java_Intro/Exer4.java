package il.co.ILRD.Java_Intro;

import java.util.*;
import java.util.List;
import java.util.Random;
public class Exer4 {
    public static void main(String[] args) {
        List<int[]> myList = new ArrayList<int[]>();

        for (int i = 0; i < 1000; ++i) {
            int[] newArr = new int[100000];
            for (int j = 0; j < 100000; ++j) {
                newArr[j] = new Random().nextInt();
            }
            myList.add(newArr);
            System.out.println("Free memory (bytes): " +
                                Runtime.getRuntime().freeMemory());

        }
    }
}

