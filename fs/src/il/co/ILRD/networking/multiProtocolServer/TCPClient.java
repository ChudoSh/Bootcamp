package il.co.ILRD.networking.multiProtocolServer;

import il.co.ILRD.networking.GatewayServer.GatewayServer;
import il.co.ILRD.networking.HttpServer.HttpServer;

import javax.crypto.spec.PSource;
import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;
import javax.json.JsonReader;
import java.io.*;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

import static il.co.ILRD.networking.multiProtocolServer.MultiProtocolServer.*;

public class TCPClient {
    int buffSize = 6000;

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
        String[] body = {"Alarm", "Tel Aviv", "Bar", "number", "mail", "number"};
        JsonObject json = Json.createObjectBuilder().add("StartLine",
                        Json.createObjectBuilder().
                                add("method", "POST/company").
                                add("URL", "Nice").
                                add("Version", "some version")).
                add("Headers", Json.createObjectBuilder().
                        add("ContentType", "application/json").
                        add("ContentLength", body.length)).
                add("Body", Json.createObjectBuilder().
                        add("company_name", body[0]).
                        add("company_address", body[1]).
                        add("contact_name", body[2]).
                        add("contact_phone", body[3]).
                        add("contact_email", body[4]).
                        add("service_fee", body[5])).build();

        byteBuffer.put(this.write(json));
        byteBuffer.flip();

        // Write the ByteBuffer object to the SocketChannel.
        socketChannel.write(byteBuffer);

        ByteBuffer message = ByteBuffer.allocate(buffSize);
        socketChannel.read(message);
        message.flip();

        json = this.read(message);
        System.out.println(json.toString());

        socketChannel.close();
    }

    public ByteBuffer write(JsonObject json) {
        if (json.isNull("StartLine") || json.isNull("Body") || json.isNull("Headers")) {
            return null;
        }

        return ByteBuffer.wrap(json.toString().getBytes());
    }

    public JsonObject read(ByteBuffer buffer) {
        if (null == buffer) {
            return null;
        }

        JsonReader reader = Json.createReader(new ByteArrayInputStream(buffer.array()));
        JsonObject json = reader.readObject();
        reader.close();

        return json;
    }
}
