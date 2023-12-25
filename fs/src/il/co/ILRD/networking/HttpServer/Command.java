package il.co.ILRD.networking.HttpServer;

import com.sun.media.sound.InvalidDataException;
import il.co.ILRD.crud_sql_n_nosql.NoSqlCrudManager;
import il.co.ILRD.crud_sql_n_nosql.SqlCrudManager;

public interface Command {
    void exec(SqlCrudManager sql, NoSqlCrudManager noSql) throws InvalidDataException;
}
