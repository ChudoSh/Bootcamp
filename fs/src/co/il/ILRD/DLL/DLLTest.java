package co.il.ILRD.DLL;


import org.junit.jupiter.api.Test;

import java.util.Iterator;

import static org.junit.jupiter.api.Assertions.*;
import static org.junit.jupiter.api.Assertions.assertEquals;

public class DLLTest {

    @Test
    public void TUPush(){
        DLL<Integer> dlist = new DLL<>();
        dlist.pushFront(3);
        dlist.pushFront(4);
        dlist.pushFront(5);
        dlist.pushFront(6);

    }

    @Test
    public void TUCount(){
        DLL<Integer> dlist = new DLL<>();
        assertTrue(dlist.isEmpty(), "Count Fail");
        dlist.pushFront(3);
        dlist.pushFront(4);
        dlist.pushFront(5);
        dlist.pushFront(6);
        assertEquals(4, dlist.count(), "Count Fail");
    }

    @Test
    public void TUFind(){
        DLL<Integer> dlist = new DLL<>();
        Iterator<Integer> toFind;
        Integer three = 3;

        dlist.pushFront(new Integer(4));
        dlist.pushFront(new Integer(5));
        dlist.pushFront(new Integer(6));
        dlist.pushFront(new Integer(3));

        toFind = dlist.find(three);
        assertEquals(three ,toFind.next(), "Find Fail");
        assertEquals(4, dlist.count(), "Size Fail");
    }

    @Test
    public void TUMerge(){
        DLL<Integer> dest = new DLL<>();
        DLL<Integer> src = new DLL<>();

        src.pushFront(new Integer(6));
        src.pushFront(new Integer(5));
        src.pushFront(new Integer(4));
        src.pushFront(new Integer(3));

        dest.pushFront(new Integer(2));
        dest.pushFront(new Integer(1));

        DLL.merge(dest, src);

        assertEquals(6 ,dest.count(), "Merge Fail");
        assertTrue(src.isEmpty(), "Merge Fail");
    }

    @Test
    public void TUPop(){
        DLL<Integer> dlist = new DLL<>();
        Integer six = 6;

        dlist.pushFront(3);
        dlist.pushFront(4);
        dlist.pushFront(5);
        dlist.pushFront(6);
        assertEquals(six,dlist.popFront(), "Pop Fail");
        assertEquals(3, dlist.count(), "Size Fail");
    }

    @Test
    public void TUPrint(){
        DLL<Integer> dlist = new DLL<>();
        Integer six = 6;

        dlist.pushFront(3);
        dlist.pushFront(4);
        dlist.pushFront(5);
        dlist.pushFront(6);
        dlist.printDList();
    }
}
