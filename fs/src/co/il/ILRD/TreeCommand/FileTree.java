package co.il.ILRD.TreeCommand;


import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;


public class FileTree {
    private final DirectoryComposite directoryRoot;
    private final int paddingIndex = 0;

    public FileTree(String path) throws FileNotFoundException {
        this.directoryRoot = new DirectoryComposite(path, paddingIndex);
    }

    public void print() {
        this.directoryRoot.printName();
    }

    private interface FileSystemComponent {
        public void printName();
    }

    private static class FileLeaf implements FileSystemComponent {
        private final String name;
        private int paddingIndex;

        private FileLeaf(String name, int index) {
            this.paddingIndex = index;
            this.name = name;
        }

        @Override
        public void printName() {
            for (int i = 0; i < paddingIndex; i++) {
                System.out.println(" ");
            }
            System.out.println(name);
        }
    }

    private static class DirectoryComposite implements FileSystemComponent {
        private final String name;
        private final String path;
        private int paddingIndex;
        private List<FileSystemComponent> list;

        private DirectoryComposite(String path, int index) throws FileNotFoundException {
            this.paddingIndex = index;
            this.path = path;
            File file = new File(path);
            this.name = file.getName();
            initList();
        }

        @Override
        public void printName() {
            for (int i = 0; i < paddingIndex; i++) {

            }
            System.out.println(name);
            for (FileSystemComponent print : list) {
                print.printName();
            }
        }

        private void initList() throws FileNotFoundException {
            this.list = new ArrayList<>();
            File currentDirectory = new File(this.path);
            File[] filesInDirectory = currentDirectory.listFiles();
            if (null != filesInDirectory) {
                int i = 0;
                for (i = 0; i < filesInDirectory.length - 1; ++i) {
                    if (filesInDirectory[i].isDirectory()) {
                        list.add(new DirectoryComposite ("├──" + filesInDirectory[i].getAbsolutePath() , ++this.paddingIndex));
                    } else {
                        list.add(new FileLeaf("├──" +filesInDirectory[i].getName(), ++this.paddingIndex));
                    }
                }
                ++i;
                if (filesInDirectory[i].isDirectory()) {
                    list.add(new DirectoryComposite("└──" + filesInDirectory[i].getAbsolutePath() , ++this.paddingIndex));
                } else {
                    list.add(new FileLeaf("└──" + filesInDirectory[i].getName(), ++this.paddingIndex));
                }
            }
        }
    }
}
