package il.co.ILRD.networking.multiProtocolServer;

import java.io.*;
import java.net.*;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;

public class MultiProtocolServer {
    private final CommunicationManager communicationManager;
    private final MessageManager messageManager;

    public MultiProtocolServer() {
        this.communicationManager = new CommunicationManager();
        this.messageManager = new MessageManager();
    }

    public void addTCPConnection(int clientPort) throws IOException {
        this.communicationManager.addTCPConnection(clientPort);
    }

    public void addUDPConnection(int clientPort) throws IOException {
        this.communicationManager.addUDPConnection(clientPort);
    }

    public void start() {
        this.communicationManager.start();
    }

    public void stop() {
        this.communicationManager.stop();
    }


    public static ByteBuffer serialize(Message<?, ?> message) {
        try {
            ByteArrayOutputStream bos = new ByteArrayOutputStream();
            ObjectOutputStream out = new ObjectOutputStream(bos);
            out.writeObject(message);
            out.flush();
            byte[] bytes = bos.toByteArray();
            return ByteBuffer.wrap(bytes);
        } catch (IOException e) {
            throw new RuntimeException("serialize error");
        }
    }

    public static Message<?, ?> deserialize(ByteBuffer buffer) {
        if (null == buffer) {
            return null;
        }

        ByteArrayInputStream bis =
                new ByteArrayInputStream(buffer.array());
        try (ObjectInput in = new ObjectInputStream(bis)) {
            return (Message<?, ?>) in.readObject();
        } catch (IOException | ClassNotFoundException e) {
            throw new RuntimeException("deserialize error");
        }
    }

    /****************************Interfaces*****************************************/
    private interface Communicator {
        ByteBuffer receive() throws IOException;

        void send(ByteBuffer buffer) throws IOException;
    }

    public interface Message<K, D extends Serializable> extends Serializable {
        K getKey();

        D getData();
    }

    private interface MessageHandler {
        void handle(Message<?, ?> message, Communicator communicator)
                throws IOException;
    }

    public enum MessageProtocol {
        PING_PONG();

        MessageProtocol() {
        }
    }

    /********************CommunicationManager**********************************/
    private class CommunicationManager {
        private boolean isRunning;
        private final Selector selector;
        private final ByteBuffer msgBuffer;
        private final SelectorRunner runner;
        private final Thread thread;

        public CommunicationManager() {
            try {
                this.selector = Selector.open();
                this.runner = new SelectorRunner();
            } catch (IOException e) {
                throw new RuntimeException("Selector open");
            }
            this.thread = new Thread(this.runner);
            msgBuffer = ByteBuffer.allocate(2048);
        }

        private void start() {
            if (!isRunning) {
                this.isRunning = true;
                this.thread.start();
                try {
                    this.thread.join();
                } catch (InterruptedException e) {
                    System.out.println("Thread Interrupted");
                    throw new RuntimeException();
                }
            }
        }

        private void addTCPConnection(int clientPort) throws IOException {
            ServerSocketChannel tcpServerSocket = ServerSocketChannel.open();
            tcpServerSocket.configureBlocking(false);
            tcpServerSocket.bind(new InetSocketAddress("localhost", clientPort));
            tcpServerSocket.register(selector, SelectionKey.OP_ACCEPT);
        }

        private void addUDPConnection(int clientPort) throws IOException {
            DatagramChannel udpServerSocket = DatagramChannel.open();
            udpServerSocket.configureBlocking(false);
            udpServerSocket.bind(new InetSocketAddress("localhost", clientPort));
            udpServerSocket.register(selector, SelectionKey.OP_READ);
        }

        private void stop() {
            this.isRunning = false;
        }

        /*************************SelectorRunner*******************************/
        private class SelectorRunner implements Runnable {
            private final ServerSocketChannel tcpServer;
            private final DatagramChannel udpServer;
            private final TCPRegister tcpRegister;

            public SelectorRunner() throws IOException {
                this.tcpServer = ServerSocketChannel.open();
                this.udpServer = DatagramChannel.open();

                this.tcpServer.configureBlocking(false);
                this.udpServer.configureBlocking(false);

                this.tcpServer.register(selector, SelectionKey.OP_ACCEPT);
                this.udpServer.register(selector, SelectionKey.OP_READ);

                this.tcpRegister = new TCPRegister();
            }

            @Override
            public void run() {
                Set<SelectionKey> keys = null;
                while (isRunning) {
                    try {
                        selector.select();

                        keys = selector.selectedKeys();
                        Iterator<SelectionKey> iterator = keys.iterator();

                        while (iterator.hasNext()) {
                            SelectionKey key = iterator.next();
                            Communicator communicator = this.getCommunicator(key);

                            if (null != communicator) {
                                messageManager.handle(msgBuffer, communicator);
                            }

                            iterator.remove();
                        }

                    } catch (IOException | ClassNotFoundException e) {
                        throw new RuntimeException(e);
                    }
                }

                assert keys != null;
                keys.clear();
            }

