package il.co.ILRD.Quizzes_and_Exams.JavaQuizzes;
import java.util.Map;
import java.util.Objects;

import static java.beans.Beans.isInstanceOf;

import java.util.Comparator;

public class MinMaxPair {

    public static <T extends Comparable<T>> Pair<T, T> findMinMax(T[] array) {
        if (array == null || array.length == 0) {
            return null;
        }

        return findMinMax(array, new Comper<T>());
    }

    public static <T extends Comparable<T>> Pair<T, T> findMinMax(T[] array, Comparator<T> comparator) {
        if (array == null || array.length == 0) {
            return null;
        }

        T min = array[0];
        T max = array[0];

        for(T current : array){
            if (comparator.compare(current, min) < 0) {
                min = current;
            }
            else if (comparator.compare(current, max) > 0) {
                max = current;
            }
        }

        return Pair.of(min, max);
    }

    public static void main(String[] args) {
        Integer[] intArray = {5, 2, 10, 8, 3};
        Map.Entry<Integer, Integer> minMaxEntry = findMinMax(intArray);
        System.out.println("Min: " + minMaxEntry.getKey() + ", Max: " + minMaxEntry.getValue());

        String[] stringArray = {"apple", "banana", "cherry", "date"};
        Map.Entry<String, String> minMaxStringEntry = findMinMax(stringArray, Comparator.reverseOrder());
        System.out.println("Min: " + minMaxStringEntry.getKey() + ", Max: " + minMaxStringEntry.getValue());
    }
}


class Comper<U extends Comparable <U>> implements Comparator<U> {
    @Override
    public int compare(U obj1, U obj2) {
        return obj1.compareTo(obj2);
    }
}
class Pair<K extends Comparable<K>,V> implements Map.Entry<K,V>, Comparable<Pair<K, V>> {
    K key;
    V value;

    private Pair(K key, V value){
        this.key = key;
        this.value = value;
    }

    @Override
    public K getKey() {
        return this.key;
    }

    public void setKey(K key){
        this.key = key;
    }

    @Override
    public V getValue() {
        return this.value;
    }

    @Override
    public V setValue(V value) {
        this.value = value;
        return value;
    }

    @Override
    public boolean equals(Object entry) {
        if (!isInstanceOf(entry, this.getClass())) {
            throw new IllegalArgumentException();
        }
        if (this == entry) {
            return true;
        }
        if (getClass() != entry.getClass()) {
            return false;
        }
        Pair<?, ?> otherPair = (Pair<?, ?>) entry;

        return Objects.equals(this.getKey(), otherPair.getKey());

    }

    @Override
    public int hashCode() {
        return key.hashCode();
    }

    public static <K extends Comparable<K>,V>Pair<K,V> of(K key, V value){
        return new Pair<>(key, value);
    }

    @Override
    public int compareTo(Pair<K, V> kvPair) {
        return this.getKey().compareTo(kvPair.getKey());
    }

}
