package databases;

import java.sql.*;
import java.util.HashMap;
import java.util.Map;

public class AdminDB implements main.java.databases.CRUD {
    private Connection databaseConnection;
    private final String databaseName;
    private Map<String, String[]> tables;
    private String username;
    private String password;

    public AdminDB(String databaseName) {
        this.databaseName = databaseName;
        this.tables = new HashMap<>();
    }

//    public void create(JsonObject json) {
//        JsonObject companyBody = json.getJsonObject("Company");
//        JsonObject paymentBody= json.getJsonObject("PaymentDetails");
//
//        int companyID = this.createCompanyRecord(
//                companyBody.getString("company_name"),
//                companyBody.getString("company_address"),
//                companyBody.getString("contact_name"),
//                companyBody.getString("contact_phone"),
//                companyBody.getString("contact_email"),
//                companyBody.getInt("service_fee"));
//
//        this.createPaymentDetailsRecord(paymentBody.getInt("bill_outstanding"),
//                companyID,
//                paymentBody.getString("IBAN"),
//                paymentBody.getString("SWIFT"),
//                paymentBody.getString("bank_account"),
//                paymentBody.getString("bank_address"),
//                paymentBody.getString("bank_branch"));
//    }
//
//    private int createCompanyRecord(String companyName, String companyAddress, String  contactName, String contactPhone, String contactEmail, int serviceFee) {
//        int FAIL = -1; //make this an exception
//        String query = Queryable.create("Companies", this.tables.get("Companies"), this.tables.get("Companies").length - 1);
//        try (PreparedStatement statement = this.databaseConnection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS)) {
//            statement.setString(1, companyName);
//            statement.setString(2, companyAddress);
//            statement.setString(3, contactName);
//            statement.setString(4, contactPhone);
//            statement.setString(5, contactEmail);
//            statement.setInt(6, serviceFee);
//            statement.executeUpdate();
//
//            ResultSet generatedKeys = statement.getGeneratedKeys();
//            if (generatedKeys.next()) {
//                return generatedKeys.getInt(1);
//            }
//
//        } catch (SQLException e) {
//            throw new RuntimeException(e);
//        }
//
//        return FAIL;
//    }
//
//    private void createPaymentDetailsRecord(int billOutstanding, int companyID, String iban, String swift, String bank_address, String bank_account, String bank_branch) {
//        String query = Queryable.create("PaymentDetails",this.tables.get("PaymentDetails") , fields.length - 1);
//        try (PreparedStatement statement = this.databaseConnection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS)) {
//            statement.setInt(1, billOutstanding);
//            statement.setInt(2, companyID);
//            statement.setString(3, iban);
//            statement.setString(4, swift);
//            statement.setString(5, bank_account);
//            statement.setString(6, bank_address);
//            statement.setString(7, bank_branch);
//            statement.executeUpdate();
//        } catch (SQLException e) {
//            throw new RuntimeException(e);
//        }
//    }
//
//    private void createProductRecord(int companyID) {
//        String[] fields = this.tables.get("Products");
//        String query = Queryable.create("Products", fields, fields.length - 1);
//        try (PreparedStatement statement = this.databaseConnection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS)) {
//            statement.setInt(2, companyID);
//            statement.setString(3, fields[1]);
//            statement.setString(4, fields[2]);
//            statement.executeUpdate();
//        } catch (SQLException e) {
//            throw new RuntimeException(e);
//        }
//   }

    @Override
    public void create(Recordable toCreate) {
        if (null == toCreate) {
            return;
        }

        toCreate.createRecord();
        System.out.println("Record created.");
    }


    @Override
    public Recordable read(Recordable toRead) {
        if (null == toRead) {
            return null;
        }

        return toRead.readRecord();
    }

    @Override
    public void update(Recordable toUpdate) {
        if (null == toUpdate) {
            System.out.println("Not the right record.");
            return;
        }

        if (null == this.read(toUpdate)) {
            System.out.println("No record exist in the table");
            return;
        }

        toUpdate.updateRecord();
    }

    @Override
    public void delete(Recordable toDelete) {
        if (null == toDelete) {
            return;
        }

        toDelete.deleteRecord();
    }

    public void initiateDatabaseAndTables() {
        String[] companyTableDefinitions =
                {"BIGINT NOT NULL AUTO_INCREMENT",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "BIGINT"};
        String[] companyTableFields =
                {"company_id",
                        "company_name",
                        "company_address",
                        "contact_name",
                        "contact_phone",
                        "contact_email",
                        "service_fee"};
        String[] productTableDefinitions =
                {"BIGINT NOT NULL AUTO_INCREMENT",
                        "BIGINT",
                        "VARCHAR(255)",
                        "VARCHAR(255)"};
        String[] productTableFields =
                {"product_id",
                        "company_id",
                        "product_name",
                        "product_description"};
        String[] paymentTableDefinitions =
                {"BIGINT NOT NULL AUTO_INCREMENT",
                        "BIGINT",
                        "BIGINT",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "VARCHAR(255)"};
        String[] paymentTableFields =
                {"pd_id",
                        "bill_outstanding",
                        "company_id",
                        "IBAN",
                        "SWIFT",
                        "bank_address",
                        "bank_account",
                        "bank_branch"};
        this.createDatabase("jdbc:mysql://localhost:3306/", "root", "password");
        this.createTable("Companies", companyTableFields, companyTableDefinitions, "company_id");
        this.createTable("Products", productTableFields, productTableDefinitions, "product_id");
        this.createTable("PaymentDetails", paymentTableFields, paymentTableDefinitions, "pd_id");
    }

    private void createDatabase(String url, String username, String password) {
        try {
            this.username = username;
            this.password = password;
            this.databaseConnection = DriverManager.getConnection(url, username, password);
            Statement stmt = this.databaseConnection.createStatement();
            String sql = Queryable.queryCreateDatabase(databaseName);
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            e.printStackTrace();
            throw new RuntimeException(e);
        }
    }

    private void createTable(String tableName, String[] fields, String[]
            definitions, String primaryKey) {
        if (this.tables.containsKey(tableName)) {
            return;
        }

        this.useDatabase();
        try {
            Statement stmt = this.databaseConnection.createStatement();
            String sql = Queryable.queryCreateTable(tableName, fields, definitions, primaryKey);
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            e.printStackTrace();
            throw new RuntimeException(e);
        }
        this.tables.put(tableName, fields);
    }

    private void useTable(String tableName, Connection connection) {
        String query = Queryable.queryUseTable(tableName);

        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.execute();
        } catch (SQLException e) {
            e.printStackTrace();
            throw new RuntimeException(e);
        }
    }

    private void useDatabase() {
        String query = Queryable.queryUseDatabase(this.databaseName);

        try (PreparedStatement statement = this.databaseConnection.prepareStatement(query)) {
            statement.execute();
        } catch (SQLException e) {
            System.out.println(query);
            e.printStackTrace();
            throw new RuntimeException(e);
        }
    }


    public Connection getDatabaseConnection() {
        return this.databaseConnection;
    }
}
