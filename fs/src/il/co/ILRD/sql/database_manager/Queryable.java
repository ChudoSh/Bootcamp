package il.co.ILRD.sql.database_manager;

import javax.json.JsonObject;
import java.util.Arrays;

abstract public class Queryable {
    private static final String queryCreate = "INSERT INTO %s (%s) VALUES (%s)";
    private static final String queryRead = "SELECT * FROM %s WHERE %s = ?";
    private static final String queryUpdate = "UPDATE %s SET %s WHERE %s = ?";
    private static final String queryDelete = "DELETE FROM %s WHERE %s = ?";
    private static final String queryCreateTable = "CREATE TABLE IF NOT EXISTS %s %s, PRIMARY KEY (%s))";
    private static final String queryCreateDatabase = "CREATE DATABASE IF NOT EXISTS %s";


    public static String create(String tableName, String[] attributes, int values) {
        if (0 >= values || null == attributes | null == tableName) {
            return null;
        }

        return String.format(queryCreate, tableName, toCreateStringFields(attributes), generateValueString(values));
    }

    public static String create(String tableName, String[] attributes, JsonObject data) {
        if (null == data || null == attributes | null == tableName) {
            return null;
        }

        return String.format(queryCreate, tableName, toCreateStringFields(attributes), parseJson(data, attributes));
    }

    public static String read(String tableName, String primaryKey) {
        return String.format(queryRead, tableName, primaryKey);
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

    public static String queryCreateTable(String tableName, String[] fields, String[] definitions, String primaryKey) {
        if (null == tableName) {
            return null;
        }

        return String.format(queryCreateTable, tableName, appendDefinitions(fields, definitions), primaryKey);
    }

    public static String queryCreateDatabase(String databaseNAme) {
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
        StringBuilder str = new StringBuilder("(");

        for (int i = 0; i < numOfValues - 1; ++i) {
            str.append("?, ");
        }

        return str.append("?)").toString();

    }

    private static String generateListedString(String[] attributes) {
        StringBuilder sb = new StringBuilder();

        for (String attribute : attributes) {
            sb.append(attribute).append(", ");
        }

        return sb.toString();
    }

    private static String toCreateStringFields(String[] attributes) {
        StringBuilder attributeList = new StringBuilder();
        for (int i = 0; i < attributes.length - 1; ++i) {
            attributeList.append(attributes[i]).append(", ");
        }

        return attributeList.append(attributes[attributes.length - 1]).toString();
    }

    private static String toUpdateStringFields(String[] attributes) {
        StringBuilder attributeList = new StringBuilder();

        for (int i = 0; i < attributes.length - 1; ++i) {
            attributeList.append(attributes[i]).append(" = ?, ");
        }

        return attributeList.append(attributes[attributes.length - 1]).append(" = ?").toString();
    }

    private static String appendDefinitions(String[] fields, String[] defintions) {
        StringBuilder attributeList = new StringBuilder("(");
        for (int i = 0; i < fields.length - 1; ++i) {
            attributeList.append(fields[i]).append(" ").append(defintions[i]).append(", ");
        }

        attributeList.append(fields[fields.length - 1]).append(" ").append(defintions[fields.length - 1]);
        return attributeList.toString();
    }

    public static String parseJson(JsonObject data, String[] keys) {
        String[] values = new String[keys.length];
        for (int i = 0; i < keys.length; ++i) {
            values[i] = String.format("'%s'",data.getString(keys[i]));
        }

        String value = Arrays.toString(values);
        value = value.replace("[", "");
        value = value.replace("]", "");
        return value;
    }
}
