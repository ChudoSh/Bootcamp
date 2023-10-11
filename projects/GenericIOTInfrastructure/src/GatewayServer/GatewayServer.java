package GatewayServer;

import com.sun.media.sound.InvalidDataException;
import databases.AdminDB;
import databases.CRUD;
import databases.CompanyRecord;
import hashmap.Pair;
import thread_pool.ThreadPool;

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
import java.util.Map.Entry;
import java.util.function.Function;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;


public class GatewayServer {
    private MultiProtocolServer multiProtocolServer;
    private RequestHandler requestHandler;
    private PlugAndPlay plugAndPlay;
    private static AdminDB adminDB;

    public GatewayServer(int numOfThreads) throws IOException {
        this.requestHandler = new RequestHandler(numOfThreads);
        this.multiProtocolServer = new MultiProtocolServer();
        this.plugAndPlay = new PlugAndPlay("/home/barchik/Mygit/bar.shadkhin/fs/src/il/co/ILRD/networking/GatewayServer/Mock data");
        this.multiProtocolServer.addTCPConnection(9090);

        this.multiProtocolServer.start();
        this.plugAndPlay.start();
        this.adminDB = new AdminDB("testdamin");
        this.adminDB.createDatabase("jdbc:mysql://localhost:3306/", "root", "password");
        String[] definitions =
                {"BIGINT NOT NULL AUTO_INCREMENT",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "BIGINT"};
        String[] tableFields =
                {"company_id",
                        "company_name",
                        "company_address",
                        "contact_name",
                        "contact_phone",
                        "contact_email",
                        "service_fee"};
        this.adminDB.createTable("Companies", tableFields, definitions, "company_id", "root", "password");
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
        void exec(CRUD database) throws InvalidDataException;
    }

    private static class RequestHandler {
        private ThreadPool threadPool;
        private Factory<String, String> factory;
        private static final String fileDir = "/home/barchik/Mygit/bar.shadkhin/fs/src/il/co/ILRD/networking/GatewayServer/Mock data/mocodata.txt";

        private RequestHandler(int numOfThreads) {
            this.threadPool = new ThreadPool(numOfThreads);
            this.factory = new Factory<>();
            this.factory.add("RegisterCompany", new RegisterCompany());
//            this.factory.add("RegisterProduct", new RegisterProduct());
//            this.factory.add("RegisterIOT", new RegisterIOT());
//            this.factory.add("Update", new Update());
        }

        private void handle(ByteBuffer buffer, Communicator communicator) {
            this.threadPool.submit(this.createRunnable(buffer, communicator), ThreadPool.Priority.DEFAULT);
        }

        private Entry<String, String> parse(String request) {
            System.out.println("In parser " + request);
            String[] parsedRequest = request.split("@", 2);

            if (parsedRequest.length <= 1) {
                return null;
            }

            return Pair.of(parsedRequest[0], parsedRequest[1]);
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

        private Runnable createRunnable(ByteBuffer buffer, Communicator communicator) {
            return () -> {
                try {
                    String request = new String(buffer.array(), 0, buffer.remaining());
                    System.out.println("In createRunnable " + request);

                    Entry<String, String> newEntry = this.parse(request);
                    if (null == newEntry) {
                        communicator.send(ByteBuffer.wrap("Failed Parse".getBytes()));
                        return;
//                        throw new InvalidDataException(");
                    }

                    Command cmd = this.factory.create(newEntry.getKey(), newEntry.getValue());
                    if (null == cmd) {
                        communicator.send(ByteBuffer.wrap("No Command".getBytes()));
                        return;
//                        throw new InvalidDataException("No Valid Command");
                    }

                    cmd.exec(GatewayServer.adminDB);
                    communicator.send(ByteBuffer.wrap("Sent Successfully".getBytes()));

                } catch (InvalidDataException e) {
                    communicator.send(ByteBuffer.wrap(e.getMessage().getBytes()));
                }
            };
        }

        private static class RegisterCompany implements Function<String, Command> {
            @Override
            public Command apply(String data) {
                return adminDB -> {
                    adminDB.create(CompanyRecord.of(data, GatewayServer.adminDB.getDatabaseConnection()));
                };
            }
        }

//        private static class RegisterProduct implements Function<String, Command> {
//            @Override
//            public Command apply(String data) {
//                return () -> {
//                    try {
//                        FileWriter writer = new FileWriter(fileDir);
//                        writer.write("Register Proudct: " + data);
//                        writer.close();
//                    } catch (IOException e) {
//                        throw new RuntimeException(e);
//                    }
//                };
//            }
//        }
//
//        private static class RegisterIOT implements Function<String, Command> {
//            @Override
//            public Command apply(String data) {
//                return () -> {
//                    try {
//                        FileWriter writer = new FileWriter(fileDir);
//                        writer.write("Register IOT: " + data);
//                        writer.close();
//                    } catch (IOException e) {
//                        throw new RuntimeException(e);
//                    }
//                };
//            }
//        }
//
//        private static class Update implements Function<String, Command> {
//            @Override
//            public Command apply(String data) {
//                return () -> {
//                    try {
//                        FileWriter writer = new FileWriter(fileDir);
//                        writer.write("Update: " + data);
//                        writer.close();
//                    } catch (IOException e) {
//                        throw new RuntimeException(e);
//                    }
//                };
//            }
//        }

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
                GatewayServer.this.handle(communicator.receive(), communicator);
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
                        Function<String, GatewayServer.Command> recipe = toCommand(obj, method);
                        System.out.println("cmd.name " + cmd.getName());

                        GatewayServer.this.requestHandler.
                                factory.add(cmd.getName(), recipe);

                    } catch (InstantiationException | IllegalAccessException |
                             NoSuchMethodException e) {
                        e.printStackTrace();
                    }
                }
            }
        }

        private Function<String, GatewayServer.Command> toCommand(Object instance, Method method) {
            Function<String, GatewayServer.Command> recipe = data -> adminDB -> {
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
            private WatchService watchService;

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

                    this.watchService =
                            FileSystems.getDefault().newWatchService();
                    toMonitor.register(this.watchService,
                            StandardWatchEventKinds.ENTRY_CREATE);

                    WatchKey key;
                    while ((key = this.watchService.take()) != null) {
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
