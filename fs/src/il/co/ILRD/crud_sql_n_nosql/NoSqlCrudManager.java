package il.co.ILRD.crud_sql_n_nosql;

import com.mongodb.client.MongoClient;
import com.mongodb.client.MongoClients;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.model.Filters;
import org.bson.Document;

import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;
import java.util.Map;

public class NoSqlCrudManager {
    private String url;
    private CompanyCRUDable companyCrud;
    private IOTCRUDable iotCrud;
    private UpdateCRUDable updateCrud;
    private final String USERS_COLLECTION = "users";
    private final String UPDATES_COLLECTION = "updates";

    public NoSqlCrudManager(String url) {
        this.url = url;
        this.companyCrud = new CompanyCRUDable();
        this.iotCrud = new IOTCRUDable();
        this.updateCrud = new UpdateCRUDable();
    }

    public void registerCompany(JsonObject json) {
        this.companyCrud.create(json);
    }

    public void registerProduct(JsonObject json) {
    }

    public void registerIOT(JsonObject json) {
        this.iotCrud.create(json);
    }

    public void registerUpdate(JsonObject json) {
        this.updateCrud.create(json);
    }

    private JsonObject createDummyJsonObject(String companyName) {
        return Json.createObjectBuilder().
                add("company_name", companyName).
                add("product_name", "dummy").build();

    }

    private JsonObject convertDocumentToJson(Document document) {
        if (null == document) {
            return null;
        }

        JsonObjectBuilder jsonObjectBuilder = Json.createObjectBuilder();

        for (Map.Entry<String, Object> entry : document.entrySet()) {
            addJsonEntry(jsonObjectBuilder, entry.getKey(), entry.getValue());
        }

        return jsonObjectBuilder.build();
    }

    private void addJsonEntry(JsonObjectBuilder jsonObjectBuilder, String key, Object value) {
        if (value instanceof Document) {
            jsonObjectBuilder.add(key, convertDocumentToJson((Document) value));
        } else {
            jsonObjectBuilder.add(key, value.toString());
        }
    }

    private class CompanyCRUDable implements CRUDable {
        @Override
        public void create(JsonObject json) {
            try (MongoClient mongoClient = MongoClients.create("mongodb://" + NoSqlCrudManager.this.url)) {
                MongoDatabase mongoDatabase = mongoClient.getDatabase(json.getString("company_name"));

                mongoDatabase.createCollection(NoSqlCrudManager.this.USERS_COLLECTION);
                mongoDatabase.createCollection(NoSqlCrudManager.this.UPDATES_COLLECTION);

                NoSqlCrudManager.this.iotCrud.create(createDummyJsonObject(json.getString("company_name")));
                NoSqlCrudManager.this.updateCrud.create(createDummyJsonObject(json.getString("company_name")));
            }
        }

        @Override
        public JsonObject read(JsonObject json) {
            return null;
        }

        @Override
        public JsonObject update(JsonObject json) {
            return null;
        }

        @Override
        public void delete(JsonObject json) {
            try (MongoClient mongoClient = MongoClients.create("mongodb://" + NoSqlCrudManager.this.url)) {
                MongoDatabase mongoDatabase = mongoClient.getDatabase(json.getString("company_name"));
                mongoDatabase.drop();
            }
        }
    }

    private class IOTCRUDable implements CRUDable {
        @Override
        public void create(JsonObject json) {
            try (MongoClient mongoClient = MongoClients.create("mongodb://" + NoSqlCrudManager.this.url)) {
                MongoDatabase mongoDatabase = mongoClient.getDatabase(json.getString("company_name"));
                mongoDatabase.getCollection(NoSqlCrudManager.this.USERS_COLLECTION).
                        insertOne(Document.parse(json.toString()));
            }
        }

        @Override
        public JsonObject read(JsonObject json) {
            try (MongoClient mongoClient = MongoClients.create("mongodb://" + NoSqlCrudManager.this.url)) {
                MongoDatabase mongoDatabase = mongoClient.getDatabase(json.getString("company_name"));

                Document doc = mongoDatabase.getCollection(NoSqlCrudManager.this.USERS_COLLECTION).find(
                        Filters.eq(json.getString("_id"))).first();

                return NoSqlCrudManager.this.convertDocumentToJson(doc);
            }
        }

        @Override
        public JsonObject update(JsonObject json) {
            try (MongoClient mongoClient = MongoClients.create("mongodb://" + NoSqlCrudManager.this.url)) {
                MongoDatabase mongoDatabase = mongoClient.getDatabase(json.getString("company_name"));

                Document doc = mongoDatabase.getCollection(NoSqlCrudManager.this.USERS_COLLECTION).findOneAndUpdate(
                        Filters.eq(json.getString("_id")), Document.parse(String.valueOf(json)));

                return NoSqlCrudManager.this.convertDocumentToJson(doc);
            }
        }

        @Override
        public void delete(JsonObject json) {
            try (MongoClient mongoClient = MongoClients.create("mongodb://" + NoSqlCrudManager.this.url)) {
                MongoDatabase mongoDatabase = mongoClient.getDatabase(json.getString("company_name"));
                mongoDatabase.getCollection(NoSqlCrudManager.this.USERS_COLLECTION).
                        findOneAndDelete(Document.parse(json.toString()));
            }
        }

    }


    private class UpdateCRUDable implements CRUDable {

        @Override
        public void create(JsonObject json) {
            try (MongoClient mongoClient = MongoClients.create("mongodb://" + NoSqlCrudManager.this.url)) {
                MongoDatabase mongoDatabase = mongoClient.getDatabase(json.getString("company_name"));
                mongoDatabase.getCollection(NoSqlCrudManager.this.UPDATES_COLLECTION).
                        insertOne(Document.parse(json.toString()));
            }
        }

        @Override
        public JsonObject read(JsonObject json) {
            try (MongoClient mongoClient = MongoClients.create("mongodb://" + NoSqlCrudManager.this.url)) {
                MongoDatabase mongoDatabase = mongoClient.getDatabase(json.getString("company_name"));

                Document doc = mongoDatabase.getCollection(NoSqlCrudManager.this.UPDATES_COLLECTION).find(
                        Filters.eq(json.getString("_id"))).first();

                return NoSqlCrudManager.this.convertDocumentToJson(doc);
            }
        }

        @Override
        public JsonObject update(JsonObject json) {
            try (MongoClient mongoClient = MongoClients.create("mongodb://" + NoSqlCrudManager.this.url)) {
                MongoDatabase mongoDatabase = mongoClient.getDatabase(json.getString("company_name"));

                Document doc = mongoDatabase.getCollection(NoSqlCrudManager.this.UPDATES_COLLECTION).findOneAndUpdate(
                        Filters.eq(json.getString("_id")), Document.parse(String.valueOf(json)));

                return NoSqlCrudManager.this.convertDocumentToJson(doc);
            }
        }

        @Override
        public void delete(JsonObject json) {
            try (MongoClient mongoClient = MongoClients.create("mongodb://" + NoSqlCrudManager.this.url)) {
                MongoDatabase mongoDatabase = mongoClient.getDatabase(json.getString("company_name"));
                mongoDatabase.getCollection(NoSqlCrudManager.this.UPDATES_COLLECTION).
                        findOneAndDelete(Document.parse(json.toString()));
            }
        }
    }
}

