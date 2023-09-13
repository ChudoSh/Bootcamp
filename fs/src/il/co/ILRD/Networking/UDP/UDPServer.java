package il.co.ILRD.Networking.UDP;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;

public class UDPServer {
    public static void main(String[] args) throws IOException {
        new UDPServer(12345);
    }

    private final DatagramSocket datagramSocket;

    public UDPServer(int port) throws IOException {
        this.datagramSocket = new DatagramSocket(port);

        try {
            System.out.println("DatagramSocket Started : Server");
            System.out.println(this.datagramSocket);
            System.out.println("CLIENT CONNECTED");
            chatServer();
        } catch (Exception e) {
            System.out.println(e);
        } finally {
            datagramSocket.close();
        }

    }

    public void chatServer() {
        DatagramPacket sendPacket;
        DatagramPacket receivePacket;
        byte[] buffer;
        String str;

        while (true) {
            buffer = new byte[1024];
            receivePacket = new DatagramPacket(buffer, buffer.length);
            try {
                datagramSocket.receive(receivePacket);
                str = new String(buffer, 0, receivePacket.getLength());
                System.out.println("Message from Client:" + str);

                System.out.println("Please insert message:");
                BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
                str = reader.readLine();

                if (str.equals("bye")) {
                    break;
                }

                buffer = str.getBytes();
                sendPacket = new DatagramPacket(buffer, buffer.length, receivePacket.getAddress(), receivePacket.getPort());
                datagramSocket.send(sendPacket);
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            System.out.println("Message sent");
        }
    }
}