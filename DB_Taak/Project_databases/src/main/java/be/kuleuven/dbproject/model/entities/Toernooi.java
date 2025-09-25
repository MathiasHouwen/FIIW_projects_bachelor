package be.kuleuven.dbproject.model.entities;

import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import static be.kuleuven.dbproject.Application.querier;

public class Toernooi extends Entity {

    //STANDAARD
    private final String datum;
    private final long tennisclubId;
    private final long wedstrijdleider_id;

    //JOIN TABLE
    private String club = null;

    public Toernooi(Map<String, Object> dbMap) {
        super((Long) dbMap.get("id"));
        this.datum = dbMap.get("datum").toString();
        this.tennisclubId = (long) dbMap.get("tennisclub_id");

        if(dbMap.containsKey("club_naam")){
            club = (String) dbMap.get("club_naam");
        }
        wedstrijdleider_id = (long) dbMap.get("wedstrijdleider_id");
    }

    public long getWedstrijdleider_id() {
        return wedstrijdleider_id;
    }

    public String getDatum() {
        return datum;
    }

    public long getTennisclubId() {
        return tennisclubId;
    }

    @Override
    public String toString() {
        return String.format("Toernooi[%d: %s: %d: %s]", getId(), datum, tennisclubId);
    }

    @Override
    public Set<String> tableIgnore(){
        Set<String> ignore = new HashSet<>();
        ignore.addAll(Set.of("id", "tennisclubId", "wedstrijdleider_id"));
        if(club == null){ignore.add("club");}
        return ignore;
    }
}
