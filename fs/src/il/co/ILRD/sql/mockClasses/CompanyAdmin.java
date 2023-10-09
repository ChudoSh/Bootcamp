package il.co.ILRD.sql.mockClasses;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class CompanyAdmin {
    private Connection connectionCompanies;
    private boolean isCompaniesDatabaseUp = false;
    private final String databaseName;
//    Connection products;
//    Connection bankDetails;


    public CompanyAdmin(String databaseName ) {
        this.databaseName = databaseName;
    }

    public Connection getCompaniesCon() {
        return this.connectionCompanies;
    }

    public void setupDatabase(String url, String username, String password) {
        if (!isCompaniesDatabaseUp) {
            try {
                this.connectionCompanies = DriverManager.getConnection(url, username, password);
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
            CRUD.createDatabase(this.connectionCompanies, databaseName, url, username, password);
            isCompaniesDatabaseUp = true;
        }
    }
}
