
import javax.json.JsonObject;
import java.sql.*;
import java.util.Arrays;

public class AdminSQLManager {
    private Connection databaseConnection;
    private final String databaseName;
    private final CompanyCRUDable companyCrud;
    private ProductCRUDable productCrud;

    public AdminSQLManager(String databaseName) {
        this.databaseName = databaseName;
        this.companyCrud = new CompanyCRUDable();
        this.start();
    }

    public void registerCompany(JsonObject json){
        this.companyCrud.create(json);
    }

    public void registerProduct(JsonObject json) {
        this.productCrud.create(json);
    }
    
    private void start() {
        this.createDatabase();
        this.useDatabase();

        this.createTable("Companies",
                FieldsAndDefinitions.Companies_Fields.values,
                FieldsAndDefinitions.Companies_Definitions.values,
                FieldsAndDefinitions.Companies_Fields.values[0]);

        this.createTable("Products",
                FieldsAndDefinitions.Products_Fields.values,
                FieldsAndDefinitions.Products_Definitions.values,
                FieldsAndDefinitions.Products_Fields.values[0]);

        this.createTable("PaymentDetails",
                FieldsAndDefinitions.PaymentDetails_Fields.values,
                FieldsAndDefinitions.PaymentDetails_Definitions.values,
                FieldsAndDefinitions.PaymentDetails_Fields.values[0]);
    }

    /*===============================CompanyCrud==================================*/
    private class CompanyCRUDable implements Cruddable {
        @Override
        public void create(JsonObject json) {
        	 String query = "INSERT INTO %s (%s) VALUES (%s)";
             String jsonCompanyString = AdminSQLManager.this.parseJson(json, 
            		 FieldsAndDefinitions.Companies_Fields.values);
             String jsonPaymentString = AdminSQLManager.this.parseJson(json, 
            		 FieldsAndDefinitions.PaymentDetails_Fields.values);

             String companyQuery = String.format(query, "Companies",String.join(", ", 
            		 FieldsAndDefinitions.Companies_Fields.values), jsonCompanyString);
             String paymentQuery = String.format(query, "PaymentDetails",String.join(", ", 
            		 FieldsAndDefinitions.PaymentDetails_Fields.values), jsonPaymentString);

             try (Statement statement = 
            		 AdminSQLManager.this.databaseConnection.createStatement()) {
                 statement.execute(companyQuery);
                 statement.execute(paymentQuery);
             } catch (SQLException e) {
                 throw new RuntimeException("Companies CRUDable error", e);
             }
        }

        @Override
        public JsonObject read(JsonObject json) {
            return null;
        }

        @Override
        public JsonObject update(JsonObject json) {
            return null;
        }

        @Override
        public void delete(JsonObject json) {

        }
    }

    /*===============================ProductCrud==============================*/
    private class ProductCRUDable implements Cruddable {
        @Override
        public void create(JsonObject json) {
        	String query = "INSERT INTO Products (%s) VALUES (%s)";
        	String jsonProductsString = AdminSQLManager.this.parseJson(json, 
        			FieldsAndDefinitions.Products_Fields.values);
        	
            String companyQuery = String.format(query,
                    String.join(", ", FieldsAndDefinitions.Products_Fields.values),
                    jsonProductsString);
        
            try (Statement statement = 
            		AdminSQLManager.this.databaseConnection.createStatement()) {
                statement.execute(companyQuery);
            } catch (SQLException e) {
                throw new RuntimeException("Products CRUDable error");
            }
        }

        @Override
        public JsonObject read(JsonObject json) {
            return null;
        }

        @Override
        public JsonObject update(JsonObject json) {
            return null;
        }

        @Override
        public void delete(JsonObject json) {

        }
    }
    /*==========================Private methods and classes=======================*/

    private void createDatabase() {
    	   // SQL query to create the database if it doesn't exist
    	
        String query = String.format("CREATE DATABASE IF NOT EXISTS %s", this.databaseName);

        try {
            // Establish a connection to the database server
        	Class.forName("com.mysql.cj.jdbc.Driver");
            this.databaseConnection = DriverManager.getConnection("jdbc:mysql://localhost:3306/", "root", "password");
        } catch (SQLException e) {
            // Handle any errors that occur during database connection
        	e.printStackTrace();
            throw new RuntimeException("Connection failed", e);
        } catch (ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

        // Try to execute the SQL query to create the database
        try (Statement stmt = this.databaseConnection.createStatement()) {
            stmt.execute(query);
        } catch (SQLException e) {
            // Handle any errors that occur during the execution of the SQL query
            throw new RuntimeException("Create database fail " + this.databaseName, e);
        }
    }

    private void createTable(String tableName, String[] fields, 
    								  String[] definitions, String primaryKey) {
    	String query = "CREATE TABLE IF NOT EXISTS %s (%s, PRIMARY KEY (%s))";;
    	StringBuilder stringBuilder = new StringBuilder();
    	
        for (int i = 0; i < fields.length - 1; ++i) {
        	stringBuilder.append(fields[i]).append(" ").append(definitions[i]).append(", ");
        }
        
        
        stringBuilder.append(fields[fields.length - 1]).append(" ").append(definitions[fields.length - 1]);
        String fieldsAndDefinitions = stringBuilder.toString();
 
   
    	try (Statement stmt = this.databaseConnection.createStatement()){
            String sql = String.format(query, tableName, fieldsAndDefinitions, primaryKey);
            stmt.execute(sql);
        } catch (SQLException e) {
            throw new RuntimeException("Create table fail " + tableName);
        }
    }

    private void useDatabase() {	
        try (Statement statement = this.databaseConnection.createStatement()) {
            statement.execute(String.format("USE %s",this.databaseName));
        } catch (SQLException e) {
            throw new RuntimeException("Use database fail");
        }
    }
    
    private String parseJson(JsonObject data, String[] keys) {
    	System.out.println(data.toString());
        String[] values = new String[keys.length];
        for (int i = 0; i < keys.length; ++i) {
            values[i] = String.format("'%s'",data.getString(keys[i]));
        }

        String value = Arrays.toString(values);
        value = value.replace("[", "");
        value = value.replace("]", "");
        System.out.println(value);
        return value;
    }
    
    

    /*==========================Enum for tables===============================*/
    private enum FieldsAndDefinitions {
        Companies_Fields(
                new String[]{"company_name",
                        "company_address",
                        "contact_name",
                        "contact_phone",
                        "contact_email",
                        "service_fee"}

        ),
        Companies_Definitions(
                new String[]{"VARCHAR(255) UNIQUE",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "VARCHAR(255)"}
        ),
        Products_Fields(
                new String[]
                        {"product_id",
                                "company_name",
                                "product_name",
                                "product_description"}
        ),
        Products_Definitions(
                new String[]
                        {"VARCHAR(255) UNIQUE",
                                "VARCHAR(255) UNIQUE",
                                "VARCHAR(255)",
                                "VARCHAR(255)"}
        ),
        PaymentDetails_Fields(
                new String[]
                        {"card_number",
                                "company_name",
                                "card_holder_name",
                                "ex_date",
                                "CVV"}

        ),
        PaymentDetails_Definitions(
                new String[]{"VARCHAR(255) UNIQUE",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "VARCHAR(255)",
                        "VARCHAR(255)"}
        );

        private final String[] values;

        FieldsAndDefinitions(String[] values) {
            this.values = values;
        }
    }
    
    
}

