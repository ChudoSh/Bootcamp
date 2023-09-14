package il.co.ILRD.Networking.selector_pingpong;

import il.co.ILRD.Networking.TCP.TCPServer;
import il.co.ILRD.Networking.UDP.UDPServer;

import java.io.*;

public class Server {
    private TCPServer tcps;
    private UDPServer udps;

    public Server(int port) throws IOException {
        this.udps = new UDPServer(port);
        this.tcps = new TCPServer(port);
    }


    public void startServer() throws IOException, InterruptedException {
        new Thread(()->this.udps.run()).start();
        new Thread(()->this.tcps.run()).start();
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        new Server(8080).startServer();
    }
}
