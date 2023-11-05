package il.co.ILRD.sql.database_manager;

import java.sql.*;
import java.util.HashMap;
import java.util.Map;

public class AdminDB implements CRUD {
    private Connection databaseConnection;
    private final String databaseName;
    private Map<String, Connection> tableNames;
    private String username;
    private String password;

    public AdminDB(String databaseName) {
        this.databaseName = databaseName;
        this.tableNames = new HashMap<>();
    }

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

    public void createDatabase(String url, String username, String password) {
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
            e.printStackTrace();
            throw new RuntimeException(e);
        }
        this.tableNames.put(tableName, this.databaseConnection);
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

    @Override
    public Connection getDatabaseConnection() {
        return this.databaseConnection;
    }
}
