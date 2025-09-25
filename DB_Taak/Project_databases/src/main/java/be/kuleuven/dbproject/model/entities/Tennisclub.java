package be.kuleuven.dbproject.model.entities;

import java.util.Map;
import java.util.Set;

public class Tennisclub extends Entity {

    private final String naam;
    private final String locatie;

    public Tennisclub(Map<String, Object> dbMap) {
        super((Long) dbMap.get("id"));
        this.naam = (String) dbMap.get("naam");
        this.locatie = (String) dbMap.get("locatie");
    }

    public String getNaam() {
        return naam;
    }

    public String getLocatie() {
        return locatie;
    }

    @Override
    public String toString() {
        return String.format("Club[%d: %s-%s]", getId(), naam, locatie);
    }

    @Override
    public Set<String> tableIgnore() {
        return null;
    }

    public String mooieNaam(){
        return naam + " - " + locatie;
    }

}
