package il.co.ILRD.networking.HttpServer.Tests;



import com.sun.media.sound.InvalidDataException;
import il.co.ILRD.networking.HttpServer.HttpServer;

import java.io.IOException;

public class HttpServerTest {
    public static void main(String[] args) throws IOException, InvalidDataException {
         HttpServer server = new HttpServer(4);
         server.start();
    }
}
