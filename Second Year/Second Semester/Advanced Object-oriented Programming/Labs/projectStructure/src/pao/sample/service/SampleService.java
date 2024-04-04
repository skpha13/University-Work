package pao.sample.service;

import pao.sample.exceptions.InvalidDataException;
import pao.sample.model.Entity1;
import pao.sample.persistence.Entity1Repository;


import java.util.ArrayList;
import java.util.List;

/** Services should expose as public methods all actions that the business should support.
 * Similar functionalities should be grouped in corresponding services.
 * */
public class SampleService {

    /** services will have a way of obtaining repositories. One service can use multiple (or no) repositories. */
    private Entity1Repository entity1Repository = new Entity1Repository();

    /**
     * Registers a new Entity in the system.
     * Checks if the name and age are valid.
     *
     * @param name The name of the entity
     * @param age The age of the entity
     * @throws InvalidDataException if any of the supplied values are incorrect
     * */
    public void registerNewEntity(String name, int age) throws InvalidDataException {

        if (name == null || name.trim().isEmpty()) {
            throw new InvalidDataException("Invalid name");
        }
        if (age <= 0) {
            throw new InvalidDataException("Invalid age");
        }
        Entity1 entity = new Entity1(name, age);
        entity1Repository.add(entity);
    }

    /**
     * Returns a list of entities that have the age of at least the supplied value
     * @param age The age to filter on
     * @return A list of entities that have the age >= the supplied age.
     */
    public Entity1[] getAllEntitiesWithAgeOver(int age) {
        List<Entity1> result = new ArrayList<>();
        for (int i = 0; i < entity1Repository.getSize(); i++) {
            if (entity1Repository.get(i) != null && entity1Repository.get(i).getAge() >= age) {
                result.add(entity1Repository.get(i));
            }
        }
        return result.toArray(new Entity1[0]);
    }

}
