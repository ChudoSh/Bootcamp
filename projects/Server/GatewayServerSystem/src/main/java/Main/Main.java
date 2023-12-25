package Main;

import gateway_server.GatewayServer;

import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException{
        GatewayServer server = new GatewayServer();
        server.start();
    }
}
