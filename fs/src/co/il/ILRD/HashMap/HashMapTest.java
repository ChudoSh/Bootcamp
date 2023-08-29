package co.il.ILRD.HashMap;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.*;

public class HashMapTest {
    HashMap<Integer, String> hashMap;

    @BeforeEach
    public void Init() {
        hashMap = new HashMap<>();
    }


    @Test
    public void TUIsEmpty() {
        assertNotNull(hashMap, "Create fail");
        assertTrue(hashMap.isEmpty(), "isEmpty fail");
    }

    @Test
    public void TUPut() {
        hashMap = new HashMap<>(200, 0.6);

        assertNotNull(hashMap, "Create fail");
        assertTrue(hashMap.isEmpty(), "isEmpty fail");

        assertEquals("History", hashMap.put(85, "History"), "put fails");
        assertEquals("Math", hashMap.put(78, "Math"), "put fails");
        assertEquals("Computers", hashMap.put(80, "Computers"), "put fails");
        assertEquals("Arts", hashMap.put(70, "Arts"), "put fails");
        assertEquals("Sports", hashMap.put(100, "Sports"), "put fails");
        assertEquals("Literature", hashMap.put(55, "Literature"), "put fails");
        assertEquals("History", hashMap.put(65, "History"), "put fails");
        assertEquals("History", hashMap.get(65), "get fails");

    }

    @Test
    public void TURemove() {
        hashMap = new HashMap<>(200, 0.6);

        assertEquals("History", hashMap.put(85, "History"), "put fails");
        assertEquals("Math", hashMap.put(78, "Math"), "put fails");
        assertEquals("Computers", hashMap.put(80, "Computers"), "put fails");
        assertEquals("Arts", hashMap.put(70, "Arts"), "put fails");
        assertEquals("Sports", hashMap.put(100, "Sports"), "put fails");
        assertEquals("Literature", hashMap.put(55, "Literature"), "put fails");

        assertEquals(6, hashMap.size());

        assertEquals("Arts", hashMap.remove(70), "remove fail");
    }

    @Test
    public void TUGet() {
        hashMap = new HashMap<>(200, 0.6);

        assertEquals("History", hashMap.put(85, "History"), "put fails");
        assertEquals("Math", hashMap.put(78, "Math"), "put fails");
        assertEquals("Computers", hashMap.put(80, "Computers"), "put fails");
        assertEquals("Arts", hashMap.put(70, "Arts"), "put fails");
        assertEquals("Sports", hashMap.put(100, "Sports"), "put fails");
        assertEquals("Literature", hashMap.put(55, "Literature"), "put fails");

        assertEquals(6, hashMap.size());

        assertEquals("Arts", hashMap.get(70), "get fail");
    }

    @Test
    public void TUClear() {
        hashMap = new HashMap<>(200, 0.6);

        assertEquals("History", hashMap.put(85, "History"), "put fails");
        assertEquals("Math", hashMap.put(78, "Math"), "put fails");
        assertEquals("Computers", hashMap.put(80, "Computers"), "put fails");
        assertEquals("Arts", hashMap.put(70, "Arts"), "put fails");
        assertEquals("Sports", hashMap.put(100, "Sports"), "put fails");
        assertEquals("Literature", hashMap.put(55, "Literature"), "put fails");

        hashMap.clear();
        assertTrue(hashMap.isEmpty(), "clear fail");

    }

    @Test
    public void TU_putAll() {
        hashMap = new HashMap<>(1, 0.6);
        HashMap<Integer, String> secondHashmap = new HashMap<>(10, 0.9);

        for (int i = 0; i < 10; ++i){
            secondHashmap.put(i, i + "Something");
        }

        assertEquals(10, secondHashmap.size(), "put fail");

        hashMap.putAll(secondHashmap);
        assertEquals(10, hashMap.size(), "putAll fails");
    }
}
