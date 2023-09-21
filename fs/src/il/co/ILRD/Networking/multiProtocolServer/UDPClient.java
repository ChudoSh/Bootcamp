package il.co.ILRD.Networking.multiProtocolServer;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.*;

import static il.co.ILRD.Networking.multiProtocolServer.MultiProtocolServer.*;

public class UDPClient implements Runnable {
    int buffSize = 2048;

    public UDPClient() {
        try {
            System.out.println("DatagramChannel Started : Client");
            System.out.println("SERVER CONNECTED");
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    @Override
    public void run() {
        try {
            // Create a DatagramChannel object.
            DatagramChannel datagramChannel = DatagramChannel.open();

            // Connect the SocketChannel to the server.
            //socketChannel.connect(serverAddress);
            InetSocketAddress serverAddress = new InetSocketAddress("localhost",9898);
            datagramChannel.connect(serverAddress);

            for (int i = 0; i < 3; ++i) {

                // Create a ByteBuffer object to store the data you want to send.
                ByteBuffer byteBuffer = ByteBuffer.allocateDirect(buffSize);

                // Write the data to the ByteBuffer object.
                byteBuffer.put(MultiProtocolServer.serialize(new myPing()));
                byteBuffer.flip();
                // Write the ByteBuffer object to the SocketChannel.
                datagramChannel.write(byteBuffer);

                ByteBuffer massage = ByteBuffer.allocate(buffSize);

                System.out.println(datagramChannel.read(massage));
                massage.flip();
                Message<?, ?> message = MultiProtocolServer.deserialize(massage);
                System.out.println(message.getData());
            }
            datagramChannel.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

    }

    public static class myPing implements MultiProtocolServer.Message<MultiProtocolServer.MessageProtocol, String> {

        public myPing() {
        }

        @Override
        public MultiProtocolServer.MessageProtocol getKey() {
            return MultiProtocolServer.MessageProtocol.PING_PONG;
        }

        @Override
        public String getData() {
            return "Ping";
        }
    }

    public static void main(String[] args) throws IOException {
        new Thread(new UDPClient()).start();
    }
}
