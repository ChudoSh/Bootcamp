/*
dev : barSh
rev : amitaiB
date : 22.8.23
status : approved
 */
package main.java.hashmap;

import java.util.Map;

public class Pair<K extends Comparable<K>, V> implements Map.Entry<K, V>, Comparable<K> {
    private K key;
    private V value;

    @Override
    public K getKey() {
        return key;
    }

    @Override
    public V getValue() {
        return value;
    }

    @Override
    public V setValue(V v) {
        V current = this.value;
        this.value = v;
        return current;
    }

    @Override
    public int hashCode() {
        return key.hashCode();
    }

    private Pair(K key, V value) {
        this.key = key;
        this.value = value;
    }

    public void setKey(K key) {
        this.key = key;
    }

    @Override
    public boolean equals(Object entry) {
        if (this == entry){
            return true;
        }

        if (null == entry){
            return false;
        }

        if (entry instanceof Pair){
            return this.key.equals(((Pair<?, ?>) entry).getKey())
                    && this.value.equals(((Pair<?, ?>) entry).getValue());

        }

        return false;
    }

    public static <K extends Comparable<K>, V> Pair<K, V> of(K key, V value) {
        return new Pair<>(key, value);
    }

    @Override
    public int compareTo(K key) {
        return key.compareTo(this.key);
    }
}
