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
                DataOutputStream dos;
                String str = null;
                DataInputStream dis = new DataInputStream(threadSocket.getInputStream());
                System.out.println("TCP CLIENT CONNECTED");
                str = dis.readUTF();
                System.out.println("TCP Client message:" + str);

                while (!str.equals("bye")){
                    System.out.println("Please insert message:");
                    BufferedReader br = new BufferedReader(
                            new InputStreamReader(System.in));
                    str = br.readLine();
                    dos = new DataOutputStream(threadSocket.getOutputStream());
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

