package il.co.ILRD.Jar;

import java.io.File;
import java.io.IOException;
import java.net.URL;
import java.util.Enumeration;
import java.util.List;
import java.util.jar.*;
import java.net.URLClassLoader;

public class DynamicJarLoader {
    String interfaceName;
    String path;

    public DynamicJarLoader(String interfaceName, String path) {
        this.interfaceName = interfaceName;
        this.path = path;
    }

    public void load() throws IOException, ClassNotFoundException {
        JarFile jar = new JarFile(new File(this.path));
        Enumeration<JarEntry> classFiles = jar.entries();

        URL[] urls = {new URL("jar:file:" + this.path + "!/")};
        URLClassLoader classLoader = URLClassLoader.newInstance(urls);

        while (classFiles.hasMoreElements()) {
            JarEntry je = classFiles.nextElement();
            String className = je.getName().substring(0, je.getName().length() - 6);
            className = className.replace('/', '.');
            Class c = classLoader.loadClass(className);
            if (0 == className.compareTo(this.interfaceName)) {

            }

        }

//        private List<String> getClassNames() {
//
//        }


    }
}
