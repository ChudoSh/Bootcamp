package il.co.ILRD.Networking.TCP;

import java.io.*;
import java.net.*;

public class TCPClient {
    private final String ipAdress;
    Socket socket;
    DataInputStream din;
    DataOutputStream dout;

    public TCPClient(String ipAdress, int port) {
        this.ipAdress = ipAdress;
        try {
            socket = new Socket(InetAddress.getByName(ipAdress),port);
            System.out.println(socket);
            din = new DataInputStream(socket.getInputStream());
            dout = new DataOutputStream(socket.getOutputStream());
            ClientChat();
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public void ClientChat() throws IOException {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String s1;

        do {
            s1 = br.readLine();
            dout.writeUTF(s1);
            dout.flush();
            System.out.println("Server Message:" + din.readUTF());
        }
        while (!s1.equals("stop"));
    }

    public static void main(String[] as) {
        new TCPClient("10.10.2.56",8080);
    }
}