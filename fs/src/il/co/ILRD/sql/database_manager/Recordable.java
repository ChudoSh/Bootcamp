package il.co.ILRD.sql.database_manager;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;

public interface Recordable {
    Recordable getRecordFromResultSet(ResultSet result) throws SQLException;

    String getPrimaryKeyName();

    void createRecord();

    Recordable readRecord();

    void updateRecord();

    void deleteRecord();
}