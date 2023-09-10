package il.co.ILRD.Java2C;
import java.io.File;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.io.IOException;
import java.io.RandomAccessFile;
import java.nio.MappedByteBuffer;
import java.nio.channels.FileChannel;

public class OutputTest {
        public static void main(String[] args) {
            Path path1 = Paths.get("/home/barchik/Mygit/bar.shadkhin/fs/src/co/il/ILRD/Java2C/JavaToSee.text");
            Path path2 = Paths.get("/home/barchik/Mygit/bar.shadkhin/fs/src/co/il/ILRD/Java2C/JavaTwoC/j2c_output.text");
            compare(path1,path2);
        }
        public static void compare(Path path1, Path path2) {
            try (RandomAccessFile randomAccessFile1 = new RandomAccessFile(path1.toFile(), "r");
                 RandomAccessFile randomAccessFile2 = new RandomAccessFile(path2.toFile(), "r");){
                FileChannel ch1 = randomAccessFile1.getChannel();
                FileChannel ch2 = randomAccessFile2.getChannel();
                if (ch1.size() != ch2.size()) {
                    System.out.println("Both files have different content");
                }
                long size = ch1.size();
                MappedByteBuffer m1 = ch1.map(FileChannel.MapMode.READ_ONLY, 0L, size);
                MappedByteBuffer m2 = ch2.map(FileChannel.MapMode.READ_ONLY, 0L, size);
                if (m1.equals(m2)) {
                    System.out.println("Both files have same content");
                }
            }
            catch(Exception e){
                System.out.println(e);
            }
        }
}
