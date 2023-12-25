import javax.json.JsonObject;

public interface Cruddable {
    void create(JsonObject json);

    JsonObject read(JsonObject json);

    JsonObject update(JsonObject json);

    void delete(JsonObject json);
}
