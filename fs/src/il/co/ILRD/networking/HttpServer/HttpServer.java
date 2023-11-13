package il.co.ILRD.networking.HttpServer;

import com.sun.media.sound.InvalidDataException;
import il.co.ILRD.hashmap.Pair;
import il.co.ILRD.sql.database_manager.AdminDB;
import il.co.ILRD.sql.database_manager.CRUD;
import il.co.ILRD.sql.database_manager.CompanyRecord;
import il.co.ILRD.thread_pool.ThreadPool;


import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonReader;
import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.InetSocketAddress;
import java.net.SocketAddress;
import java.net.URL;
import java.net.URLClassLoader;
import java.nio.ByteBuffer;
import java.nio.channels.*;
import java.nio.file.*;
import java.util.*;
import java.util.function.Function;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;

public class HttpServer {
    private MultiProtocolServer multiProtocolServer;
    private RequestHandler requestHandler;
    private AdminDB adminDB;
    private PlugAndPlay plugAndPlay;

    public HttpServer(int numOfThreads) {
        this.requestHandler = new RequestHandler(numOfThreads);
        this.adminDB = new AdminDB("httpServerTest");
        this.multiProtocolServer = new MultiProtocolServer();
        this.plugAndPlay = new PlugAndPlay("/home/barchik/Mygit/bar.shadkhin/fs/src/il/co/ILRD/networking/GatewayServer/Mock data");
    }

