package il.co.ILRD.crud_sql_n_nosql;

import com.sun.media.sound.InvalidDataException;
import il.co.ILRD.sql.database_manager.Queryable;

import javax.json.JsonObject;
import java.sql.*;

public class SqlCrudManager {
    private Connection databaseConnection;
    private final String databaseName;
    private final CompanyCRUDable companyCrud;
    private ProductCRUDable productCrud;

    public SqlCrudManager(String databaseName) {
        this.databaseName = databaseName;
        this.companyCrud = new CompanyCRUDable();
    }

    public void registerCompany(JsonObject json) throws InvalidDataException {
        this.companyCrud.create(json);
    }

    public void registerProduct(JsonObject json) throws InvalidDataException {
        this.productCrud.create(json);
    }

    /*===============================CompanyCrud==================================*/
    private class CompanyCRUDable implements CRUDable {
        @Override
        public void create(JsonObject json) throws InvalidDataException {
            String companyQuery = Queryable.create("Companies",
                    FieldsAndDefinitions.Companies_Fields.values,
                    json);

            String paymentQuery = Queryable.create("PaymentDetails",
                    FieldsAndDefinitions.PaymentDetails_Fields.values,
                    json);

            try (Statement statement = SqlCrudManager.this.databaseConnection.createStatement()) {
                statement.execute(companyQuery);
                statement.execute(paymentQuery);
            } catch (SQLException e) {
                throw new InvalidDataException("Companies CRUDable error");
            }

        }

        @Override
        public JsonObject read(JsonObject json) throws InvalidDataException {
            return null;
        }

        @Override
        public JsonObject update(JsonObject json) {
            return null;
        }

        @Override
        public void delete(JsonObject json) {

        }
    }

    /*===============================ProductCrud==============================*/
    private class ProductCRUDable implements CRUDable {

        @Override
        public void create(JsonObject json) {
//            String productQuery = Queryable.create("Products",
//                    FieldsAndDefinitions.Companies_Fields.values,
//                    FieldsAndDefinitions.Companies_Fields.values.length);
//
//            try (PreparedStatement statement = tableNames.get("Products").
//                    prepareStatement(productQuery, Statement.RETURN_GENERATED_KEYS)) {
//                statement.setInt(1, json.getInt("company_id"));
//                statement.setString(2, json.getString("product_name"));
//                statement.setString(3, json.getString("product_description"));
//                statement.executeUpdate();
//            } catch (SQLException e) {
//                throw new RuntimeException("Bad syntax product");
//            }
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

        }
    }
    /*==========================Private methods and classes=======================*/

    private void createDatabase(String url, String username, String password) {
        try {
            this.databaseConnection = DriverManager.getConnection(url, username, password);
            Statement stmt = this.databaseConnection.createStatement();
            stmt.execute(Queryable.queryCreateDatabase(this.databaseName));
        } catch (SQLException e) {
            throw new RuntimeException("Create database fail" + this.databaseName);
        }
    }

    private void createTable(String tableName, String[] fields, String[] definitions, String primaryKey) {
        try {
            Statement stmt = this.databaseConnection.createStatement();
            String sql = Queryable.queryCreateTable(tableName, fields, definitions, primaryKey);
            stmt.execute(sql);
        } catch (SQLException e) {
            throw new RuntimeException("Create table fail " + tableName);
        }
    }

    private void useDatabase() {
        try (Statement statement = this.databaseConnection.createStatement()) {
            statement.execute(Queryable.queryUseDatabase(this.databaseName));
        } catch (SQLException e) {
            throw new RuntimeException("Use database fail");
        }
    }

    public void start() {
        this.createDatabase("jdbc:mysql://localhost:3306/", "root", "password");
        this.useDatabase();

        this.createTable("Companies",
                FieldsAndDefinitions.Companies_Fields.values,
                FieldsAndDefinitions.Companies_Definitions.values,
                FieldsAndDefinitions.Companies_Fields.values[0]);

        this.createTable("Products",
                FieldsAndDefinitions.Products_Fields.values,
                FieldsAndDefinitions.Products_Definitions.values,
                FieldsAndDefinitions.Products_Fields.values[0]);

        this.createTable("PaymentDetails",
                FieldsAndDefinitions.PaymentDetails_Fields.values,
                FieldsAndDefinitions.PaymentDetails_Definitions.values,
                FieldsAndDefinitions.PaymentDetails_Fields.values[0]);
    }

    private enum FieldsAndDefinitions {
        Companies_Fields(
                new String[]{"company_name",
                        "company_address",
                        "contact_name",
                        "contact_phone",
                        "contact_email",
                        "service_fee"}

        ),
        Companies_Definitions(
                new String[]{"VARCHAR(255) UNIQUE",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "VARCHAR(255)"}
        ),
        Products_Fields(
                new String[]
                        {"product_id",
                                "company_name",
                                "product_name",
                                "product_description"}
        ),
        Products_Definitions(
                new String[]
                        {"BIGINT NOT NULL AUTO_INCREMENT",
                                "VARCHAR(255) UNIQUE",
                                "VARCHAR(255)",
                                "VARCHAR(255)"}
        ),
        PaymentDetails_Fields(
                new String[]
                        {"card_number",
                                "company_name",
                                "card_holder_name",
                                "ex_date",
                                "CVV"}

        ),
        PaymentDetails_Definitions(
                new String[]{"VARCHAR(255) UNIQUE",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "VARCHAR(255)"}
        );

        private final String[] values;

        public String[] getFieldsWithoutPrimaryKey() {
            String[] toReturn = new String[this.values.length - 1];

            for (int i = 1; i < this.values.length; ++i) {
                toReturn[i - 1] = this.values[i];
            }

            return toReturn;
        }

        FieldsAndDefinitions(String[] values) {
            this.values = values;
        }

    }
}
