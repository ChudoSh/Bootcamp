package il.co.ILRD.Networking.multiProtocolServer;

import il.co.ILRD.Networking.TCP.TCPServer;
import il.co.ILRD.Networking.UDP.UDPServer;

import java.io.IOException;

public class Hardcoded_mpServer {
    private TCPServer tcps;
    private UDPServer udps;

    public Hardcoded_mpServer(int port) throws IOException {
        this.udps = new UDPServer(port);
        this.tcps = new TCPServer(port);
    }


    public void startServer() {
        new Thread(()->this.udps.run()).start();
        new Thread(()->this.tcps.run()).start();
    }

    public static void main(String[] args) throws IOException, InterruptedException {
        new Hardcoded_mpServer(8080).startServer();
    }
}
