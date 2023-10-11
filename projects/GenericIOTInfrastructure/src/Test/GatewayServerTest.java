package Test;

import GatewayServer.GatewayServer;

import java.io.IOException;

public class GatewayServerTest {
    public static void main(String[] args) throws IOException, ClassNotFoundException {
        GatewayServer server = new GatewayServer(4);
    }
}
