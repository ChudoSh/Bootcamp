/*
dev : barSh
rev : amitaiB
date : 22.8.23
status : approved
 */
package co.il.ILRD.HashMap;

import com.sun.istack.internal.NotNull;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.util.*;

import static org.junit.jupiter.api.Assertions.*;

public class HashMap<K extends Comparable<K>, V> implements Map<K, V> {
    private List<Collection<Entry<K, V>>> listOfBuckets;
    private EntrySet entrySet;
    private KeySet keySet;
    private ValueCollection valueCollection;
    private int capacity; //default value 150 values
    private double loadFactor;//default value is 0.8
    private int expectedModCounter;
    private final int toTreeFactor = 10;

    public HashMap() {
        this(150, 0.8);
    }

    public HashMap(int capacity) {
        this(capacity, 0.8);
    }

    public HashMap(double loadFactor) {
        this(150, loadFactor);
    }

    public HashMap(int capacity, double loadFactor) {
        this.capacity = capacity;
        this.loadFactor = loadFactor;
        this.listOfBuckets = new ArrayList<>(Collections.nCopies(capacity, null));
        this.entrySet = new EntrySet();
        this.keySet = new KeySet();
        this.valueCollection = new ValueCollection();
    }

    @Override
    public int size() {
        int size = 0;

        for (Collection<Entry<K, V>> bucket : this.listOfBuckets) {
            if (null != bucket) {
                size += bucket.size();
            }
        }
        return size;
    }

    @Override
    public boolean isEmpty() {
        return (0 == this.size());
    }

    @Override
    public boolean containsKey(@NotNull Object key) {
        if (null == listOfBuckets.get(getHashCode(key))) {
            return false;
        }

        for (K toFind : keySet) {
            if (key.equals(toFind)) {
                return true;
            }
        }
        return false;
    }

    @Override
    public boolean containsValue(@NotNull Object value) {
        for (V toFind : this.valueCollection) {
            if (value.equals(toFind)) {
                return true;
            }
        }

        return false;
    }

    @Override
    public V get(@NotNull Object key) {
        int index = getHashCode(key);

        if (this.isEmpty() || null == listOfBuckets.get(index)) {
            return null;
        }

        for (Entry<K, V> checker : listOfBuckets.get(index)) {
            if (key.equals(checker.getKey())) {
                return checker.getValue();
            }
        }

        return null;
    }

    @Override
    public V put(@NotNull K key, V value) {
        V toReturn = value;

        if (this.containsKey(key)) {
            toReturn = this.remove(key);
        }

        int index = getHashCode(key);

        if (null == listOfBuckets.get(index)){
            listOfBuckets.set(index, new ArrayList<>());
        }

        Collection<Entry<K, V>> bucket = listOfBuckets.get(index);
        Entry<K, V> pairToPut = Pair.of(key, value);
        bucket.add(pairToPut);
        ++this.expectedModCounter;
        this.toListOrTree(index);
        this.toResizeCapacity();

        return toReturn;
    }

    @Override
    public V remove(@NotNull Object key) {
        int index = getHashCode(key);
        Collection<Entry<K, V>> currentBucket = listOfBuckets.get(index);

        if (null == currentBucket) {
            return null;
        }

        for (Entry<K, V> checker : listOfBuckets.get(index)) {
            if (key.equals(checker.getKey())) {
                V toReturn = checker.getValue();
                currentBucket.remove(checker);
                ++this.expectedModCounter;
                this.toListOrTree(index);

                return toReturn;
            }
        }

        return null;
    }

    @Override
    public void putAll(@NotNull Map<? extends K, ? extends V> map) {
        for (Entry<? extends K, ? extends V> entry : map.entrySet()) {
            this.put(entry.getKey(), entry.getValue());
        }
    }


    @Override
    public void clear() {
        for (Collection<Entry<K, V>> toRemove : listOfBuckets) {
            if (null != toRemove) {
                toRemove.clear();
            }
        }
    }

    @Override
    public Set<K> keySet() {
        return this.keySet;
    }

