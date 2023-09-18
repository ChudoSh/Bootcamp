package il.co.ILRD.Networking.multiProtocolServer;

public enum Protocol {
    PINGPONG(1),
    CHAT(2);

    private int protocol;

    private Protocol(int protocol) {
        this.protocol = protocol;
    }
}
