package il.co.ILRD.Networking.UDP;

import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.nio.charset.StandardCharsets;

public class UDPClient {
    private DatagramSocket datagramSocket;
    private int port;

    public UDPClient(int port) throws IOException {
        this.datagramSocket = new DatagramSocket();
        this.port = port;


        try {
            System.out.println("DatagramSocket Started : Client");
            System.out.println(datagramSocket);
            System.out.println("SERVER CONNECTED");
            chatClient();
            datagramSocket.close();
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    private void chatClient() throws IOException {
        DatagramPacket receivePacket;
        DatagramPacket sendPacket;
        byte[] buffer;
        String str = null;

        while (true) {
            System.out.println("Please insert message:");
            BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
            str = reader.readLine();

            if (str.equals("bye")) {
                System.out.println("Chat is over");
                break;
            }

            buffer = str.getBytes();
            sendPacket = new DatagramPacket(buffer,buffer.length,InetAddress.getLocalHost(),this.port);
            this.datagramSocket.send(sendPacket);
            System.out.println("Message sent");

            buffer = new byte[1024];
            receivePacket = new DatagramPacket(buffer, buffer.length);
            datagramSocket.receive(receivePacket);
            str = new String(buffer, 0, receivePacket.getLength());
            System.out.println("Message from Server:" + str);
        }
    }

    public static void main(String[] args) throws IOException {
        new UDPClient(1234);
    }
}
