package il.co.ILRD.DesignPatterns.Composite;

import org.junit.jupiter.api.Test;

import java.io.FileNotFoundException;

public class TreeCommandTest {
    @Test
    public void TU1() throws FileNotFoundException {
       FileTree current = new FileTree(System.getProperty("user.dir"));
        current.print();
    }
}
