package il.co.ILRD.networking.HttpServer;

import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonReader;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

public class ReadTest implements  Runnable{
    private String address = "localhost";
    private int port = 8989;
    int buffSize = 6000;

    public static void main(String[] args) throws IOException {
        ReadTest test = new ReadTest();
    }

    public ReadTest() {
        try {
            System.out.println("SocketChannel Started : ReadClient");
            System.out.println("SERVER CONNECTED");
        } catch (Exception e) {
            System.out.println(e);
        }
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

    @Override
    public void run() {
        try{
            SocketChannel socketChannel = SocketChannel.open();
            InetSocketAddress serverAddress = new InetSocketAddress(address, port);

            socketChannel.connect(serverAddress);
            System.out.println(socketChannel);
            ByteBuffer byteBuffer = ByteBuffer.allocateDirect(buffSize);

            String[] body = {"Alarm", "Tel Aviv", "Bar", "number", "mail", "85"};
            JsonObject json = Json.createObjectBuilder().add("StartLine",
                            Json.createObjectBuilder().
                                    add("method", "GET/company").
                                    add("URL", "Nice").
                                    add("Version", "some version")).
                    add("Headers", Json.createObjectBuilder().
                            add("ContentType", "application/json").
                            add("ContentLength", 1)).
                    add("Body", Json.createObjectBuilder().
                            add("company_name", body[0]).
                            add("company_address", body[1]).
                            add("contact_name", body[2]).
                            add("contact_phone", body[3]).
                            add("contact_email", body[4]).
                            add("service_fee", Integer.parseInt(body[5])).
                            add("company_id", 1)).build();

            byteBuffer.put(this.write(json));
            byteBuffer.flip();

            socketChannel.write(byteBuffer);

            ByteBuffer message = ByteBuffer.allocate(buffSize);
            socketChannel.read(message);
            message.flip();

            json = this.read(message);
            System.out.println(json.toString());

            socketChannel.close();
        } catch (Exception e){
            e.printStackTrace();
        }

    }
}
