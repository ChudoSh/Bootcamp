package il.co.ILRD.crud_sql_n_nosql;

import com.sun.media.sound.InvalidDataException;

import javax.json.JsonObject;

public interface CRUDable {
    void create(JsonObject json) throws InvalidDataException;

    JsonObject read(JsonObject json) throws InvalidDataException;

    JsonObject update(JsonObject json);

    void delete(JsonObject json);
}
