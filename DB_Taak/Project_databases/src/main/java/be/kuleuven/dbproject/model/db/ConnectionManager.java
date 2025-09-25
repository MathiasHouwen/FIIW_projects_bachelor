package be.kuleuven.dbproject.model.db;

import java.sql.*;

public class ConnectionManager {

    public static final String url = "jdbc:mysql://localhost/project_databases";
    public static final String user = "root";
    public static final String pwd = "";
    private final Connection connection;


    public Connection getConnection() {
        return connection;
    }

    public void flushConnection() {
        try {
            connection.commit();
            connection.close();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }

    public ConnectionManager() {
        try {
            connection = DriverManager.getConnection(url, user, pwd);
        } catch (Exception e) {
            throw new RuntimeException("Db connection handle failure");
        }
    }


}
