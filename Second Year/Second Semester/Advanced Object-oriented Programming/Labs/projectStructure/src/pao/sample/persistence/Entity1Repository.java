package pao.sample.persistence;


import pao.sample.model.Entity1;

import java.util.Arrays;

/**
 * Repositories are responsible for interacting with the storage of entities. Usually a 1-to-1 relation with the
 * entities. Any entity that should be persisted, should have a Repo.
 * */
public class Entity1Repository implements GenericRepository<Entity1> {

    private Entity1[] storage = new Entity1[10];

    @Override
    public void add(Entity1 entity) {
        // check if there's room in the storage
        for (int i=0; i<storage.length; i++) {
            if (storage[i] == null) {
                storage[i] = entity;
                return;
            }
        }
        // no place found. Increasing capacity
        Entity1[] newStorage = Arrays.<Entity1, Entity1>copyOf(storage, 2*storage.length, Entity1[].class);
        // add the new entry
        newStorage[storage.length] = entity;
        storage = newStorage;
    }

    @Override
    public Entity1 get(int index) {
        return storage[index];
    }

    @Override
    public void update(Entity1 entity) {
        // TODO: implement
    }

    @Override
    public void delete(Entity1 entity) {
        // TODO: implement
    }

    @Override
    public int getSize() {
        return storage.length;
    }
}