    public void start() {
        try {
            this.multiProtocolServer.addTCPConnection(8989);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        this.multiProtocolServer.start();
        this.adminDB.initiateDatabaseAndTables();
//        this.plugAndPlay.start();
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

    public interface Command {
        void exec(CRUD adminDB) throws InvalidDataException;
    }

    private class RequestHandler {
        private ThreadPool threadPool;
        private RequestHandler.Factory<String, JsonObject> factory;
        private HttpHandler httpHandler;
        private static final String fileDir = "/home/barchik/Mygit/bar.shadkhin/fs/src/il/co/ILRD/networking/GatewayServer/Mock data/mocodata.txt";

        private RequestHandler(int numOfThreads) {
            this.httpHandler = new HttpHandler();
            this.threadPool = new ThreadPool(numOfThreads);
            this.factory = new Factory<>();
            this.factory.add("POST/company", new CreateCompany());
            this.factory.add("GET/company", new ReadCompany());
            this.factory.add("PUT/company", new UpdateCompany());
            this.factory.add("DELETE/company", new DeleteCompany());
        }

        private void handle(ByteBuffer buffer, Communicator communicator) {
            this.threadPool.submit(this.createRunnable(buffer, communicator), ThreadPool.Priority.DEFAULT);
        }

        private class Factory<K, D> {
            private Map<K, Function<D, Command>> commands;

            public Factory() {
                this.commands = new HashMap<>();
            }

            private void add(K key, Function<D, Command> command) {
                this.commands.put(key, command);
                System.out.println("command " + key + " added to factory");
            }

            private Command create(K key, D data) {
                Function<D, Command> recipe = this.commands.get(key);

                return (null == recipe) ? null : recipe.apply(data);
            }
        }

        private class HttpHandler {
            public HttpHandler() {
            }

            public Command handle(ByteBuffer buffer, Communicator communicator) {
                JsonObject json = this.read(buffer);
                if (null == json) {
                    JsonObject error = this.createResponse(400, "No Request Found");
                    communicator.send(this.write(error));
                    return null;
                }

                Map.Entry<String, JsonObject> newEntry = Pair.of(json.getJsonObject("StartLine").getString("method"), json.getJsonObject("Body"));

                Command cmd = factory.create(newEntry.getKey(), newEntry.getValue());
                if (null == cmd) {
                    JsonObject error = this.createResponse(405, "Method Not Allowed");
                    communicator.send(this.write(error));
                    return null;
                }

                return cmd;
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
        }

        private Runnable createRunnable(ByteBuffer buffer, Communicator communicator) {
            return () -> {
                try {
                    Objects.requireNonNull(httpHandler.handle(buffer, communicator)).exec(HttpServer.this.adminDB);
                    JsonObject success = httpHandler.createResponse(200, "Success");
                    communicator.send(httpHandler.write(success));
                } catch (InvalidDataException e) {
                    communicator.send(ByteBuffer.wrap(e.getMessage().getBytes()));
                }
            };
        }

        private class CreateCompany implements Function<JsonObject, Command> {
            @Override
            public Command apply(JsonObject data) {
                return adminDB -> {
                    CompanyRecord companyRecord = new CompanyRecord(data.getString("company_name"),
                            data.getString("company_address"),
                            data.getString("contact_name"),
                            data.getString("contact_email"),
                            data.getString("contact_phone"),
                            data.getInt("service_fee"), adminDB.getDatabaseConnection());
                    adminDB.create(companyRecord);
                };
            }
        }

        private class ReadCompany implements Function<JsonObject, Command> {
            @Override
            public Command apply(JsonObject data) {
                return adminDB -> {
                    CompanyRecord companyRecord = new CompanyRecord(data.getString("company_name"),
                            data.getString("company_address"),
                            data.getString("contact_name"),
                            data.getString("contact_email"),
                            data.getString("contact_phone"),
                            data.getInt("service_fee"), adminDB.getDatabaseConnection());
                    companyRecord.setCompanyID(data.getInt("company_id"));
                    CompanyRecord read = (CompanyRecord) adminDB.read(companyRecord);
                    System.out.println(read.toString());
                };
            }
        }

        private class UpdateCompany implements Function<JsonObject, Command> {
            @Override
            public Command apply(JsonObject data) {
                return adminDB -> {
                    CompanyRecord companyRecord = new CompanyRecord(data.getString("company_name"),
                            data.getString("company_address"),
                            data.getString("contact_name"),
                            data.getString("contact_email"),
                            data.getString("contact_phone"),
                            data.getInt("service_fee"), adminDB.getDatabaseConnection());
                    companyRecord.setCompanyID(data.getInt("company_id"));
                    adminDB.update(companyRecord);
                };
            }
        }

        private class DeleteCompany implements Function<JsonObject, Command> {
            @Override
            public Command apply(JsonObject data) {
                return adminDB -> {
                    CompanyRecord companyRecord = new CompanyRecord(data.getString("company_name"),
                            data.getString("company_address"),
                            data.getString("contact_name"),
                            data.getString("contact_email"),
                            data.getString("contact_phone"),
                            data.getInt("service_fee"), adminDB.getDatabaseConnection());
                    companyRecord.setCompanyID(data.getInt("company_id"));
                    adminDB.delete(companyRecord);
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
                        System.out.println("In receive TCP Communicator "
                                + new String(buffer.array()));
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

    /*=================================================================================================*/
    /*===================================== Plug & Play ===============================================*/
    /*=================================================================================================*/

    private class PlugAndPlay implements Runnable { /*add a way to load classes that already exist in the folder*/
        private final Loader jarLoader;
        private final Wathcer wathcer;
        private final String path;

        public PlugAndPlay(String path) {
            this.path = path;
            this.wathcer = new Wathcer(path);
            this.jarLoader = new Loader();
        }

        public void start() {
            new Thread(this).start();
        }

        @Override
        public void run() {
            try {
//                this.addToFactory(
//                        this.jarLoader.load(
//                                Path.of(this.path)));
                while (!Thread.currentThread().isInterrupted()) {
                    this.addToFactory(this.jarLoader.load(
                            this.wathcer.watch()));
                }
            } catch (ClassNotFoundException e) {
                throw new RuntimeException("Class not found - Wathcer");
            } catch (IOException e) {
                throw new RuntimeException("IO - watcher");
            }
        }

        private void addToFactory(List<Class<?>> commands) {
            if (null != commands) {
                for (Class<?> cmd : commands) {
                    try {
                        Object obj = cmd.newInstance();
                        Method method = cmd.getMethod("call");
                        Function<JsonObject, Command> recipe = toCommand(obj, method);
                        System.out.println("cmd.name " + cmd.getName());

                        HttpServer.this.requestHandler.
                                factory.add(cmd.getName(), recipe);

                    } catch (InstantiationException | IllegalAccessException |
                             NoSuchMethodException e) {
                        e.printStackTrace();
                    }
                }
            }
        }

        private Function<JsonObject, Command> toCommand(Object instance, Method method) {
            Function<JsonObject, Command> recipe = data -> adminDB -> {
                try {
                    method.invoke(instance);
                } catch (IllegalAccessException |
                         InvocationTargetException e) {
                    throw new InvalidDataException(e.getMessage());
                }
            };

            return recipe;
        }

        private class Wathcer {
            private final Path toMonitor;

            public Wathcer(String toMonitor) {
                this.toMonitor = Paths.get(toMonitor);
            }

            private Path watch() throws ClassNotFoundException {
                try {

//                    File plugins = SRC_PATH.toFile();
//                    if (plugins.isDirectory()) {
//                        for (File jar : Objects.requireNonNull(plugins.listFiles())) {
//                            try {
//                                addJar(jar.getAbsolutePath());
//                            } catch (IOException e) {
//                                e.printStackTrace();
//                            }
//                        }
//                    }

                    WatchService watchService = FileSystems.getDefault().newWatchService();
                    toMonitor.register(watchService,
                            StandardWatchEventKinds.ENTRY_CREATE);

                    WatchKey key;
                    while ((key = watchService.take()) != null) {
                        for (WatchEvent<?> event : key.pollEvents()) {
                            if (StandardWatchEventKinds.ENTRY_CREATE == event.kind()) {
                                Path dir = (Path) key.watchable();
                                Path jarFile = dir.resolve((Path) event.context());
                                System.out.println(jarFile);

                                return jarFile;
                            }
                        }
                        key.reset();
                    }
                } catch (IOException e) {
                    throw new RuntimeException("Folder not found - Watcher");
                } catch (InterruptedException e) {
                    throw new RuntimeException("Thread interrupted");
                }

                return null;
            }
        }

        private class Loader {
            private final String interfaceName = "Callable";

            public Loader() {
            }


            public List<Class<?>> load(Path path) throws IOException, ClassNotFoundException {
                List<Class<?>> list = new ArrayList<>();
                Enumeration<JarEntry> entryEnumeration;
                Class<?> classToAdd;
                URL[] urls = {new URL("jar:file:" + path + "!/")};
                URLClassLoader cl = URLClassLoader.newInstance(urls);

                try (JarFile jar = new JarFile(new File(path.toString()))) {
                    entryEnumeration = jar.entries();

                    while (entryEnumeration.hasMoreElements()) {
                        JarEntry jarEntry = entryEnumeration.nextElement();

                        if (jarEntry.getName().endsWith(".class")) {
                            String className = jarEntry.getName().substring(0,
                                    jarEntry.getName().length() - 6);
                            className = className.replace('/', '.');
                            System.out.println(className);
                            Class<?> classInJar = cl.loadClass(className);

                            Class<?>[] interfaces = classInJar.getInterfaces();
                            for (Class<?> clazz : interfaces) {
                                if (clazz.getSimpleName().equals(this.interfaceName)) {
                                    ClassLoader classLoader = classInJar.getClassLoader();
                                    classToAdd = classLoader.loadClass(className);
                                    list.add(classToAdd);
                                }
                            }
                        }
                    }
                }

                return list;
            }
        }
    }
}
