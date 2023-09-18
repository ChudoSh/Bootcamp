package il.co.ILRD.Networking.multiProtocolServer;


import java.io.*;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.ServerSocket;
import java.net.Socket;

public class MPServer {
    private final CommunicationManager communicator;
    private final MessageManager messanger;

    public MPServer(int port) throws IOException {
        this.communicator = new CommunicationManager(port);
        this.messanger = new MessageManager();
    }

    public void start() {
        this.communicator.startCommunication();
    }

    public void stop() throws InterruptedException {
        this.communicator.stopCommunication();
    }

    public interface Response {
        void send(String message) throws IOException;
        String getData() throws IOException;
    }

    /******************************************************************************/
    private class CommunicationManager {
        private final Thread TCPRegister;
        private final Thread UDPregister;

        public CommunicationManager(int port) {
            this.TCPRegister = new Thread(() -> {
                try {
                    new TCPRegister(port).run();
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            });

            this.UDPregister = new Thread(() -> {
                try {
                    new UDPRegister(port).run();
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
            });
        }

        public void startCommunication() {
            this.UDPregister.start();
            this.TCPRegister.start();
        }

        public void stopCommunication() throws InterruptedException {
            this.UDPregister.join();
            this.TCPRegister.join();
        }

        private void send(Response responder, String message) throws IOException {
            responder.send(message);
        }
    }

    /***************************************************************************/
    private static class MessageManager {
        public MessageManager() {
        }

        public String handle(String newData) throws IOException {
            System.out.println(newData);
            return "Pong";
        }
    }

    /***************************************************************************/
    private class TCPRegister implements Runnable {
        private final ServerSocket serverSocket;
        private boolean isRunning = true;

        public TCPRegister(int port) throws IOException {
            this.serverSocket = new ServerSocket(port);
        }

        public void stop() {
            this.isRunning = false;
        }

        @Override
        public void run() {
            while (isRunning) {
                Socket socket;
                try {
                    socket = this.serverSocket.accept();
                } catch (IOException e) {
                    Thread.currentThread().interrupt();
                    throw new RuntimeException(e);
                }
                new Thread(() -> new TCPListener(socket).run()).start();
            } //add close server
        }

        private class TCPListener implements Runnable {
            private final TCPResponse tcpResponse;

            private TCPListener(Socket socket) {
                this.tcpResponse = new TCPResponse(socket);
            }

            @Override
            public void run() {
                try {
                    communicator.send(this.tcpResponse,
                            messanger.handle(
                                    this.tcpResponse.getData()));
                } catch (IOException e) {
                    Thread.currentThread().interrupt();
                    throw new RuntimeException(e);
                }
            }
        }

    }

    private static class TCPResponse implements Response {
        private final Socket socket;

        public TCPResponse(Socket socket) {
            this.socket = socket;
        }

        @Override
        public void send(String message) throws IOException {
            DataOutputStream dos = new DataOutputStream(this.socket.getOutputStream());
            dos.writeUTF(message);
            dos.flush();
        }

        @Override
        public String getData() throws IOException {
            return new DataInputStream(this.socket.getInputStream()).readUTF();
        }
    }

    /***************************************************************************/
    private class UDPRegister implements Runnable {
        private final DatagramSocket serverDatagram;
        private boolean isRunning = true;

        public UDPRegister(int port) throws IOException {
            this.serverDatagram = new DatagramSocket(port);
        }

        public void stop() {
            this.isRunning = false;
        }

        @Override
        public void run() {
            while (isRunning) {
                try {
                    int bufferSize = 1024;
                    byte[] buffer = new byte[bufferSize];
                    DatagramPacket packet = new DatagramPacket(buffer, bufferSize);

                    this.serverDatagram.receive(packet);
                    UDPResponse udpResponse = new UDPResponse(serverDatagram, packet);

                    communicator.send(udpResponse, messanger.handle(udpResponse.getData()));
                } catch (IOException e) {
                    this.serverDatagram.close();
                    Thread.currentThread().interrupt();
                    throw new RuntimeException(e);
                }

            }
        }
    }

    private static class UDPResponse implements Response {
        private final DatagramPacket packet;
        private final DatagramSocket datagramSocket;

        public UDPResponse(DatagramSocket dgs, DatagramPacket packet) {
            this.datagramSocket = dgs;
            this.packet = packet;
        }

        @Override
        public void send(String message) throws IOException {
            datagramSocket.send(new DatagramPacket(message.getBytes(), message.getBytes().length,
                    this.packet.getAddress(), this.packet.getPort()));
        }

        @Override
        public String getData() throws IOException {
            return new String(this.packet.getData());
        }
    }

    /***************************************************************************/
    public static void main(String[] args) throws IOException {
        new MPServer(8080).start();
    }
}
