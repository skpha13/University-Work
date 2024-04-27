package jdbc.repository;


import jdbc.config.DatabaseConfiguration;
import jdbc.model.Person;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class PersonRepository {

    // CallableStatement (for this example to work - store procedure needs to be created into the database)
    public void insertPerson(Person person) {
        String preparedSql = "{call INSERT_PERSON(?,?,?)}";

        try (CallableStatement cstmt = DatabaseConfiguration.getConnection().prepareCall(preparedSql)) { //try-with-resources
            cstmt.setString(2, person.getName());
            cstmt.setDouble(3, person.getAge());

            cstmt.registerOutParameter(1, Types.INTEGER); //out param (result of the procedure call)

            cstmt.execute();
            System.out.println("Added user with id:" + cstmt.getInt(1));    //out param (result of the procedure call)
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    // PreparedStatement - use when we have parameters
    public Person getPersonById(int id) {
        String selectSql = "SELECT * FROM persons WHERE id=?";

        try (PreparedStatement preparedStatement = DatabaseConfiguration.getConnection().prepareStatement(selectSql)) { //try-with-resources
            preparedStatement.setInt(1, id);
            try (ResultSet resultSet = preparedStatement.executeQuery()) { //try-with-resources
                if (resultSet.next()) {
                    return mapResultSetToPerson(resultSet);
                } else {
                    return null;
                }
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return null;
    }

    // PreparedStatement
    public void updatePersonName(String name, int id) {
        String updateNameSql = "UPDATE persons SET name=? WHERE id=?";

        try (PreparedStatement preparedStatement = DatabaseConfiguration.getConnection().prepareStatement(updateNameSql)) { //try-with-resources
            preparedStatement.setString(1, name);
            preparedStatement.setInt(2, id);

            preparedStatement.executeUpdate();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    // Statement
    public List<Person> getPersons() {
        List<Person> personList = new ArrayList<>();
        String selectSql = "SELECT * FROM persons";
        try (Statement stmt = DatabaseConfiguration.getConnection().createStatement();
             ResultSet resultSet = stmt.executeQuery(selectSql)) { //try-with-resources
            while (resultSet.next()) {
                Person person = mapResultSetToPerson(resultSet);
                personList.add(person);
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        }
        return personList;
    }

    private Person mapResultSetToPerson(ResultSet resultSet) throws SQLException {
        return new Person(resultSet.getInt(1), resultSet.getString(2), resultSet.getDouble(3));
    }

}
