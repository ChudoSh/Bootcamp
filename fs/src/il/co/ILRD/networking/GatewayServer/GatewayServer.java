package il.co.ILRD.networking.GatewayServer;

import com.sun.media.sound.InvalidDataException;
import il.co.ILRD.hashmap.Pair;
import il.co.ILRD.thread_pool.ThreadPool;

import java.io.FileWriter;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.util.*;
import java.util.Map.Entry;
import java.util.function.Function;


public class GatewayServer {
    private MultiProtocolServer multiProtocolServer;
    private RequestHandler requestHandler;

    public GatewayServer(int numOfThreads) throws IOException, ClassNotFoundException {
        this.requestHandler = new RequestHandler(numOfThreads);
        this.multiProtocolServer = new MultiProtocolServer();
        this.multiProtocolServer.addTCPConnection(8989);
        this.multiProtocolServer.start();
    }


    private void handle(ByteBuffer buffer, Communicator communicator) {
        if (null ==  buffer){
           return;
        }
        this.requestHandler.handle(buffer, communicator);
    }

    private interface Communicator {
        ByteBuffer receive();

        void send(ByteBuffer buffer);

    }

    private interface Command {
        void exec() throws InvalidDataException, InvocationTargetException, IllegalAccessException;
    }

    private static class RequestHandler {
        private ThreadPool threadPool;
        private Factory<String, String> factory;
        private static final String fileDir = "/home/barchik/Mygit/bar.shadkhin/fs/src/il/co/ILRD/networking/GatewayServer/Mock data";

        private RequestHandler(int numOfThreads) {
            this.threadPool = new ThreadPool(numOfThreads);
            this.factory = new Factory<>();
            this.factory.add("RegisterCompany", new RegisterCompany());
            this.factory.add("RegisterProduct", new RegisterProduct());
            this.factory.add("RegisterIOT", new RegisterIOT());
            this.factory.add("Update", new Update());
        }

        private void handle(ByteBuffer buffer, Communicator communicator) {
            this.threadPool.submit(this.createRunnable(buffer, communicator), ThreadPool.Priority.DEFAULT);
        }

        private Entry<String, String> parse(String request) throws InvalidDataException {
            String[] prasedRequest = request.split("@");
            StringBuilder data = new StringBuilder();

            if (prasedRequest.length <= 1) {
                throw new InvalidDataException("Invalid parsing");
            }

            for (int i = 1; i < prasedRequest.length; ++i) {
                data.append(prasedRequest[i]);
            }

            return Pair.of(prasedRequest[0], data.toString());
        }

        private class Factory<K, D> {
            private Map<K, Function<D, Command>> commands;

            public Factory() {
                this.commands = new HashMap<>();
            }

            private void add(K key, Function<D, Command> command) {
                this.commands.put(key, command);
            }

            private Command create(K key, D data) {
                return this.commands.get(key).apply(data);
            }
        }

        private Runnable createRunnable(ByteBuffer buffer, Communicator communicator) {
            return () -> {
                try {
                    String request = new String(buffer.array(), 0, buffer.remaining());
                    Entry<String, String> newEntry = this.parse(request);
                    this.factory.create(newEntry.getKey(), newEntry.getValue()).exec();
                    communicator.send(ByteBuffer.wrap("Received".getBytes()));
                } catch (InvalidDataException e) {
                    communicator.send(ByteBuffer.wrap(e.getMessage().getBytes()));
                } catch (InvocationTargetException | IllegalAccessException e) {
                    throw new RuntimeException(e);
                }
            };
        }

        private static class RegisterCompany implements Function<String, Command> {
            @Override
            public Command apply(String data) {
                return () -> {
                    try {
                        FileWriter writer = new FileWriter(fileDir);
                        writer.write("Register Company: " + data);
                        writer.close();
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                };
            }
        }

        private static class RegisterProduct implements Function<String, Command> {
            @Override
            public Command apply(String data) {
                return () -> {
                    try {
                        FileWriter writer = new FileWriter(fileDir);
                        writer.write("Register Proudct: " + data);
                        writer.close();
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                };
            }
        }

        private static class RegisterIOT implements Function<String, Command> {
            @Override
            public Command apply(String data) {
                return () -> {
                    try {
                        FileWriter writer = new FileWriter(fileDir);
                        writer.write("Register IOT: " + data);
                        writer.close();
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                };
            }
        }

        private static class Update implements Function<String, Command> {
            @Override
            public Command apply(String data) {
                return () -> {
                    try {
                        FileWriter writer = new FileWriter(fileDir);
                        writer.write("Update: " + data);
                        writer.close();
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                };
            }
        }
    }

    private class MultiProtocolServer {
        private final CommunicationManager communicationManger;
        private final MessageManager messageManager;

        public MultiProtocolServer() {
            this.communicationManger = new CommunicationManager();
            this.messageManager = new MessageManager();
        }

        public void addTCPConnection(int clientPort) throws IOException {
            this.communicationManger.addTCPConnection(clientPort);
        }

        public void addUDPConnection(int clientPort) throws IOException {
            this.communicationManger.addUDPConnection(clientPort);
        }

        public void stop() {
            this.communicationManger.stop();
        }


