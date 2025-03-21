package il.co.ILRD.networking.HttpServer.Tests;

import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonReader;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

public class CreateTest implements Runnable {
    private int buffSize = 6000;
    private String address = "localhost";
    private int port = 9797;

    public static void main(String[] args) throws IOException {
        CreateTest test = new CreateTest();
        test.run();
    }

    public CreateTest() {
    }

    private ByteBuffer write(JsonObject json) {
        if (json.isNull("StartLine") || json.isNull("Body") || json.isNull("Headers")) {
            return null;
        }

        return ByteBuffer.wrap(json.toString().getBytes());
    }

    private JsonObject read(ByteBuffer buffer) {
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
        try {
            SocketChannel socketChannel = SocketChannel.open();
            InetSocketAddress serverAddress = new InetSocketAddress(this.address, this.port);
            socketChannel.connect(serverAddress);
            System.out.println(socketChannel);
            ByteBuffer byteBuffer = ByteBuffer.allocateDirect(buffSize);

            String[] body = {"Naairco", "TelAviv", "Bar", "number", "mail", "85", "Banknumber345", "barchik", "28/9/2344", "000"};
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
                            add("service_fee", body[5]).
                            add("card_number", body[6]).
                            add("card_holder_name", body[7]).
                            add("ex_date", body[8]).
                            add("CVV", body[9])).build();

            byteBuffer.put(this.write(json));
            byteBuffer.flip();

            socketChannel.write(byteBuffer);

            ByteBuffer message = ByteBuffer.allocate(buffSize);
            socketChannel.read(message);
            message.flip();

            json = this.read(message);
            System.out.println(json.toString());

            socketChannel.close();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

    }
}
