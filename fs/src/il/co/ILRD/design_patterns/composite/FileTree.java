package il.co.ILRD.design_patterns.composite;


import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;


public class FileTree {
    private final DirectoryComposite directoryRoot;
    private int hierarchyCounter = 0;
    public FileTree(String path) {
        this.directoryRoot = new DirectoryComposite(path);
    }
    public void print(){
        this.directoryRoot.printName();
    }

    private interface FileSystemComponent{
        void printName();
    }

    private class FileLeaf implements FileSystemComponent{
        private final String name;
        private FileLeaf(String name){
            this.name = new File(name).getName();
        }
        @Override
        public void printName() {
            StringBuilder spaces = new StringBuilder();
            for (int i =0; i < hierarchyCounter; ++i){
                spaces.append("│  ");
            }
            System.out.println("└──" + spaces + name);
        }
    }

    private class DirectoryComposite implements FileSystemComponent{
        private final String name;
        private final List<FileSystemComponent> list;

        private DirectoryComposite(String name){
            this.name = name;
            this.list = new LinkedList<>();
            File dirFile = new File(name);
            File[] filesList = dirFile.listFiles();

            if(filesList == null){
                return;
            }

            for (File file: filesList){
                if(file.isDirectory()){
                    this.list.add(new DirectoryComposite(file.getAbsolutePath()));
                }
                else {
                    this.list.add(new FileLeaf(file.getAbsolutePath()));
                }
            }
        }

        @Override
        public void printName() {
            String nameOfDir = new File(this.name).getName();
            StringBuilder spaces = new StringBuilder();

            spaces.append("│  ".repeat(Math.max(0, hierarchyCounter)));

            System.out.println(spaces + nameOfDir);
            System.out.print("├──");
            ++hierarchyCounter;


            for (FileSystemComponent file : list){
                file.printName();
            }
            --hierarchyCounter;
        }
    }
}
