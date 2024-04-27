package jdbc.config;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;

public class DatabaseConfiguration {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/lab9";
    private static final String USER = "userpao";
    private static final String PASSWORD = "Password1.";

    private static Connection databaseConnection;

    private DatabaseConfiguration() {
    }

    public static Connection getConnection() {
        try {
            if (databaseConnection == null || databaseConnection.isClosed()) {
                databaseConnection = DriverManager.getConnection(DB_URL, USER, PASSWORD);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return databaseConnection;
    }
}
