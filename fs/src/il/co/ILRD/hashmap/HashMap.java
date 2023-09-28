/*
dev : barSh
rev : amitaiB
date : 22.8.23
status : approved
 */
package il.co.ILRD.hashmap;

import com.sun.istack.internal.NotNull;

import java.util.*;

public class HashMap<K extends Comparable<K>, V> implements Map<K, V> {
    private List<Collection<Entry<K, V>>> listOfBuckets;
    private EntrySet entrySet;
    private KeySet keySet;
    private ValueCollection valueCollection;
    private int capacity;
    private double loadFactor;
    private int expectedModCounter;
    private static final int defaultCapacity = 150; //default value 150 values
    private static final double defaultLoadFactor = 0.8;//default value is 0.8private final int toTreeFactor = 10;
    private static final int toTreeFactor = 2;

    public HashMap() {
        this(defaultCapacity,defaultLoadFactor);
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
        return this.valueCollection.contains(value);
    }

    @Override
    public V get(@NotNull Object key) {
        int index = getHashCode(key);

        if (null == listOfBuckets.get(index)) {
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
}