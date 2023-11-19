package il.co.ILRD.sql.database_manager;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.PreparedStatement;
import java.sql.Statement;

public class CompanyRecord implements Recordable {
    private int companyID;
    private String companyName;
    private String companyAddress;
    private String contactName;
    private String contactEmail;
    private String contactPhone;
    private int serviceFee;
    private static final int numOfFieldsInTable = 6;
    private static final String tableName = "Companies";
    private Connection tableConnection;
    private static final String[] tableFields =
            {"company_name",
                    "company_address",
                    "contact_name",
                    "contact_phone",
                    "contact_email",
                    "service_fee"};

    public CompanyRecord(String companyName, String companyAddress, String contactName, String contactEmail, String contactPhone, int serviceFee, Connection connection) {
        this.companyName = companyName;
        this.companyAddress = companyAddress;
        this.contactName = contactName;
        this.contactEmail = contactEmail;
        this.contactPhone = contactPhone;
        this.serviceFee = serviceFee;
        this.tableConnection = connection;
    }

    public static CompanyRecord of(String data, Connection tableConnection) {
        String[] values = data.split("\\.", data.length());
        return new CompanyRecord(values[0],
                values[1],
                values[2],
                values[3],
                values[4],
                Integer.parseInt(values[5]), tableConnection);
    }

    @Override
    public Recordable getRecordFromResultSet(ResultSet result) throws SQLException {
        CompanyRecord toReturn = new CompanyRecord(
                result.getString(tableFields[0]),
                result.getString(tableFields[1]),
                result.getString(tableFields[2]),
                result.getString(tableFields[3]),
                result.getString(tableFields[4]),
                result.getInt(tableFields[5]), tableConnection);
        toReturn.setCompanyID(this.companyID);

        return toReturn;
    }


    public String[] getFields() {
        return tableFields;
    }

    @Override
    public void createRecord() {
        String query = Queryable.create(tableName, tableFields, numOfFieldsInTable);
        try (PreparedStatement statement = tableConnection.prepareStatement(query, Statement.RETURN_GENERATED_KEYS)) {
            statement.setString(1, this.companyName);
            statement.setString(2, this.companyAddress);
            statement.setString(3, this.contactName);
            statement.setString(4, this.contactPhone);
            statement.setString(5, this.contactEmail);
            statement.setInt(6, this.serviceFee);
            statement.executeUpdate();

            ResultSet generatedKeys = statement.getGeneratedKeys();
            if (generatedKeys.next()) {
                this.companyID = generatedKeys.getInt(1);
            }

        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    @Override
    public Recordable readRecord() {
        String query = Queryable.read(tableName, this.getPrimaryKeyName());

        try (PreparedStatement statement = tableConnection.prepareStatement(query)) {
            statement.setInt(1, this.companyID);
            ResultSet result = statement.executeQuery();

            if (result.next()) {
                Recordable toReturn = this.getRecordFromResultSet(result);
                System.out.println("Record read.");

                return toReturn;
            }

            return null;
        } catch (SQLException e) {
            e.printStackTrace();
            throw new RuntimeException(e);
        }
    }

    @Override
    public void updateRecord() {
        String query = Queryable.update(tableName, tableFields, this.getPrimaryKeyName());

        try (PreparedStatement statement = tableConnection.prepareStatement(query)) {
            statement.setString(1, this.companyName);
            statement.setString(2, this.companyAddress);
            statement.setString(3, this.contactName);
            statement.setString(4, this.contactPhone);
            statement.setString(5, this.contactEmail);
            statement.setInt(6, this.serviceFee);
            statement.setInt(7, this.companyID);
            statement.executeUpdate();
            System.out.println("Record updated.");
        } catch (SQLException e) {
            e.printStackTrace();
            throw new RuntimeException(e);
        }
    }

    @Override
    public void deleteRecord() {
        String query = Queryable.delete(tableName, String.valueOf(this.companyID));

        try (PreparedStatement statement = tableConnection.prepareStatement(query)) {
            statement.setInt(1, this.companyID);
            statement.executeUpdate();
            System.out.println("Record deleted.");
        } catch (SQLException e) {
            e.printStackTrace();
            throw new RuntimeException(e);
        }
    }

    @Override
    public String getPrimaryKeyName() {
        return "company_id";
    }

    /*------------------------Getters and Setters---------------------------------*/
    public int getCompanyID() {
        return this.companyID;
    }

    public void setCompanyID(int companyID) {
        this.companyID = companyID;
    }


    public String getCompanyName() {
        return this.companyName;
    }

    public void setCompanyName(String companyName) {
        this.companyName = companyName;
    }

    public String getCompanyAddress() {
        return this.companyAddress;
    }

    public void setCompanyAddress(String companyAddres) {
        this.companyAddress = companyAddres;
    }

    public String getContactName() {
        return this.contactName;
    }

    public void setContactName(String contactName) {
        this.contactName = contactName;
    }

    public String getContactEmail() {
        return this.contactEmail;
    }

    public void setContactEmail(String contactEmail) {
        this.contactEmail = contactEmail;
    }

    public String getContactPhone() {
        return this.contactPhone;
    }

    public void setContactPhone(String contactPhone) {
        this.contactPhone = contactPhone;
    }

    public int getServiceFee() {
        return this.serviceFee;
    }

    public void setServiceFee(int serviceFee) {
        this.serviceFee = serviceFee;
    }

    @Override
    public String toString() {
        return "CompanyRecord{" +
                "companyID = " + this.companyID +
                ", companyName ='" + this.companyName + '\'' +
                ", companyAddress = '" + this.companyAddress + '\'' +
                ", contactName = '" + this.contactName + '\'' +
                ", contactEmail = '" + this.contactEmail + '\'' +
                ", contactPhone = '" + this.contactPhone + '\'' +
                ", serviceFee = " + this.serviceFee +
                '}';
    }
}
