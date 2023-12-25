package il.co.ILRD.networking.HttpServer;

import il.co.ILRD.crud_sql_n_nosql.NoSqlCrudManager;
import il.co.ILRD.crud_sql_n_nosql.SqlCrudManager;
import il.co.ILRD.hashmap.Pair;
import il.co.ILRD.thread_pool.ThreadPool;


import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonReader;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import com.sun.media.sound.InvalidDataException;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.util.*;
import java.util.function.Function;

public class HttpServer {
    private MultiProtocolServer multiProtocolServer;
    private RequestHandler requestHandler;
    private PlugAndPlay plugAndPlay;

    public HttpServer(int numOfThreads) {
        this.requestHandler = new RequestHandler(numOfThreads);
        this.multiProtocolServer = new MultiProtocolServer();
        this.plugAndPlay = new PlugAndPlay("/home/barchik/Mygit/bar.shadkhin/fs/src/il/co/ILRD/networking/GatewayServer/Mock data", this.requestHandler.factory);
    }

    public void start() {
        try {
            this.multiProtocolServer.addTCPConnection(9797);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        this.multiProtocolServer.start();
        this.plugAndPlay.start();
    }

    private void handle(ByteBuffer buffer, Communicator communicator) {
        if (null == buffer) {
            return;
        }
        this.requestHandler.handle(buffer, communicator);
    }

    private interface Communicator {
        ByteBuffer receive();

        void send(ByteBuffer buffer);
    }

    private class RequestHandler {
        private final ThreadPool threadPool;
        private final Factory<String, JsonObject> factory;
        private static final String fileDir = "/home/barchik/Mygit/bar.shadkhin/fs/src/il/co/ILRD/networking/GatewayServer/Mock data/mocodata.txt";
        private SqlCrudManager sqlCrudManager;
        private NoSqlCrudManager noSqlCrudManager;

        private RequestHandler(int numOfThreads) {
            this.threadPool = new ThreadPool(numOfThreads);
            this.factory = new Factory<>();
            this.noSqlCrudManager = new NoSqlCrudManager("localhost");
            this.sqlCrudManager = new SqlCrudManager("SqlAndNoSqlTest");
            this.sqlCrudManager.start();
            this.factory.add("POST/company", new CreateCompany());
//            this.factory.add("GET/company", new ReadCompany());
//            this.factory.add("PUT/company", new UpdateCompany());
//            this.factory.add("DELETE/company", new DeleteCompany());
        }

        private void handle(ByteBuffer buffer, Communicator communicator) {
            Runnable run = this.createRunnable(buffer, communicator);
            this.threadPool.execute(run);
        }

        private Runnable createRunnable(ByteBuffer buffer, Communicator communicator) {
            return () -> {
                try {
                    JsonObject json = this.read(buffer);
                    if (null == json) {
                        throw new InvalidDataException("json is null");
                    }

                    Map.Entry<String, JsonObject> newEntry = Pair.of(json.getJsonObject("StartLine").getString("method"), json.getJsonObject("Body"));

                    Command cmd = factory.create(newEntry.getKey(), newEntry.getValue());
                    if (null == cmd) {
                        throw new InvalidDataException("invalid request");
                    }

                    cmd.exec(this.sqlCrudManager, this.noSqlCrudManager);
                    JsonObject success = this.createResponse(200, "Success");
                    communicator.send(this.write(success));

                } catch (InvalidDataException e) {
                    System.out.println("um here");
                    JsonObject error = this.createResponse(405, e.getMessage());
                    communicator.send(ByteBuffer.wrap(error.toString().getBytes()));
                }
            };
        }

        private JsonObject createResponse(int statusCode, String message) {
            return Json.createObjectBuilder().add("StartLine",
                            Json.createObjectBuilder().
                                    add("Status Code", statusCode).
                                    add("URL", "")).
                    add("Version", "").
                    add("Headers", Json.createObjectBuilder().
                            add("ContentType", "application/json").
                            add("ContentLength", message.length())).
                    add("Body", message).build();
        }

        private ByteBuffer write(JsonObject json) {
            if (json.isNull("StartLine") || json.isNull("Body") || json.isNull("Headers")) {
                return null;
            }

            return ByteBuffer.wrap(json.toString().getBytes());
        }

        private JsonObject read(ByteBuffer buffer) {
            if (null == buffer) {
                return null;
            }

            JsonReader reader = Json.createReader(new ByteArrayInputStream(buffer.array()));
            JsonObject json = reader.readObject();
            reader.close();

            return json;
        }

    }

    private class CreateCompany implements Function<JsonObject, Command> {
        @Override
        public Command apply(JsonObject data) {
            return (sqlCrudManager, noSqlCrudManager) -> {
                sqlCrudManager.registerCompany(data);
                noSqlCrudManager.registerCompany(data);
            };
        }
    }

//        private class ReadCompany implements Function<JsonObject, Command> {
//            @Override
//            public Command apply(JsonObject data) {
//                return adminDB -> {
//                    CompanyRecord companyRecord = new CompanyRecord(data.getString("company_name"),
//                            data.getString("company_address"),
//                            data.getString("contact_name"),
//                            data.getString("contact_email"),
//                            data.getString("contact_phone"),
//                            data.getInt("service_fee"), adminDB.getDatabaseConnection());
//                    companyRecord.setCompanyID(data.getInt("company_id"));
//                    CompanyRecord read = (CompanyRecord) adminDB.read(companyRecord);
//                    System.out.println(read.toString());
//                };
//            }
//        }
//
//        private class UpdateCompany implements Function<JsonObject, Command> {
//            @Override
//            public Command apply(JsonObject data) {
//                return adminDB -> {
//                    CompanyRecord companyRecord = new CompanyRecord(data.getString("company_name"),
//                            data.getString("company_address"),
//                            data.getString("contact_name"),
//                            data.getString("contact_email"),
//                            data.getString("contact_phone"),
//                            data.getInt("service_fee"), adminDB.getDatabaseConnection());
//                    companyRecord.setCompanyID(data.getInt("company_id"));
//                    adminDB.update(companyRecord);
//                };
//            }
//        }
//
//        private class DeleteCompany implements Function<JsonObject, Command> {
//            @Override
//            public Command apply(JsonObject data) {
//                return adminDB -> {
//                    CompanyRecord companyRecord = new CompanyRecord(data.getString("company_name"),
//                            data.getString("company_address"),
//                            data.getString("contact_name"),
//                            data.getString("contact_email"),
//                            data.getString("contact_phone"),
//                            data.getInt("service_fee"), adminDB.getDatabaseConnection());
//                    companyRecord.setCompanyID(data.getInt("company_id"));
//                    adminDB.delete(companyRecord);
//                };
//            }
//        }


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


        public void start() {
            this.communicationManger.start();
        }

        /*=================================================================================================*/
        /*===================================== Massage Handlers =====================================*/
        /*=================================================================================================*/
        private class MessageManager {
            public void handle(Communicator communicator) {
                HttpServer.this.handle(communicator.receive(), communicator);
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
                    Iterator<SelectionKey> iterator;
                    while (isRunning) {
                        try {
                            selector.select();
                            selectedKeys = selector.selectedKeys();
                            iterator = selectedKeys.iterator();

                            while (iterator.hasNext()) {
                                SelectionKey key = iterator.next();
                                getConnectionAndHandle(key);
                            }
                        } catch (IOException | ClassNotFoundException e) {
                            throw new RuntimeException(e);
                        }
                        iterator.remove();
                    }
                    assert selectedKeys != null;
                    selectedKeys.clear();
                }

                private void getConnectionAndHandle(SelectionKey key)
                        throws IOException, ClassNotFoundException {
                    if (key.isAcceptable()) {
                        ServerSocketChannel ssc = (ServerSocketChannel) key.channel();
                        tcpRegister.TCPAccept(ssc);
                    } else if (key.isReadable()) {
                        Channel channel = key.channel();
                        if (channel instanceof SocketChannel) {
                            messageManager.handle((TCPCommunicator) key.attachment());
                        } else {
                            DatagramChannel datagramChannel = (DatagramChannel) channel;

                            messageManager.handle(new UDPCommunicator(datagramChannel));
                        }
                    }
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
                    int FAIL = -1;

                    try {
                        ByteBuffer buffer = ByteBuffer.allocate(2048);
                        int bytesRead = this.clientSocketChannel.read(buffer);

                        if (bytesRead == FAIL) {
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

    public static void main(String[] args) throws IOException {
        HttpServer server = new HttpServer(4);
        server.start();
    }
}
