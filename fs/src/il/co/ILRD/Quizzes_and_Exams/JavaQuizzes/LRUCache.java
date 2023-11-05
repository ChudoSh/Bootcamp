package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;

import java.util.*;

public class LRUCache<K, V> {
    private final List<K> lruOrder;
    private final Map<K, V> map;
    private final int maxCapacity;
    private int size;

    public LRUCache(int maxCapacity) {
        assert maxCapacity != 0;

        this.map = new HashMap<>();
        this.lruOrder = new ArrayList<>();
        this.maxCapacity = maxCapacity;
    }

    public void put(K key, V value) {
        ++this.size;

        if (this.size > this.maxCapacity) {
            this.map.remove(this.lruOrder.remove(this.maxCapacity - 1));
        }

        this.map.put(key, value);
        this.lruOrder.add(key);
    }

    public V get(K key) {
        if (!map.containsKey(key)) {
            return null;
        }

        this.lruOrder.remove(maxCapacity - 1);
        this.lruOrder.add(key);

        return this.map.get(key);
    }
}
