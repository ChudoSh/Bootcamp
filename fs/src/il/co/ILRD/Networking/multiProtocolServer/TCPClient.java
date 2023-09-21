package il.co.ILRD.Networking.multiProtocolServer;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

import static il.co.ILRD.Networking.multiProtocolServer.MultiProtocolServer.*;

public class TCPClient {
    int bufSize = 2048;

    public static void main(String[] args) throws IOException {
        new TCPClient().ClientChat("localhost", 8989);
        new TCPClient().ClientChat("localhost", 8990);
        new TCPClient().ClientChat("localhost", 8991);
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
        ByteBuffer byteBuffer = ByteBuffer.allocateDirect(bufSize);

        // Write the data to the ByteBuffer object.
        byteBuffer.put(MultiProtocolServer.serialize(new myPing()));
        byteBuffer.flip();

        // Write the ByteBuffer object to the SocketChannel.
        socketChannel.write(byteBuffer);

        ByteBuffer massage = ByteBuffer.allocate(bufSize);

        System.out.println(socketChannel.read(massage));
        massage.flip();
        Message<?, ?> message = MultiProtocolServer.deserialize(massage);
        System.out.println(message.getData());

        socketChannel.close();

    }

    public static class myPing implements Message<MessageProtocol, String> {

        public myPing() {
        }

        @Override
        public MessageProtocol getKey() {
            return MessageProtocol.PING_PONG;
        }

        @Override
        public String getData() {
            return "Ping";
        }
    }
}
