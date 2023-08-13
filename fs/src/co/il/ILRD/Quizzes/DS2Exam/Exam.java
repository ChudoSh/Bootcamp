package co.il.ILRD.Quizzes.DS2Exam;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

import java.io.File;

import java.util.ArrayList;
import java.util.Stack;


public class Exam {

    @Test
    public void TUQ1(){
        Node tail = new Node(5, null);
        Node four = new Node(4, tail);
        Node three = new Node(3, four);
        Node two = new Node(2, three);
        Node head = new Node(1, two);

        Q1.FlipListRecursion(head);
        assertSame(tail.getNext(), four, "Rec Fail");
        assertSame(four.getNext(), three, "Rec Fail");
        assertSame(three.getNext(), two, "Rec Fail");
        assertSame(two.getNext(), head, "Rec Fail");

        Q1.FlipListIteratively(tail);
        assertSame(head.getNext(), two, "Iter Fail");
        assertSame(two.getNext(), three, "Iter Fail");
        assertSame(three.getNext(), four, "Iter Fail");
        assertSame(four.getNext(), tail, "Iter Fail");
    }

    @Test
    public void TUQ2(){
        ArrayList<Integer> arr = new ArrayList<Integer>();

        arr.add(-2);
        arr.add(1);
        arr.add(-3);
        arr.add(4);
        arr.add(-2);
        arr.add(2);
        arr.add(1);
        arr.add(-5);
        arr.add(-4);

        assertEquals(Q2.findLargestSumInSubArray(arr), 5, "Q2 fail");

    }

    @Test
    public void TUQ3(){
        Stack<Integer> to_sort = new Stack<Integer>();
        int temp = 0;

        to_sort.push(34);
        to_sort.push(3);
        to_sort.push(31);
        to_sort.push(98);
        to_sort.push(92);
        to_sort.push(23);

        to_sort = Q3.sortStack(to_sort);

        while (to_sort.size() > 1){
            temp = to_sort.pop();
            assertTrue(temp < to_sort.peek(), "Q3 fail");
        }
    }

    @Test
    public void TUQ4(){
        File file = new File("/home/barchik/Mygit/bar.shadkhin/fs/src/co/il/ILRD/DS2Exam/Q4TestFile.text");

        Q4.sortCharsInFiles(file);
    }

//    @Test
//    public void TUQ5(){
//        Q5 tree = new Q5(5);
//
//        tree.insertIteratively(4);
//
//        assertEquals(30, root.left.value);
//
//
//        assertEquals(30, root.left.value);
//        assertEquals(70, root.right.value);
//        assertEquals(20, root.left.left.value);
//        assertEquals(40, root.left.right.value);
//        assertEquals(60, root.right.left.value);
//        assertEquals(80, root.right.right.value);
//
//
//    }

    @Test
    public void TUQ7(){
        String result = Q7.reverseString("Malena");

        assertEquals("anelaM", result, "Q7 fail");

    }

    @Test
    public void TUQ8(){
        Q8.printAllPermutations("BAR");
    }

    @Test
    public void TUQ10(){
        Stack<Integer> to_sort = new Stack<Integer>();
        int temp = 0;

        to_sort.push(34);
        to_sort.push(3);
        to_sort.push(31);
        to_sort.push(98);
        to_sort.push(92);
        to_sort.push(23);

        Q10.sortStack(to_sort);

        while (to_sort.size() > 1){
            temp = to_sort.pop();
            assertTrue(temp < to_sort.peek(), "Q10 fail");
        }
    }

}
