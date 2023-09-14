package il.co.ILRD.Networking.TCP;

import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;

public class TCPServer implements Runnable {
    private final ServerSocket ss;
    private boolean isRunning = true;

    public TCPServer(int port) throws IOException {
        this.ss = new ServerSocket(port);

        System.out.println("TCP Server Started");
        System.out.println("Type 'bye' to exit");
    }

    @Override
    public void run() {
        while (isRunning) {
            Socket socket;
            try {
                socket = this.getSocket();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            new TCPThread(socket).start();
        }
    }

    private static class TCPThread extends Thread {
        private final Socket threadSocket;

        private TCPThread(Socket socket) {
            this.threadSocket = socket;
        }

        @Override
        public void run() {
            try {
                String str = null;
                DataInputStream dis = new DataInputStream(threadSocket.getInputStream());
                DataOutputStream dos = new DataOutputStream(threadSocket.getOutputStream());
                System.out.println("TCP CLIENT CONNECTED");
                str = dis.readUTF();
                System.out.println("Client Message:" + str);

                while (!str.equals("bye")) {
                    BufferedReader br = new BufferedReader(
                            new InputStreamReader(System.in));
                    str = br.readLine();
                    dos.writeUTF(str);
                    dos.flush();

                    str = dis.readUTF();
                    System.out.println("Client Message:" + str);
                }
                this.threadSocket.close();
            } catch (IOException e) {
                Thread.currentThread().interrupt();
                throw new RuntimeException(e);
            }
        }
    }

    public Socket getSocket() throws IOException {
        return ss.accept();
    }

    public void stop() {
        this.isRunning = false;
    }
}

