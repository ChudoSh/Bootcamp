package co.il.ILRD.SLL;


import org.junit.Before;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;
import static org.junit.jupiter.api.Assertions.*;

public class linkListTest {

    @Test
    public void Test_isEmpty(){
        LinkList list = new LinkList();
        assertTrue(list.isEmpty(), " Is Empty Fail");
        list.pushFront(new Integer(3));
        list.pushFront(new Integer(4));
        list.pushFront(new Integer(5));
        list.pushFront(new Integer(6));
        assertFalse(list.isEmpty(), " Is Empty Fail");
    }

    @Test
    public void Test_SizeNPush(){
        LinkList list = new LinkList();
        assertTrue(0 == list.Size(), "Size Fail");
        list.pushFront(new Integer(3));
        list.pushFront(new Integer(4));
        list.pushFront(new Integer(5));
        list.pushFront(new Integer(6));
        assertTrue(4 == list.Size(), "Size Fail");
    }

    @Test
    public void Test_Find(){
        LinkList list = new LinkList();
        ListIterator toFind;
        Integer three = 3;

        list.pushFront(new Integer(4));
        list.pushFront(new Integer(5));
        list.pushFront(new Integer(6));
        list.pushFront(new Integer(3));

        toFind = list.Find(three);
        assertEquals(three ,toFind.Next(), "Find Fail");
        assertTrue(4 == list.Size(), "Size Fail");
    }

    @Test
    public void Test_Begin(){
        LinkList list = new LinkList();
        Integer three = 6;

        list.pushFront(three);
        list.pushFront(new Integer(4));
        list.pushFront(new Integer(5));
        list.pushFront(new Integer(6));
        assertEquals(three, list.Begin().Next() , "Begin Fail");
        assertTrue(4 == list.Size(), "Size Fail");
    }

    @Test
    public void Test_Pop(){
        LinkList list = new LinkList();
        Integer six = 6;

        list.pushFront(3);
        list.pushFront(4);
        list.pushFront(5);
        list.pushFront(6);
        assertEquals(six,list.popFront(), "Pop Fail");
        assertTrue(3 == list.Size(), "Size Fail");
    }
}