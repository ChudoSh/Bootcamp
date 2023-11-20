package il.co.ILRD.mongodb;

import il.co.ILRD.sql.database_manager.CompanyRecord;
import org.bson.Document;
import org.junit.jupiter.api.BeforeAll;
import org.junit.jupiter.api.Test;

import java.util.List;
import java.util.Map;

public class AdminCrudTests {
    MongoAdmin mongoAdmin;

    @BeforeAll
    void init() {
        mongoAdmin = new MongoAdmin("localhost");
    }

    @Test
    void test() {
    }

}

class Company {
    private String companyName;
    private Map<String, Product> productMap;

    public Company(String companyName) {
        this.companyName = companyName;
    }

    public String getCompanyName() {
        return companyName;
    }

    public void setCompanyName(String companyName) {
        this.companyName = companyName;
    }

    public Product getProduct(String productName) {
        return productMap.get(productName);
    }

    public void addProduct(Product product) {
        return productMap.put(product.getName(), product);
    }


}

class Product {
    private String productName;
    private Document users;

}