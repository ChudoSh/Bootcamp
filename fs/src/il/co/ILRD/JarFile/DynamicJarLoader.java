package il.co.ILRD.JarFile;/*
Dev: BarSh
Rev: Barak
Date: 11.9.23
Status: Approved
*/

import java.io.File;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Enumeration;
import java.util.List;
import java.util.jar.*;
import java.net.URL;
import java.net.URLClassLoader;;

public class DynamicJarLoader {
    private final String interfaceName;
    private final String path;

    public DynamicJarLoader(String interfaceName, String path) {
        this.interfaceName = interfaceName;
        this.path = path;
    }

    public List<Class<?>> load() throws IOException, ClassNotFoundException {
        List<Class<?>> list = new ArrayList<>();
        Enumeration<JarEntry> entryEnumeration;
        Class<?> classToAdd;
        URL[] urls = { new URL("jar:file:" + this.path+ "!/")};
        URLClassLoader cl = URLClassLoader.newInstance(urls);

        try (JarFile jar = new JarFile(new File(this.path))) {
            entryEnumeration = jar.entries();

            while (entryEnumeration.hasMoreElements()) {
                JarEntry jarEntry = entryEnumeration.nextElement();

                if (jarEntry.getName().endsWith(".class")) {
                    String className = jarEntry.getName().substring(0, jarEntry.getName().length() - 6);
                    className = className.replace('/', '.');
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


    public static void main(String[] args) throws IOException, ClassNotFoundException, InstantiationException, IllegalAccessException {
        DynamicJarLoader loader = new DynamicJarLoader("SomeInterface", "/home/barchik/Mygit/bar.shadkhin/fs/src/il/co/ILRD/JarFile/JarFile/out/production/JarFile/MyJar.jar");
        List<Class<?>> list = loader.load();

        for (Object obj : list) {
            obj = new SomeClass();
            ((SomeClass) obj).sayHi();
        }
    }
}
