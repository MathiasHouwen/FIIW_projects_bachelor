package be.kuleuven.dbproject.model.entities;

import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class Reeks extends Entity {

    //STANDAARD
    private final String leeftijdsgroep;
    private final String geslacht;
    private final long toernooiID;

    //JOIN TABLE
    private String toernooi;

    public Reeks(Map<String, Object> dbMap) {
        super((Long) dbMap.get("id"));

        leeftijdsgroep =        (String) dbMap.get("leeftijdsgroep");
        geslacht =              (String) dbMap.get("geslacht");
        toernooiID =            (Long) dbMap.get("toernooi_id");

        if(dbMap.containsKey("toernooi_datum") && dbMap.containsKey("club_naam")){
            String datum =  dbMap.get("toernooi_datum").toString();
            String club =   (String) dbMap.get("club_naam");
            toernooi = club + " - " + datum;
        }
    }

    @Override
    public String toString() {
        return String.format("Reeks[%d: %s %s]", getId(), leeftijdsgroep, geslacht);
    }

    public String toMooieZin(){
        return mooieZin(geslacht, leeftijdsgroep);
    }

    public static String mooieZin(String geslacht, String leeftijdsgroep){
        String geslachtMeervoud = geslacht.equals("man") ? "mannen" : "vrouwen";
        String jaar = leeftijdsgroep.equals("18+") ? "volwasennen" : leeftijdsgroep+" jaar";
        return geslachtMeervoud + "reeks - "+jaar;
    }

    public String getGeslacht() {
        return geslacht;
    }

    public long getToernooiID() {
        return toernooiID;
    }

    public String getToernooi() {
        return toernooi;
    }

    public boolean gepasteLeeftijd(int leeftijd){
        if(leeftijdsgroep.equals("18+")) return leeftijd >= 18;
        if(leeftijdsgroep.equals("11-17")) return leeftijd >= 11 && leeftijd <= 17;
        if(leeftijdsgroep.equals("5-10")) return leeftijd >= 5 && leeftijd <= 10;
        return false;
    }

    @Override
    public Set<String> tableIgnore() {
        Set<String> ignore = new HashSet<>();
        ignore.addAll(Set.of("id", "toernooiID"));
        if(toernooi == null){ignore.add("toernooi");}
        return ignore;
    }
}
