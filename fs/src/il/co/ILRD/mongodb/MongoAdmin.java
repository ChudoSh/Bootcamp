package il.co.ILRD.mongodb;

public class MongoAdmin {
    private final String url;

    public MongoAdmin(String url) {
        this.url = url;
    }
//
//    public void createCollections(String databaseName, String collectionName) {
//        try (MongoClient mongoClient = MongoClients.create("mongodb://" + this.url)) {
//            MongoDatabase mongoDatabase = mongoClient.getDatabase(databaseName);
//            mongoDatabase.createCollection(collectionName);
//        }
//    }
//
//    public ObjectId create(String databaseName, String collectionName, Document data) {
//        try (MongoClient mongoClient = MongoClients.create("mongodb://" + this.url)) {
//            MongoDatabase mongoDatabase = mongoClient.getDatabase(databaseName);
//            return mongoDatabase.getCollection(collectionName).
//                    insertOne(data).getInsertedId().asObjectId().getValue();
//
//        }
//    }
//
//    public Document read(String databaseName, String collectionName, ObjectId id) {
//        try (MongoClient mongoClient = MongoClients.create("mongodb://" + this.url)) {
//            MongoDatabase mongoDatabase = mongoClient.getDatabase(databaseName);
//            return mongoDatabase.getCollection(collectionName).find(
//                    Filters.eq("_id", id)).first();
//        }
//    }
//
//    public Document update(String databaseName, String collectionName, ObjectId id, Document update) {
//        try (MongoClient mongoClient = MongoClients.create("mongodb://" + this.url)) {
//            MongoDatabase mongoDatabase = mongoClient.getDatabase(databaseName);
//            return mongoDatabase.getCollection(collectionName).findOneAndUpdate(
//                    Filters.eq("_id", id),
//                    new Document("$set", update));
//        }
//    }
//
//    public Document delete(String databaseName, String collectionName, ObjectId id) {
//        try (MongoClient mongoClient = MongoClients.create("mongodb://" + this.url)) {
//            MongoDatabase mongoDatabase = mongoClient.getDatabase(databaseName);
//            return mongoDatabase.getCollection(collectionName).findOneAndDelete(
//                    Filters.eq("_id", id));
//        }
//    }
}
