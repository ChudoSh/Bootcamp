package il.co.ILRD.sql.mockClasses;

import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class Tests {
    CompanyAdmin adminDB;
    CompanyCRUD newCompany;

    @BeforeEach
    void init(){
        this.adminDB = new CompanyAdmin("mockadmin");
        this.adminDB.setupDatabase("jdbc:mysql://localhost:3306/","root", "password");
    }

    @Test
    void createCompany(){
        newCompany = new CompanyCRUD("Tadiran", "Tel Aviv", "Bar","nice email", "some phone", 299, this.adminDB.getCompaniesCon());
//        CRUD.create(newCompany);
    }
}
