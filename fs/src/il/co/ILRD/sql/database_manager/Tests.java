package il.co.ILRD.sql.database_manager;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import java.sql.SQLException;

public class Tests {
    AdminDB adminDB;

    @BeforeEach
    void init() throws SQLException {
        this.adminDB = new AdminDB("mockadmin");
        this.adminDB.createDatabase("jdbc:mysql://localhost:3306/", "root", "password");
        String[] definitions =
                {"BIGINT NOT NULL AUTO_INCREMENT",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "BIGINT"};
        String[] tableFields =
                {"company_id",
                        "company_name",
                        "company_address",
                        "contact_name",
                        "contact_phone",
                        "contact_email",
                        "service_fee"};

        this.adminDB.createTable("Companies", tableFields, definitions, "company_id");
    }


    @Test
    void createCompany() {
        CompanyRecord newCompany = new CompanyRecord("Bezeq", "tel aviv", "bar", "something", "something", 49, this.adminDB.getDatabaseConnection());
        this.adminDB.create(newCompany);
    }

    @Test
    void readCompany() {
        CompanyRecord newCompany = new CompanyRecord("Tadiran", "tel aviv", "bar", "something", "something", 49, this.adminDB.getDatabaseConnection());
        this.adminDB.create(newCompany);
        CompanyRecord toRead = (CompanyRecord) this.adminDB.read(newCompany);
        System.out.println(toRead.toString());
    }

    @Test
    void updateCompany() {
        CompanyRecord newCompany = new CompanyRecord("Electra", "tel aviv", "bar", "something", "something", 49, this.adminDB.getDatabaseConnection());
        this.adminDB.create(newCompany);
        newCompany.setCompanyName("SomeUpdate");
        newCompany.setContactName("Malena");
        newCompany.setCompanyAddress("Netanya");
        this.adminDB.update(newCompany);
        System.out.println(newCompany);
    }

    @Test
    void deleteCompany() throws SQLException {
        CompanyRecord newCompany = new CompanyRecord("ToDelete", "tel aviv", "bar", "something", "something", 49, this.adminDB.getDatabaseConnection());
        this.adminDB.create(newCompany);
        this.adminDB.delete(newCompany);
    }
}
