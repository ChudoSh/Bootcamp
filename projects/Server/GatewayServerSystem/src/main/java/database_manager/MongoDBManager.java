package database_manager;

import Interfaces.Cruddable;
import com.mongodb.client.MongoClient;
import com.mongodb.client.MongoClients;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.model.Filters;
import org.bson.Document;

import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;
import java.util.Map;

public class MongoDBManager {
    private final String url;
    private final CompanyCRUDable companyCrud;
    private final IOTCRUDable iotCrud;
    private final UpdateCRUDable updateCrud;
    private final String USERS_COLLECTION = "users";
    private final String UPDATES_COLLECTION = "updates";

    public MongoDBManager(String url) {
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

    private class CompanyCRUDable implements Cruddable {
        @Override
        public void create(JsonObject json) {
            try (MongoClient mongoClient = MongoClients.create("mongodb://" + MongoDBManager.this.url)) {
                MongoDatabase mongoDatabase = mongoClient.getDatabase(json.getString("company_name"));

                mongoDatabase.createCollection(MongoDBManager.this.USERS_COLLECTION);
                mongoDatabase.createCollection(MongoDBManager.this.UPDATES_COLLECTION);

                MongoDBManager.this.iotCrud.create(createDummyJsonObject(json.getString("company_name")));
                MongoDBManager.this.updateCrud.create(createDummyJsonObject(json.getString("company_name")));
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
            try (MongoClient mongoClient = MongoClients.create("mongodb://" + MongoDBManager.this.url)) {
                MongoDatabase mongoDatabase = mongoClient.getDatabase(json.getString("company_name"));
                mongoDatabase.drop();
            }
        }
    }

    private class IOTCRUDable implements Cruddable{
        @Override
        public void create(JsonObject json) {
            try (MongoClient mongoClient = MongoClients.create("mongodb://" + MongoDBManager.this.url)) {
                MongoDatabase mongoDatabase = mongoClient.getDatabase(json.getString("company_name"));
                mongoDatabase.getCollection(MongoDBManager.this.USERS_COLLECTION).
                        insertOne(Document.parse(json.toString()));
            }
        }

        @Override
        public JsonObject read(JsonObject json) {
            try (MongoClient mongoClient = MongoClients.create("mongodb://" + MongoDBManager.this.url)) {
                MongoDatabase mongoDatabase = mongoClient.getDatabase(json.getString("company_name"));

                Document doc = mongoDatabase.getCollection(MongoDBManager.this.USERS_COLLECTION).find(
                        Filters.eq(json.getString("_id"))).first();

                return MongoDBManager.this.convertDocumentToJson(doc);
            }
        }

        @Override
        public JsonObject update(JsonObject json) {
            try (MongoClient mongoClient = MongoClients.create("mongodb://" + MongoDBManager.this.url)) {
                MongoDatabase mongoDatabase = mongoClient.getDatabase(json.getString("company_name"));

                Document doc = mongoDatabase.getCollection(MongoDBManager.this.USERS_COLLECTION).findOneAndUpdate(
                        Filters.eq(json.getString("_id")), Document.parse(String.valueOf(json)));

                return MongoDBManager.this.convertDocumentToJson(doc);
            }
        }

        @Override
        public void delete(JsonObject json) {
            try (MongoClient mongoClient = MongoClients.create("mongodb://" + MongoDBManager.this.url)) {
                MongoDatabase mongoDatabase = mongoClient.getDatabase(json.getString("company_name"));
                mongoDatabase.getCollection(MongoDBManager.this.USERS_COLLECTION).
                        findOneAndDelete(Document.parse(json.toString()));
            }
        }

    }


    private class UpdateCRUDable implements Cruddable {

        @Override
        public void create(JsonObject json) {
            try (MongoClient mongoClient = MongoClients.create("mongodb://" + MongoDBManager.this.url)) {
                MongoDatabase mongoDatabase = mongoClient.getDatabase(json.getString("company_name"));
                mongoDatabase.getCollection(MongoDBManager.this.UPDATES_COLLECTION).
                        insertOne(Document.parse(json.toString()));
            }
        }

        @Override
        public JsonObject read(JsonObject json) {
            try (MongoClient mongoClient = MongoClients.create("mongodb://" + MongoDBManager.this.url)) {
                MongoDatabase mongoDatabase = mongoClient.getDatabase(json.getString("company_name"));

                Document doc = mongoDatabase.getCollection(MongoDBManager.this.UPDATES_COLLECTION).find(
                        Filters.eq(json.getString("_id"))).first();

                return MongoDBManager.this.convertDocumentToJson(doc);
            }
        }

        @Override
        public JsonObject update(JsonObject json) {
            try (MongoClient mongoClient = MongoClients.create("mongodb://" + MongoDBManager.this.url)) {
                MongoDatabase mongoDatabase = mongoClient.getDatabase(json.getString("company_name"));

                Document doc = mongoDatabase.getCollection(MongoDBManager.this.UPDATES_COLLECTION).findOneAndUpdate(
                        Filters.eq(json.getString("_id")), Document.parse(String.valueOf(json)));

                return MongoDBManager.this.convertDocumentToJson(doc);
            }
        }

        @Override
        public void delete(JsonObject json) {
            try (MongoClient mongoClient = MongoClients.create("mongodb://" + MongoDBManager.this.url)) {
                MongoDatabase mongoDatabase = mongoClient.getDatabase(json.getString("company_name"));
                mongoDatabase.getCollection(MongoDBManager.this.UPDATES_COLLECTION).
                        findOneAndDelete(Document.parse(json.toString()));
            }
        }
    }
}

