package il.co.ILRD.Networking.UDP;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.nio.charset.StandardCharsets;

public class UDPServer {
    private DatagramSocket datagramSocket;
    private int port;

    public UDPServer(int port) throws IOException {
        this.datagramSocket = new DatagramSocket(port);
        this.port = port;


        try {
            System.out.println("DatagramSocket Started : Server");
            System.out.println(this.datagramSocket);
            System.out.println("CLIENT CONNECTED");
            chatServer();
            datagramSocket.close();
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    private void chatServer() throws IOException {
        DatagramPacket sendPacket;
        DatagramPacket receivePacket;
        byte[] buffer;
        String str = null;

        while (true) {
            System.out.println("Please insert message:");
            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
            str = reader.readLine();

            if (str.equals("bye")) {
                break;
            }

            buffer = new byte[100];
            receivePacket = new DatagramPacket(buffer, buffer.length);
            datagramSocket.receive(receivePacket);
            str = new String(buffer, 0, receivePacket.getLength());
            System.out.println("Message from Client:" + str);

            buffer = str.getBytes();
            sendPacket = new DatagramPacket(buffer, buffer.length, receivePacket.getAddress(), receivePacket.getPort());
            datagramSocket.send(sendPacket);
            System.out.println("Message sent");

        }
    }

    public static void main(String[] args) throws IOException {
        new UDPServer(1234);
    }
}
