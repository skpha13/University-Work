package jdbc.config;


import java.sql.Connection;
import java.sql.SQLException;
import java.sql.Statement;

public class DataSetup {

    public void createTableAndStoredProcedure() throws SQLException {
        String createTableSql = "CREATE TABLE IF NOT EXISTS persons" +
                "(id int PRIMARY KEY AUTO_INCREMENT, name varchar(30)," +
                "age double)";

        String deleteProcedure = "DROP PROCEDURE IF EXISTS lab9.INSERT_PERSON;";

        String createStoredProcedure = "CREATE PROCEDURE IF NOT EXISTS INSERT_PERSON(OUT id int, IN name varchar(30), IN age double) " +
                "BEGIN " +
                "INSERT INTO persons(name,age) " +
                "VALUES (name,age); " +
                "SET id = LAST_INSERT_ID(); " +
                "END";

        Connection databaseConnection = DatabaseConfiguration.getConnection();
        Statement stmt = databaseConnection.createStatement();

        stmt.execute(createTableSql);
        stmt.execute(deleteProcedure);
        stmt.execute(createStoredProcedure);
    }
}
