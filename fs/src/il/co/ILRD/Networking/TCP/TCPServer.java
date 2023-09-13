package il.co.ILRD.Networking.TCP;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class TCPServer {
    private ServerSocket ss;
    private Socket s;
    private DataInputStream dis;
    private DataOutputStream dos;

    public TCPServer(int port) throws IOException {
        this.ss = new ServerSocket(port);
        this.s = ss.accept();
        this.dis = new DataInputStream(s.getInputStream());
        this.dos = new DataOutputStream(s.getOutputStream());

        try {
            System.out.println("Server Started");
            System.out.println(s);
            System.out.println("CLIENT CONNECTED");
            dis = new DataInputStream(s.getInputStream());
            dos = new DataOutputStream(s.getOutputStream());
            ServerChat();
        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public void ServerChat() throws IOException {
        String str, s1;
        do {
            str = dis.readUTF();
            System.out.println("Client Message:" + str);
            BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
            s1 = br.readLine();
            dos.writeUTF(s1);
            dos.flush();
        }
        while (!s1.equals("bye"));
    }

    public static void main(String[] as) throws IOException {
        new TCPServer(1234);
    }
}

