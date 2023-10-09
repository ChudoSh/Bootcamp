package il.co.ILRD.sql.mockClasses;

import java.util.Objects;

abstract public class Queryable {
    private static final String queryCreate = "INSERT INTO %s %s VALUES %s";
    private static final String queryRead = "SELECT %s FROM %s WHERE %s";
    private static final String queryUpdate = "UPDATE %s SET %s WHERE %s";
    private static final String queryDelete = "DELETE FROM %s WHERE %s";
    private static final String queryCreateTable = "CREATE TABLE IF NOT EXISTS %s %s, PRIMARY KEY (%s))";
    private static final String queryCreateDatabase = "CREATE DATABASE IF NOT EXISTS %s";


    public static String create(String tableName, String[] attributes, int values) {
        if (0 >= values || null == attributes | null == tableName) {
            return null;
        }

        return String.format(queryCreate, tableName, toCreateStringFields(attributes), generateValueString(values));
    }

    public static String read(String tableName, String[] attributes, String[] conditions) {
        if (null == tableName || null == conditions) {
            return null;
        }

        return String.format(queryRead,
                Objects.requireNonNullElse(
                        generateListedString(attributes), "*"),
                tableName,
                generateListedString(conditions));
    }

    public static String read(String tableName, String[] conditions) {
        return read(tableName, null, conditions);
    }

    public static String read(String tableName, String primaryKey) {
        return read(tableName, null, new String[]{primaryKey});
    }

    public static String update(String tableName, String[] fields, String primaryKey) {
        if (null == tableName || null == fields || null == primaryKey) {
            return null;
        }

        return String.format(queryUpdate, tableName, toUpdateStringFields(fields), primaryKey);
    }

    public static String delete(String tableName, String conditions) {
        if (null == tableName || null == conditions) {
            return null;
        }

        return String.format(queryDelete, tableName, conditions);
    }

    public static String createTable(String tableName, String[] fields, String[] defintions, String primaryKey) {
        if (null == tableName) {
            return null;
        }

        return String.format(queryCreateTable, tableName,appendDefinitions(fields, defintions), primaryKey);
    }

    public static String createDatabase(String databaseNAme) {
        if (null == databaseNAme) {
            return null;
        }

        return String.format(queryCreateDatabase, databaseNAme);
    }

    public static String queryUseTable(String tableName) {
        return "USE " + tableName + " ";
    }

    public static String queryUseDatabase(String databaseName) {
        return "USE  " + databaseName + " ";
    }

    private static String generateValueString(int numOfValues) {
        return "(" + "?, ".repeat(numOfValues) + ")";
    }

    private static String generateListedString(String[] attributes) {
        StringBuilder sb = new StringBuilder();

        for (String attribute : attributes) {
            sb.append(attribute).append(", ");
        }

        return sb.toString();
    }

    private static String toCreateStringFields(String[] attributes) {
        StringBuilder attributeList = new StringBuilder("(");
        for (int i = 0; i < attributes.length - 1; ++i) {
            attributeList.append(attributes[i]).append(", ");
        }
        return attributeList.append(attributes[attributes.length]).append(")").toString();
    }

    private static String toUpdateStringFields(String[] attributes) {
        StringBuilder attributeList = new StringBuilder();
        for (int i = 0; i < attributes.length - 1; ++i) {
            attributeList.append(attributes[i]).append("= ?, ");
        }
        return attributeList.append(attributes[attributes.length]).append("= ?").toString();
    }

    private static String appendDefinitions(String[] fields, String[] defintions) {
        StringBuilder attributeList = new StringBuilder("(");
        for (int i = 0; i < fields.length - 1; ++i) {
            attributeList.append(fields[i]).append(" ").append(defintions[i]).append(", ");
        }

        attributeList.append(fields[fields.length - 1]).append(" ").append(defintions[fields.length - 1]);
        return attributeList.toString();
    }
}
