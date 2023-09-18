package il.co.ILRD.Networking.selector_pingpong;

import java.io.IOException;

public class Request {
    private final Response responder;
    private final String message;

    public Request(String message, Response newResponse){
        this.responder = newResponse;
        this.message = message;
    }

    public void parseMessage(){
        System.out.println(this.message);
    }

    public void send(String message) throws IOException {
        this.responder.send(message);
    }
}
