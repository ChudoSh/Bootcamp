package il.co.ILRD.networking.HttpServer;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class Tests {
    Thread create;
    Thread read;
    Thread update;
    Thread delete;

    @BeforeEach
    void init(){
        create = new Thread(new CreateTest());
        read = new Thread(new ReadTest());
        update = new Thread(new UpdateTest());
        delete = new Thread(new DeleteTest());
    }

    @Test
    void create(){
        create.start();
    }
}