        public void start() throws IOException, ClassNotFoundException {
            this.communicationManger.start();
        }

        /*=================================================================================================*/
        /*===================================== Massage Handlers =====================================*/
        /*=================================================================================================*/
        private class MessageManager {
            public void handle(Communicator communicator) throws IOException, ClassNotFoundException {
                ByteBuffer byteBuffer = communicator.receive();
                GatewayServer.this.handle(byteBuffer, communicator);
            }
        }

        /*=================================================================================================*/
        /*===================================== Communication Manager =====================================*/
        /*=================================================================================================*/
        private class CommunicationManager { //is it public?

            private final Selector selector;
            private boolean isRunning;
            private final SelectorRunner selectorRunner;


            public CommunicationManager() {
                try {
                    this.selector = Selector.open();
                } catch (IOException e) {
                    throw new RuntimeException(e);
                }
                this.isRunning = true;
                this.selectorRunner = new SelectorRunner();
            }

            public void addTCPConnection(int TCPClientPort) throws IOException {
                this.selectorRunner.tcpServerSocket.bind(new InetSocketAddress("localhost", TCPClientPort));
            }

            public void addUDPConnection(int UDPClientPort) throws IOException {
                this.selectorRunner.udpServerSocket.bind(new InetSocketAddress("localhost", UDPClientPort));
            }

            public void start() {
                new Thread(this.selectorRunner).start();
            }

            public void stop() {
                this.isRunning = false;
            }

            /*================================ Selector Runner ==============================================*/

            private class SelectorRunner implements Runnable {
                private final ServerSocketChannel tcpServerSocket;
                private final DatagramChannel udpServerSocket;
                private TCPRegister tcpRegister;

                public SelectorRunner() {
                    try {
                        this.tcpServerSocket = ServerSocketChannel.open();
                        this.udpServerSocket = DatagramChannel.open();
                        this.tcpServerSocket.configureBlocking(false);
                        this.udpServerSocket.configureBlocking(false);
                        this.udpServerSocket.register(selector, SelectionKey.OP_READ);
                        this.tcpServerSocket.register(selector, SelectionKey.OP_ACCEPT);
                        this.tcpRegister = new TCPRegister();

                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                }

                @Override
                public void run() {
                    Set<SelectionKey> selectedKeys = null;
                    while (isRunning) {
                        try {
                            selector.select();
                            selectedKeys = selector.selectedKeys();
                            Iterator<SelectionKey> iterator = selectedKeys.iterator();

                            while (iterator.hasNext()) {
                                SelectionKey key = iterator.next();
                                Communicator communicator = getCommunicator(key);

                                if (null != communicator) {
                                    messageManager.handle(communicator);
                                }

                                iterator.remove();
                            }
                        } catch (IOException | ClassNotFoundException e) {
                            throw new RuntimeException(e);
                        }
                    }
                    assert selectedKeys != null;
                    selectedKeys.clear();
                }

                private Communicator getCommunicator(SelectionKey key)
                        throws IOException {
                    if (key.isAcceptable()) {
                        ServerSocketChannel ssc = (ServerSocketChannel) key.channel();
                        return this.tcpRegister.TCPAccept(ssc);
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

            /*======================================== TCP register =================================================*/
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
            /*========================================== Communicators =================================================*/

            private class TCPCommunicator implements Communicator {
                private final SocketChannel clientSocketChannel;

                public TCPCommunicator(SocketChannel clientSocketChannel) {
                    this.clientSocketChannel = clientSocketChannel;
                }

                @Override
                public ByteBuffer receive() {
                    try {
                        ByteBuffer buffer = ByteBuffer.allocate(2048);
                        int bytesRead = this.clientSocketChannel.read(buffer);
                        buffer.flip();

                        if (bytesRead == -1) {
                            this.clientSocketChannel.close();
                            return null;
                        }

                        buffer.flip();
                        return buffer;
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                }

                @Override
                public void send(ByteBuffer buffer) {
                    try {
                        if (!this.clientSocketChannel.isOpen() || !this.clientSocketChannel.isConnected()) {
                            System.out.println("SocketChannel is not open or connected!");
                            return;
                        }
                        buffer.limit(buffer.array().length);
                        while (buffer.hasRemaining()) {
                            this.clientSocketChannel.write(buffer);
                        }

                        System.out.println("Sending massage to " + clientSocketChannel);
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                }
            }

            private class UDPCommunicator implements Communicator {

                private final DatagramChannel clientDatagramChannel;
                private SocketAddress clientAddress;

                public UDPCommunicator(DatagramChannel clientDatagramChannel) {
                    this.clientDatagramChannel = clientDatagramChannel;
                }

                @Override
                public ByteBuffer receive() {
                    try {
                        ByteBuffer buffer = ByteBuffer.allocate(2048);
                        this.clientAddress = clientDatagramChannel.receive(buffer);
                        buffer.flip();
                        return buffer;
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                }

                @Override
                public void send(ByteBuffer buffer) {
                    try {
                        this.clientDatagramChannel.send(buffer, clientAddress);
                        buffer.flip();
                    } catch (IOException e) {
                        throw new RuntimeException(e);
                    }
                }
            }
        }
    }
}
