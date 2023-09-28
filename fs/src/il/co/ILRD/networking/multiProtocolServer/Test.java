package il.co.ILRD.networking.multiProtocolServer;

import org.junit.jupiter.api.BeforeEach;

import java.io.IOException;

public class Test {
    public MultiProtocolServer server;

    @BeforeEach
    void init() throws IOException {
        this.server = new MultiProtocolServer();
    }

    @org.junit.jupiter.api.Test
    void TU_add() throws IOException {
        this.server.addUDPConnection(9898);
        this.server.addTCPConnection(8989);
        this.server.start();
    }
}
