package il.co.ILRD.Networking.multiProtocolServer;

import java.io.Serializable;

public class PingPongMessage<K, D extends Serializable> implements MultiProtocolServer.Message<K, D> {
    private final K key;
    private final D data;

    public PingPongMessage(K key, D data) {
        this.key = key;
        this.data = data;
    }

    @Override
    public K getKey() {
        return this.key;
    }

    @Override
    public D getData() {
        return this.data;
    }
}