    @Override
    public Collection<V> values() {
        return this.valueCollection;
    }

    @Override
    public Set<Entry<K, V>> entrySet() {
        return this.entrySet;

    }

    private class EntrySet extends AbstractSet<Entry<K, V>> {

        @Override
        public @NotNull Iterator<Entry<K, V>> iterator() {
            return new EntryIterator();
        }

        @Override
        public int size() {
            int counter = 0;
            for (Entry<K, V> ignored : this) {
                ++counter;
            }
            return counter;
        }

        private class EntryIterator implements Iterator<Entry<K, V>> {

            private final Iterator<Collection<Entry<K, V>>> listIterator;
            private final int currentModCounter;
            private Iterator<Entry<K, V>> bucketIterator;


            private EntryIterator() {
                listIterator = HashMap.this.listOfBuckets.iterator();
                this.currentModCounter = HashMap.this.expectedModCounter;
            }

            @Override
            public boolean hasNext() {
                if (currentModCounter != HashMap.this.expectedModCounter) {
                    throw new ConcurrentModificationException();
                }

                if (null != bucketIterator && bucketIterator.hasNext()) {
                    return true;
                }

                while (listIterator.hasNext()) {
                    Collection<Entry<K, V>> bucket = listIterator.next();
                    if (null == bucket) {
                        continue;
                    }

                    bucketIterator = bucket.iterator();

                    if (bucketIterator.hasNext()) {
                        return true;
                    }
                }

                if (null == bucketIterator) {
                    return false;
                }

                return bucketIterator.hasNext();
            }

            @Override
            public Entry<K, V> next() {
                if (currentModCounter != HashMap.this.expectedModCounter) {
                    throw new ConcurrentModificationException();
                }

                return bucketIterator.next();
            }
        }
    }
    private class KeySet extends AbstractSet<K> {

        @Override
        public Iterator<K> iterator() {
            return new KeyIterator();
        }

        @Override
        public int size() {
            return entrySet.size();
        }

        private class KeyIterator implements Iterator<K> {
            Iterator<Entry<K, V>> iterator = entrySet.iterator();

            @Override
            public boolean hasNext() {
                return iterator.hasNext();
            }

            @Override
            public K next() {
                return iterator.next().getKey();
            }
        }
    }

    private class ValueCollection extends AbstractCollection<V> {

        @Override
        public Iterator<V> iterator() {
            return new ValueIterator();
        }

        @Override
        public int size() {
            return entrySet.size();
        }

        private class ValueIterator implements Iterator<V> {

            Iterator<Entry<K, V>> iterator = entrySet.iterator();

            @Override
            public boolean hasNext() {
                return iterator.hasNext();
            }

            @Override
            public V next() {
                return iterator.next().getValue();
            }
        }
    }

    //=============================private methods==============================
    private int getHashCode(Object key) { //add type safety check
        return Math.abs(key.hashCode()) % this.capacity;
    }

    private void toResizeCapacity() {
        if (((double) (this.size()) / this.capacity) >= loadFactor) {
            List<Collection<Entry<K, V>>> newListOfBuckets = new ArrayList<>(Collections.nCopies((this.capacity * 2), null));
            int i = 0;

            for (Collection<Entry<K, V>> bucket : this.listOfBuckets) {
                if (null != bucket) {
                    newListOfBuckets.set(i, bucket);
                }
                ++i;
            }

            this.listOfBuckets = newListOfBuckets;
        }
    }

    private void toListOrTree(int index) {
        Collection<Entry<K, V>> bucket = listOfBuckets.get(index);

        if ((double) (bucket.size() / this.capacity) >= toTreeFactor && !(bucket instanceof TreeSet)) {
            listOfBuckets.set(index, new TreeSet<>(bucket));
            System.out.println("Switched to Tree");
        } else if (((double) (bucket.size() / this.capacity) < toTreeFactor && !(bucket instanceof List))) {
            listOfBuckets.set(index, new ArrayList<>(bucket));
            System.out.println("Switched to List");
        }
    }

    public static class HashMapTest {
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
}