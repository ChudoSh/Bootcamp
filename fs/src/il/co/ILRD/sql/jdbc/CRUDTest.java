package il.co.ILRD.sql.jdbc;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

import java.sql.SQLException;

public class CRUDTest {
    private static DataObjectCRUD crud;
    private static String tableName = "infinity";

    @BeforeEach
    void init() {
        crud = new DataObjectCRUD("jdbc:mysql://localhost:3306/inifinity", "root", "0000");
    }

    @Test
    void create() {
        crud.create(new Student("Daniel", (short) 28, "FS143-44", (short) 4), tableName);
    }

    @Test
    void read() {
        try {
            Student student = crud.read(tableName, "Daniel");
            System.out.println(student.toString());
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Test
    void update() {
        try {
            Student student = crud.read(tableName, "Daniel");
            student.setAge((short) 42);
            crud.update(tableName, student);

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Test
    void delete() {
        try {
            Student student = crud.read(tableName, "Daniel");
            crud.delete(tableName, student);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @AfterEach
    void close() {
        crud.close();
    }

}
