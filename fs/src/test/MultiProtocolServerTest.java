package test;

import il.co.ILRD.Networking.multiProtocolServer.MultiProtocolServer;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.io.IOException;

import static org.junit.jupiter.api.Assertions.*;

public class MultiProtocolServerTest {
    public MultiProtocolServer server;

    @BeforeEach
    void init() throws IOException {
        this.server = new MultiProtocolServer();
    }

    @Test
    void TU_add() throws IOException {
        this.server.addUDPConnection(9898);
        this.server.addTCPConnection(8989);
        this.server.start();
    }
}
