package be.kuleuven.dbproject.model.entities;

import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class Match extends Entity{

    //STANDAARD
    private final int ronde;

    //JOIN TABLE
    private String reeks = null;
    private String toernooi;

    public Match(Map<String, Object> dbMap) {
        super((Long) dbMap.get("id"));
        this.ronde = (int) dbMap.get("ronde");
        if(dbMap.containsKey("reeks_geslacht") && dbMap.containsKey("reeks_leeftijdsgroep")){
            String geslacht = (String) dbMap.get("reeks_geslacht");
            String leeftijd = (String) dbMap.get("reeks_leeftijdsgroep");
            reeks = Reeks.mooieZin(geslacht, leeftijd);
        }
        if(dbMap.containsKey("toernooi_datum") && dbMap.containsKey("club_naam")){
            String datum = dbMap.get("toernooi_datum").toString();
            String club = (String) dbMap.get("club_naam");
            toernooi = club + " - " + datum;
        }
    }

    @Override
    public String toString() {
        return String.format("Match[%d: %d]", getId(), ronde);
    }

    @Override
    public Set<String> tableIgnore() {
        Set<String> ignore = new HashSet<>();
        ignore.addAll(Set.of("id"));
        if(reeks == null){ignore.add("reeks");}
        if(toernooi == null){ignore.add("toernooi");}
        return ignore;
    }


}
