package il.co.ILRD.sql.database_manager;

import java.sql.Connection;

public interface CRUD {
    void create(Recordable toCreate);

    Recordable read(Recordable toRead);

    void update(Recordable toUpdate);

    void delete(Recordable toDelete);

    Connection getDatabaseConnection();
}
