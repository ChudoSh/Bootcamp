package il.co.ILRD.Networking.selector_pingpong;

import java.io.DataOutputStream;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.Socket;

public interface Response {
    void send(String message) throws IOException;
}

class TCPResponse implements Response {
    private Socket socket;

    public TCPResponse(Socket socket) {
        this.socket = socket;
    }

    @Override
    public void send(String message) throws IOException {
        DataOutputStream dos = new DataOutputStream(this.socket.getOutputStream());
        dos.write(message.getBytes());
        dos.flush();
    }
}

class UDPResponse implements Response {
    private DatagramPacket packet;

    public UDPResponse(DatagramPacket packet) {
        this.packet = packet;
    }

    @Override
    public void send(String message) throws IOException {
        DatagramPacket toSend = new DatagramPacket(message.getBytes(), message.getBytes().length,
                this.packet.getAddress(), this.packet.getPort());
    }
}