package il.co.ILRD.crud_sql_n_nosql;

import il.co.ILRD.sql.database_manager.Queryable;

import javax.json.Json;
import javax.json.JsonObject;
import javax.json.JsonObjectBuilder;
import javax.json.JsonArray;
import java.math.BigDecimal;
import java.sql.*;
import java.util.HashMap;
import java.util.Map;

public class SqlCrudManager {
    private Connection databaseConnection;
    private final String databaseName;
    private final Map<String, Connection> tableNames;
    private CompanyCRUDable companyCrud;
    private ProductCRUDable productCrud;

    public SqlCrudManager(String databaseName) {
        this.databaseName = databaseName;
        this.tableNames = new HashMap<>();
        this.companyCrud = new CompanyCRUDable();
    }

    public void registerCompany(JsonObject json) {
        this.companyCrud.create(json);
    }

    public void registerProduct(JsonObject json) {
        this.productCrud.create(json);
    }


    private class CompanyCRUDable implements CRUDable {
        @Override
        public void create(JsonObject json) {
            String companyQuery = Queryable.create("Companies",
                    FieldsAndDefinitions.Companies_Fields.values,
                    FieldsAndDefinitions.Companies_Fields.values.length);
            String paymentQuery = Queryable.create("PaymentDetails",
                    FieldsAndDefinitions.PaymentDetails_Fields.values,
                    FieldsAndDefinitions.PaymentDetails_Fields.values.length);


            try (PreparedStatement statement = tableNames.get("Companies").
                    prepareStatement(companyQuery)) {
                statement.setString(1, json.getString("company_name"));
                statement.setString(2, json.getString("company_address"));
                statement.setString(3, json.getString("contact_name"));
                statement.setString(4, json.getString("contact_phone"));
                statement.setString(5, json.getString("contact_email"));
                statement.setInt(6, json.getInt("service_fee"));
                statement.execute();
            } catch (SQLException e) {
                e.printStackTrace();
                return;
//                throw new RuntimeException("Company CRUDable error");
            }

            try (PreparedStatement statement = tableNames.get("PaymentDetails").
                    prepareStatement(paymentQuery)) {
                statement.setString(1, json.getString("card_number"));
                statement.setString(2, json.getString("company_name"));
                statement.setString(3, json.getString("card_holder_name"));
                statement.setString(4, json.getString("ex_date"));
                statement.setString(5, json.getString("CVV"));
                statement.execute();
            } catch (SQLException e) {
                throw new RuntimeException("Payment CRUDable error");
            }
        }

        @Override
        public JsonObject read(JsonObject json) {
            String query = Queryable.read("Companies",
                    FieldsAndDefinitions.Companies_Fields.values[0]);

            try (PreparedStatement statement = tableNames.get("Companies").prepareStatement(query)) {
                statement.setInt(1, json.getInt("company_id"));

                return SqlCrudManager.this.convertResultSetToJson(statement.executeQuery());
            } catch (SQLException e) {
                System.out.println("Couldnt read");
                throw new RuntimeException(e);
            }

        }

        @Override
        public JsonObject update(JsonObject json) {
            return null;
        }

        @Override
        public void delete(JsonObject json) {

        }
    }

    private class ProductCRUDable implements CRUDable {

        @Override
        public void create(JsonObject json) {
            String productQuery = Queryable.create("Companies",
                    FieldsAndDefinitions.Companies_Fields.values,
                    FieldsAndDefinitions.Companies_Fields.values.length);

            try (PreparedStatement statement = tableNames.get("Companies").
                    prepareStatement(productQuery, Statement.RETURN_GENERATED_KEYS)) {
                statement.setInt(1, json.getInt("company_id"));
                statement.setString(2, json.getString("product_name"));
                statement.setString(3, json.getString("product_description"));
                statement.executeUpdate();
            } catch (SQLException e) {
                throw new RuntimeException("Bad syntax product");
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

        }
    }

    private JsonObject convertResultSetToJson(ResultSet resultSet) throws SQLException {
        JsonObjectBuilder mainJsonObjectBuilder = Json.createObjectBuilder();
        JsonArray jsonArray = Json.createArrayBuilder().build();

        try (ResultSet resultSetLocal = resultSet) {
            ResultSetMetaData resultSetMetaData = resultSetLocal.getMetaData();
            int columnCount = resultSetMetaData.getColumnCount();

            while (resultSetLocal.next()) {
                JsonObjectBuilder rowJsonObjectBuilder = Json.createObjectBuilder();

                for (int i = 1; i <= columnCount; i++) {
                    String columnName = resultSetMetaData.getColumnName(i);
                    Object value = resultSetLocal.getObject(i);

                    if (value instanceof String) {
                        rowJsonObjectBuilder.add(columnName, (String) value);
                    } else if (value instanceof Integer) {
                        rowJsonObjectBuilder.add(columnName, (Integer) value);
                    } else if (value instanceof Boolean) {
                        rowJsonObjectBuilder.add(columnName, (Boolean) value);
                    } else if (value != null) {
                        rowJsonObjectBuilder.add(columnName, value.toString());
                    }
                }

                jsonArray.add(rowJsonObjectBuilder.build());
            }
        }

        mainJsonObjectBuilder.add("data", jsonArray);
        return mainJsonObjectBuilder.build();
    }

    public void createDatabase(String url, String username, String password) {
        try {
            this.databaseConnection = DriverManager.getConnection(url, username, password);
            Statement stmt = this.databaseConnection.createStatement();
            String sql = Queryable.queryCreateDatabase(this.databaseName);
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            throw new RuntimeException("Create database fail" + this.databaseName);
        }
    }

    public void createTable(String tableName, String[] fields, String[] definitions, String primaryKey) {
        if (this.tableNames.containsKey(tableName)) {
            return;
        }

        this.useDatabase();
        try {
            Statement stmt = this.databaseConnection.createStatement();
            String sql = Queryable.queryCreateTable(tableName, fields, definitions, primaryKey);
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            throw new RuntimeException("Create table fail " + tableName);
        }
        this.tableNames.put(tableName, this.databaseConnection);
    }

    private void useTable(String tableName, Connection connection) {
        String query = Queryable.queryUseTable(tableName);

        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.execute();
        } catch (SQLException e) {
            throw new RuntimeException("Use table fail");
        }
    }

    private void useDatabase() {
        String query = Queryable.queryUseDatabase(this.databaseName);

        try (PreparedStatement statement = this.databaseConnection.prepareStatement(query)) {
            statement.execute();
        } catch (SQLException e) {
            throw new RuntimeException("Use database fail");
        }
    }

    public void start() {
        this.createDatabase("jdbc:mysql://localhost:3306/", "root", "password");

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
                        "BIGINT"}
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
