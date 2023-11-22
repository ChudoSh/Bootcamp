package il.co.ILRD.crud_sql_n_nosql;

import javax.json.JsonObject;

public interface CRUDable {
    void create(JsonObject json);

    JsonObject read(JsonObject json);

    JsonObject update(JsonObject json);

    void delete(JsonObject json);
}
