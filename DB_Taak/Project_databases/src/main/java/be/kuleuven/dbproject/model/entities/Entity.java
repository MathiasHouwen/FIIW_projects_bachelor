package be.kuleuven.dbproject.model.entities;

import java.util.Set;

public abstract class Entity {

    private final long id;

    public Entity(long id){
        this.id = id;
    }
    public abstract String toString();
    public abstract Set<String> tableIgnore();

    public long getId() {
        return id;
    }
}
