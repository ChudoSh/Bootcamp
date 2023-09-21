package il.co.ILRD.Networking.hardcoded_mps.UDP;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class UDPClient {
    public static void main(String[] args) throws IOException {
        new UDPClient(9898, "localhost");
    }

    private final DatagramSocket datagramSocket;
    private final int port;
    private final String ipName;

    public UDPClient(int port, String ipName) throws IOException {
        this.datagramSocket = new DatagramSocket();
        this.port = port;
        this.ipName = ipName;

        System.out.println("DatagramSocket Started : Client");
        System.out.println(datagramSocket);
        System.out.println("SERVER CONNECTED");
        System.out.println("Type 'bye' to exit");
        chatClient();
    }

    private void chatClient() {
        DatagramPacket receivePacket;
        DatagramPacket sendPacket;
        byte[] buffer;
        String str;

        while (true) {
            try {
                System.out.println("Please insert message:");
                BufferedReader reader = new BufferedReader(
                        new InputStreamReader(System.in));
                str = reader.readLine();

                if (str.equals("bye")) {
                    System.out.println("Chat is over");
                    break;
                }

                buffer = str.getBytes();
                InetAddress address = InetAddress.getByName(this.ipName);
                sendPacket = new DatagramPacket(buffer, buffer.length,
                       address , this.port);
                this.datagramSocket.send(sendPacket);
                System.out.println("Message sent");

                buffer = new byte[1024];
                receivePacket = new DatagramPacket(buffer, buffer.length);
                datagramSocket.receive(receivePacket);
                str = new String(buffer, 0, receivePacket.getLength());
                System.out.println("Message from Server:" + str);
            } catch (Exception e) {
                datagramSocket.close();
                throw new RuntimeException();
            }
        }
        datagramSocket.close();
    }
}
