/*
Dev: BarSh
Rev: Noga
Status: Approved
Date: 29.8.23
 */
package il.co.ILRD.design_patterns.factory;


import java.util.HashMap;
import java.util.function.Function;

public class Creator<K, D, V> {
    private HashMap<K, Function<D, ? extends V>> typeCreators;

    public Creator() {
        this.typeCreators = new HashMap<>();
    }

    public V create(K key, D data) {
        return typeCreators.get(key).apply(data);
    }

    public V create(K key) {
        return this.create(key, null);
    }

    public void add(K key, Function<D, ? extends V> studentCreate) {
        typeCreators.put(key, studentCreate);
    }
}
