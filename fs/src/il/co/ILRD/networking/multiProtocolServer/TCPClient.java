package il.co.ILRD.networking.multiProtocolServer;

import javax.crypto.spec.PSource;
import java.io.*;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

import static il.co.ILRD.networking.multiProtocolServer.MultiProtocolServer.*;

public class TCPClient {
    int buffSize = 2048;

    public static void main(String[] args) throws IOException {
        new TCPClient().ClientChat("localhost", 8989);
    }

    public TCPClient() {
        try {
            System.out.println("SocketChannel Started : Client");
            System.out.println("SERVER CONNECTED");
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public void ClientChat(String ipAddress, int port) throws IOException {
        // Create a SocketChannel object.
        SocketChannel socketChannel = SocketChannel.open();


        // Connect the SocketChannel to the server.
        InetSocketAddress serverAddress = new InetSocketAddress(ipAddress, port);
        socketChannel.connect(serverAddress);
        System.out.println(socketChannel);
        // Create a ByteBuffer object to store the data you want to send.
        ByteBuffer byteBuffer = ByteBuffer.allocateDirect(buffSize);

        // Write the data to the ByteBuffer object.
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String request = br.readLine();
        byteBuffer.put(request.getBytes());
        byteBuffer.flip();

        // Write the ByteBuffer object to the SocketChannel.
        socketChannel.write(byteBuffer);

        ByteBuffer message = ByteBuffer.allocate(buffSize);
        socketChannel.read(message);
        message.flip();

        System.out.println(new String(message.array()));

        socketChannel.close();
    }
}
