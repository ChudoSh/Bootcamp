package il.co.ILRD.sql.jdbc;

import java.sql.*;
import java.util.Arrays;

public class DataObjectCRUD {
    private final Connection con;
    private final String create = "INSERT INTO %s (Name, Age, Class, Year) VALUES (?, ?, ?, ?)";
    private final String read = "SELECT * FROM %s WHERE Name = ?";
    private final String update = "UPDATE %s SET Age = ?, Class = ?, Year = ? WHERE Name = ?";
    private final String delete = "DELETE FROM %s WHERE Name = ?";

    public DataObjectCRUD(String url, String user, String password) {
        try {
            this.con = DriverManager.getConnection(url, user, password);
        } catch (SQLException e) {
            throw new RuntimeException(e.getSQLState());
        }
    }

    public void create(Student newStudent, String tableName) {
        String sql = String.format(this.create, tableName);

        try (PreparedStatement statement = this.con.prepareStatement(sql)) {
            statement.setString(1, newStudent.getName());
            statement.setShort(2, newStudent.getAge());
            statement.setString(3, newStudent.getClazz());
            statement.setShort(4, newStudent.getYear());
            statement.executeUpdate();

            System.out.println("Record created.");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public Student read(String tableName, String byName) throws SQLException {
        String sql = String.format(this.read, tableName);

        try (PreparedStatement statement = con.prepareStatement(sql)) {
            statement.setString(1, byName);
            ResultSet result = statement.executeQuery();

            if (result.next()) {
                Student toReturn = new Student(result.getString("Name"), result.getShort("Age"), result.getString("Class"), result.getShort("Year"));
                result.close();

                System.out.println("Record read.");
                return toReturn;
            }

            return null;

        } catch (SQLException e) {
            throw new SQLException(e);
        }
    }

    public void update(String tableName, Student student) throws SQLException {
        String sql = String.format(this.update, tableName);

        try (PreparedStatement statement = con.prepareStatement(sql)) {
            statement.setShort(1, student.getAge());
            statement.setString(2, student.getClazz());
            statement.setShort(3, student.getYear());
            statement.setString(4, student.getName());

            statement.executeUpdate();
            System.out.println("Record updated.");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void delete(String tableName, Student student) throws SQLException {
        String sql = String.format(this.delete, tableName);

        try (PreparedStatement statement = con.prepareStatement(sql)) {
            statement.setString(1, student.getName());
            statement.executeUpdate();
            System.out.println("Record deleted.");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void close() {
        try {
            this.con.close();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    private static String replaceSqrBrackets(String[] toReplace) {
        String temp = Arrays.toString(toReplace).replace("[", "");
        return temp.replace("]", "");
    }
}
