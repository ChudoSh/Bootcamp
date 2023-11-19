package il.co.ILRD.mongodb;

import com.mongodb.client.MongoClients;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.MongoClient;
import com.mongodb.client.model.Filters;
import com.mongodb.client.result.InsertOneResult;
import org.bson.Document;
import org.bson.types.ObjectId;

import javax.json.JsonObject;

public class MongoCRUD {
    private MongoClient mongoClient;
    private MongoDatabase database;
    private MongoCollection<Document> collection;
    private String DBName;
    private String url;
    private String collectionName;

    public MongoCRUD(String url, String DBName, String collectionName) {
        this.DBName = DBName;
        this.url = url;
        this.collectionName = collectionName;
    }

    public void start() {
        this.mongoClient = MongoClients.create("mongodb://" + this.url);
        this.useDatabase(this.DBName);
        this.setCollection(this.collectionName);
        System.out.println("Connected to the database");
    }

    public void close() {
        this.mongoClient.close();
    }


    public MongoDatabase getDatabase() {
        return this.database;
    }

    public void useDatabase(String DBName) {
        this.database = this.mongoClient.getDatabase(DBName);
        this.DBName = DBName;
    }

    public void setCollection(String collectionName) {
        this.collection = this.database.getCollection(collectionName);
    }


    public ObjectId create(Document doc) {
        return this.collection.insertOne(doc).getInsertedId().asObjectId().getValue();
    }

    public Document read(ObjectId id) {
        return this.collection.find(Filters.eq("_id", id)).first();
    }

    public Document update(ObjectId id, Document toUpdate) {
        return this.collection.findOneAndUpdate(Filters.eq("_id", id), new Document("$set", toUpdate));
    }

    public Document delete(ObjectId id) {
        return this.collection.findOneAndDelete(Filters.eq("_id", id));
    }

    public static Document parseJsonToDocument(JsonObject json) {
        return Document.parse(json.toString());
    }
}
