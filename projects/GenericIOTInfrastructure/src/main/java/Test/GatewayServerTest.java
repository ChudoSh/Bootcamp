package Test;

import GatewayServer.GatewayServer;

import java.io.IOException;

public class GatewayServerTest {
    public static void main(String[] args) throws IOException{
        GatewayServer server = new GatewayServer(4);
        server.start();
    }
}
