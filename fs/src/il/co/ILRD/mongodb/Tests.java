package il.co.ILRD.mongodb;

import org.bson.Document;
import org.bson.types.ObjectId;
import org.junit.jupiter.api.*;

import javax.json.JsonObject;

public class Tests {
    private final MongoCRUD connection = new MongoCRUD("localhost", "Test", "resaurants");

    @BeforeEach
    void init() {
        this.connection.start();
    }

    @Test
    void test() {
        Restaurant create;
        ObjectId id;

        create = new Restaurant(null, "someUrl", "Happy", "Birthday", "Barchik", "!", "!", 5, "goodFood");
        create.setId(this.connection.create(create.toDocument()));
        id = create.getId();

        Restaurant toRead = new Restaurant(this.connection.read(id));
        System.out.println(toRead);

        Restaurant update = new Restaurant(null, "updatedUrl", "nice", "nice", "readtest", "!", "!", 5, "goodFood");
        this.connection.update(id, update.toDocument());
        update.setId(id);
        System.out.println(update);

        this.connection.delete(id);
    }

    @AfterEach
    void close() {
        this.connection.close();
    }

}

class Restaurant {
    private ObjectId id;
    private String url;
    private String address;
    private String addressLine;
    private String name;
    private String outcode;
    private String postcode;

    @Override
    public String toString() {
        return "Restaurant{" +
                "id=" + id +
                ", url='" + url + '\'' +
                ", address='" + address + '\'' +
                ", addressLine='" + addressLine + '\'' +
                ", name='" + name + '\'' +
                ", outcode='" + outcode + '\'' +
                ", postcode='" + postcode + '\'' +
                ", rating=" + rating +
                ", typeOfFood='" + typeOfFood + '\'' +
                '}';
    }

    private int rating;
    private String typeOfFood;

    public Restaurant(ObjectId id, String url, String address, String addressLine, String name, String outcode, String postcode, int rating, String typeOfFood) {
        this.id = id;
        this.url = url;
        this.address = address;
        this.addressLine = addressLine;
        this.name = name;
        this.outcode = outcode;
        this.postcode = postcode;
        this.rating = rating;
        this.typeOfFood = typeOfFood;
    }

    public Restaurant(Document doc) {
        this.id = (ObjectId) doc.get("_id");
        this.url = (String) doc.get("url");
        this.address = (String) doc.get("address");
        this.addressLine = (String) doc.get("address line 2");
        this.name = (String) doc.get("name");
        this.outcode = (String) doc.get("outocode");
        this.postcode = (String) doc.get("postcode");
        this.rating = (int) doc.get("rating");
        this.typeOfFood = (String) doc.get("type_of_food");
    }

    public Document toDocument() {
        Document doc = new Document();

        if (null != this.id) {
            doc.put("_id", this.id);
        }

        doc.put("url", this.url);
        doc.put("address", this.address);
        doc.put("address line 2", this.addressLine);
        doc.put("name", this.name);
        doc.put("outcode", this.outcode);
        doc.put("postcode", this.postcode);
        doc.put("rating", this.rating);
        doc.put("type_of_food", this.typeOfFood);

        return doc;
    }

    public Restaurant(JsonObject json) {
        this(MongoCRUD.parseJsonToDocument(json));
    }

    public ObjectId getId() {
        return this.id;
    }

    public void setId(ObjectId id) {
        this.id = id;
    }

    public String getUrl() {
        return url;
    }

    public void setUrl(String url) {
        this.url = url;
    }

    public String getAddress() {
        return address;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public String getAddressLine() {
        return addressLine;
    }

    public void setAddressLine(String addressLine) {
        this.addressLine = addressLine;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getOutcode() {
        return outcode;
    }

    public void setOutcode(String outcode) {
        this.outcode = outcode;
    }

    public String getPostcode() {
        return postcode;
    }

    public void setPostcode(String postcode) {
        this.postcode = postcode;
    }

    public int getRating() {
        return rating;
    }

    public void setRating(int rating) {
        this.rating = rating;
    }

    public String getTypeOfFood() {
        return typeOfFood;
    }

    public void setTypeOfFood(String typeOfFood) {
        this.typeOfFood = typeOfFood;
    }
}
