package il.co.ILRD.networking.HttpServer;

import com.sun.media.sound.InvalidDataException;

import javax.json.JsonObject;
import java.io.File;
import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.lang.reflect.Method;
import java.net.URL;
import java.net.URLClassLoader;
import java.nio.file.*;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;
import java.util.function.Function;
import java.util.jar.JarEntry;
import java.util.jar.JarFile;


public class PlugAndPlay implements Runnable { /*add a way to load classes that already exist in the folder*/
    private final Factory<String, JsonObject> factory;
    private final Loader jarLoader;
    private final Wathcer wathcer;
    private final String path;

    public PlugAndPlay(String path, Factory<String, JsonObject> factory) {
        this.factory = factory;
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

                    this.factory.add(cmd.getName(), recipe);
                } catch (InstantiationException | IllegalAccessException |
                         NoSuchMethodException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    private Function<JsonObject, Command> toCommand(Object instance, Method method) {
        Function<JsonObject, Command> recipe = data -> (sqlCrudManager, noSqlCrudManager) -> {
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
