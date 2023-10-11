package il.co.ILRD.sql.mockClasses;

import java.sql.*;

public interface CRUD {
    void create(Recordable toCreate);

    Recordable read(Recordable toRead);

    void update(Recordable toUpdate);

    void delete(Recordable toDelete);
}
