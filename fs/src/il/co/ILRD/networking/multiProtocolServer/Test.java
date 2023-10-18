package il.co.ILRD.networking.multiProtocolServer;

import org.junit.jupiter.api.BeforeEach;

import java.io.IOException;

public class Test {
    public MultiProtocolServer server;

    @BeforeEach
    void init() throws IOException {
        this.server = new MultiProtocolServer();
        this.server.start();
    }
}
