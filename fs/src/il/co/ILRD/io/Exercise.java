package il.co.ILRD.io;

import java.io.IOException;
import java.nio.file.*;
import java.io.File;
import java.util.Scanner;

public class Exercise {

    public void watchFolderAndCopy() throws IOException, InterruptedException {
        Path pathToMonitor = Paths.get("/home/barchik/Mygit/bar.shadkhin/fs/src/co/il/ILRD/IO/Original");
        Path pathToBackup = Paths.get("/home/barchik/Mygit/bar.shadkhin/fs/src/co/il/ILRD/IO/Backup");

        WatchService watcher = FileSystems.getDefault().newWatchService();
        pathToMonitor.register(watcher,StandardWatchEventKinds.ENTRY_CREATE);

        WatchKey key;
        while ((key = watcher.take()) != null) {
            for (WatchEvent<?> event : key.pollEvents()) {
                if (StandardWatchEventKinds.ENTRY_CREATE == event.kind()){
                    File fileToBackup = new File(String.valueOf( event.context()));
                }
            }
            key.reset();
        }


    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String line = scanner.nextLine();
        System.out.println("You entered: " + line);
    }
}