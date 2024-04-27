package jdbc.service;

import jdbc.exception.InvalidPersonException;
import jdbc.model.Person;
import jdbc.repository.PersonRepository;

import java.util.List;

public class PersonService {

    private PersonRepository personRepository = new PersonRepository();

    public void registerNewPerson(String name, int age) throws InvalidPersonException {
        if (name == null || name.trim().isEmpty()) {
            throw new InvalidPersonException("Invalid name");
        }
        if (age <= 0) {
            throw new InvalidPersonException("Invalid age");
        }
        Person person = new Person(name, age);
        personRepository.insertPerson(person);
    }

    public Person getPersonById(int id) {
        return personRepository.getPersonById(id);
    }

    public void updatePersonNameForId(String name, int id) throws InvalidPersonException {
        if (name == null || name.trim().isEmpty()) {
            throw new InvalidPersonException("Invalid name");
        }
        personRepository.updatePersonName(name, id);
    }

    public List<Person> getAllPersons() {
        return personRepository.getPersons();
    }
}
