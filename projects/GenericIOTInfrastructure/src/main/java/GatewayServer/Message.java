package main.java.GatewayServer;

import java.io.Serializable;

public interface Message<K, D extends Serializable> extends Serializable{
    K getKey();
    D getData();
}