            private Communicator getCommunicator(SelectionKey key)
                    throws IOException {
                if (key.isAcceptable()) {
                    ServerSocketChannel ssc = (ServerSocketChannel) key.channel();
                    this.tcpRegister.TCPAccept(ssc);
                } else if (key.isReadable()) {
                    Channel channel = key.channel();
                    if (channel instanceof SocketChannel) {
                        return (TCPCommunicator) key.attachment();
                    } else {
                        DatagramChannel datagramChannel = (DatagramChannel) channel;
                        datagramChannel.disconnect();

                        return new UDPCommunicator(datagramChannel);
                    }
                }

                return null;
            }

        }

        /******************************TCPRegister*****************************/
        private class TCPRegister {
            public TCPRegister() {
            }

            public TCPCommunicator TCPAccept(ServerSocketChannel ssc) {
                try {
                    SocketChannel client = ssc.accept();
                    client.configureBlocking(false);
                    SelectionKey key = client.register(selector, SelectionKey.OP_READ);
                    TCPCommunicator tcpCommunicator = new TCPCommunicator(client);
                    key.attach(tcpCommunicator);

                    return tcpCommunicator;
                } catch (IOException e) {
                    throw new RuntimeException("tcp accept error");
                }
            }
        }
    }

    /***************************TCPCommunicator********************************/
    private static class TCPCommunicator implements Communicator {
        private final SocketChannel clientSocketChannel;

        public TCPCommunicator(SocketChannel clientSocketChannel) {
            this.clientSocketChannel = clientSocketChannel;
        }

        @Override
        public void send(ByteBuffer buffer) {
            try {
                if (!clientSocketChannel.isOpen() || !clientSocketChannel.isConnected()) {
                    System.out.println("SocketChannel not available");
                    return;
                }

                buffer.limit(buffer.array().length);
                while (buffer.hasRemaining()) {
                    this.clientSocketChannel.write(buffer);
                }
            } catch (IOException e) {
                throw new RuntimeException("tcp send error");
            }
        }

        @Override
        public ByteBuffer receive() {
            try {
                int buffSize = 2048;
                ByteBuffer buffer = ByteBuffer.allocate(buffSize);

                if (-1 == this.clientSocketChannel.read(buffer)) {
                    this.clientSocketChannel.close();
                    return null;
                }

                buffer.flip();
                return buffer;
            } catch (IOException e) {
                throw new RuntimeException("tcp receive error");
            }
        }
    }

    /******************************UDPCommunicator*****************************/
    private static class UDPCommunicator implements Communicator {
        private SocketAddress socketAddress;
        private final DatagramChannel datagramChannel;

        public UDPCommunicator(DatagramChannel datagramChannel) {
                this.datagramChannel = datagramChannel;
        }

        @Override
        public void send(ByteBuffer buffer) {
            try {
                this.datagramChannel.send(buffer, socketAddress);
                buffer.flip();
            } catch (IOException e) {
                throw new RuntimeException("udpCommunicator send error");
            }
        }

        @Override
        public ByteBuffer receive() {
            try {
                int buffSize = 2048;

                ByteBuffer buffer = ByteBuffer.allocate(buffSize);
                this.socketAddress = this.datagramChannel.receive(buffer);
                buffer.flip();

                return buffer;
            } catch (IOException e) {
                throw new RuntimeException("udpCommunicator receive error");
            }
        }

    }

    /*************************MessageManager***********************************/
    private static class MessageManager {
        private final Map<MessageProtocol, MessageHandler> messageHandlers = new HashMap<>();

        public MessageManager() {
            messageHandlers.put(MessageProtocol.PING_PONG, new PingPongMessageHandler());
        }

        private void handle(ByteBuffer buffer, Communicator communicator) throws IOException, ClassNotFoundException {
            buffer = communicator.receive();
            Message<?, ?> message = deserialize(buffer);
            if (null == message) {
                return;
            }
            this.messageHandlers.get(message.getKey()).handle(message, communicator);
        }

        private static class PingPongMessageHandler implements MessageHandler {

            PingPongMessage<MessageProtocol, String> messagePingPong;

            @Override
            public void handle(Message<?, ?> message, Communicator communicator) throws IOException {
                System.out.println((String) message.getData());
                this.messagePingPong = new PingPongMessage<>(MessageProtocol.PING_PONG, "Pong");

                ByteBuffer toSend = serialize(messagePingPong);
                toSend.flip();
                toSend.limit(toSend.array().length);
                communicator.send(toSend);
            }
        }
    }
}