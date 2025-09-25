package be.kuleuven.dbproject.model.entities;


import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class Speler extends Entity {

    //STANDAARD
    private final int nummer;
    private int hoogste_rank;
    private final String persoonlijk__naam;
    private final String persoonlijk__email;
    private final String fysiek__geslacht;
    private final int fysiek__leeftijd;
    private int matches__gespeeld;
    private int matches__gewonnenen;
    private final int matches__verloren;
    private final long tennisclubID;

    //JOIN TABLE
    private String club = null;

    public Speler(Map<String, Object> dbMap) {
        super((Long)dbMap.get("id"));
        nummer =                (int) dbMap.get("nummer");
        hoogste_rank =          (int) dbMap.get("hoogste ranking");
        persoonlijk__naam =     (String) dbMap.get("persoonlijk_naam");
        persoonlijk__email =    (String) dbMap.get("persoonlijk_email");
        fysiek__geslacht =      (String) dbMap.get("fysiek_geslacht");
        fysiek__leeftijd =      (int) dbMap.get("fysiek_leeftijd");
        matches__gespeeld =     (int) dbMap.get("aantal gespeelde matches");
        matches__gewonnenen =   (int) dbMap.get("aantal gewonnen matches");
        this.tennisclubID =     (long) dbMap.get("tennisclub_id");
        matches__verloren = matches__gespeeld - matches__gewonnenen;
        if(dbMap.containsKey("club_naam")){
            club = (String) dbMap.get("club_naam");
        }
    }

    public Set<String> tableIgnore(){
        Set<String> ignore = new HashSet<>();
        ignore.addAll(Set.of("id", "tennisclubID"));
        if(club == null){ignore.add("club");}
        return ignore;
    }

    public String getClub() {
        return club;
    }

    public String getNaam() {
        return persoonlijk__naam;
    }

    public String getEmail(){return persoonlijk__email;}
    public long getTennisclubID() {
        return tennisclubID;
    }

    public int getNummer() {
        return nummer;
    }

    public int getHoogste_rank() {
        return hoogste_rank;
    }

    public String getGeslacht() {
        return fysiek__geslacht;
    }

    public int getLeeftijd() {
        return fysiek__leeftijd;
    }

    public void verhoogAantalGespeeldeMatchen(){
        matches__gespeeld ++ ;
    }
    public void verhoogAantalGewonnenMatchen(){
        matches__gewonnenen ++ ;
    }

    public void setHoogste_rank(int hoogste_rank) {
        this.hoogste_rank = hoogste_rank;
    }

    public String getLeeftijdsRange(){
        if(this.fysiek__leeftijd < 11) return "5-10";
        else if(this.fysiek__leeftijd < 18) return "11-17";
        return "18+";
    }

    public int getMatches__gespeeld() {
        return matches__gespeeld;
    }

    public String getPersoonlijk__email() {
        return persoonlijk__email;
    }

    public String getFysiek__geslacht() {
        return fysiek__geslacht;
    }

    public int getFysiek__leeftijd() {
        return fysiek__leeftijd;
    }

    public int getMatches__verloren() {
        return matches__verloren;
    }

    public int getMatches__gewonnenen() {
        return matches__gewonnenen;
    }

    @Override
    public String toString() {
        return String.format("Speler[%d: %s]", getId(), persoonlijk__naam);
    }

}
