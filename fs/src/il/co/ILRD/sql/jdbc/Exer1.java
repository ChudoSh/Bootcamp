package il.co.ILRD.sql.jdbc;

import java.io.IOException;
import java.sql.*;

public class Exer1 {
    public static void main(String[] args) throws SQLException, ClassNotFoundException, IOException {
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/inifinity", "root", "0000");
        ResultSet rs = con.createStatement().executeQuery("SELECT @@transaction_isolation AS isolation_level");

        while(rs.next()){
           try {
               String isolationLevel = rs.getString("isolation_level");
               System.out.println("The isolation level is " + isolationLevel);

           } catch (Exception e){
               e.printStackTrace();
           }
        }

//        System.out.println("the isolation level is " + con.getTransactionIsolation());
    }
}
