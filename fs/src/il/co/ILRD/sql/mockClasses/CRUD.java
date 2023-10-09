package il.co.ILRD.sql.mockClasses;

import java.sql.*;

public interface CRUD {
    static void create(CRUD toCreate) {
        CRUD.useDatabase(toCreate.getDatabaseName(), toCreate.getConnection());
        CRUD.useTable(toCreate.getTableName(), toCreate.getConnection());

        String query = Queryable.create(toCreate.getTableName(),
                toCreate.getFields(),
                toCreate.getNumOfFields());

        try (PreparedStatement statement = toCreate.getCreateStatement(query)) {
            statement.executeUpdate();
            System.out.println("Record created.");
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

    }

    static CRUD read(CRUD toRead) {
        CRUD.useTable(toRead.getTableName(), toRead.getConnection());
        String query = Queryable.read(toRead.getTableName(), toRead.getPrimaryKey());

        try (PreparedStatement statement = toRead.getReadStatement(query)) {
            statement.executeUpdate();
            ResultSet result = statement.executeQuery();

            if (result.next()) {
                CRUD toReturn = toRead.getCruddableFromResultSet(result);
                System.out.println("Record read.");

                return toReturn;
            }

            return null;
        } catch (
                SQLException e) {
            throw new RuntimeException(e);
        }
    }

    static void update(CRUD toUpdate) {
        CRUD.useTable(toUpdate.getTableName(), toUpdate.getConnection());
        CRUD read = CRUD.read(toUpdate);
        if (null == read) {
            System.out.println("Record not found.");
            return;
        }
        String query = Queryable.update(toUpdate.getTableName(), toUpdate.getFields(), toUpdate.getPrimaryKey());

        try {
            try (PreparedStatement statement = read.getUpdateStatement(query, toUpdate)) {
                statement.executeUpdate();
                System.out.println("Record updated.");
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }

    }

    static void delete(CRUD toDelete) {
        String query = Queryable.delete(toDelete.getTableName(), toDelete.getPrimaryKey());

        try (PreparedStatement statement = toDelete.getDeleteStatement(query)) {
            statement.executeUpdate();
            System.out.println("Record deleted.");
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    static void createDatabase(Connection connection, String databaseName, String url, String username, String password) {
        try {
            Statement stmt = connection.createStatement();
            String sql = Queryable.createDatabase(databaseName);
            stmt.executeUpdate(sql);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    static void createTable(Connection connection, String databaseName, String tableName, String[] fields, String[] definitions, String primaryKey) {
        try {
            CRUD.useDatabase(databaseName, connection);
            Statement stmt = connection.createStatement();
            String query = Queryable.createTable(tableName, fields, definitions, primaryKey);
            System.out.println(query);

            stmt.executeUpdate(query);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    private static void useTable(String tableName, Connection connection) {
        String query = Queryable.queryUseTable(tableName);

        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.execute();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    private static void useDatabase(String databaseName, Connection connection) {
        String query = Queryable.queryUseDatabase(databaseName);

        try (PreparedStatement statement = connection.prepareStatement(query)) {
            statement.execute();
        } catch (SQLException e) {
            System.out.println(query);
            throw new RuntimeException(e);
        }
    }

    CRUD getCruddableFromResultSet(ResultSet result) throws SQLException;

    String getTableName();

    String getDatabaseName();

    String getPrimaryKey();

    PreparedStatement getCreateStatement(String query);

    PreparedStatement getReadStatement(String query);

    PreparedStatement getUpdateStatement(String query, CRUD toUpdate);

    PreparedStatement getDeleteStatement(String query);

    String[] getFields();

    Connection getConnection();

    int getNumOfFields();

}
