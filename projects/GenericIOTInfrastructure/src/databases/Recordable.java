package databases;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;

public interface Recordable {
    Recordable getRecordFromResultSet(ResultSet result) throws SQLException;


    String getPrimaryKeyName();

    Connection getConnection();

    void createRecord();

    Recordable readRecord();

    void updateRecord();

    void deleteRecord();
}