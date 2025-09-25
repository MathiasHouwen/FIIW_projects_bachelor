package be.kuleuven.dbproject.model.db;

import be.kuleuven.dbproject.model.entities.Entity;
import be.kuleuven.dbproject.model.entities.Reeks;
import be.kuleuven.dbproject.model.entities.Speler;
import be.kuleuven.dbproject.model.entities.Toernooi;

import java.util.*;
import java.util.stream.Collectors;

import static be.kuleuven.dbproject.Application.querier;

public class Wedstrijdgenerator {

    Random rand;

    Reeks reeks;

    List<Entity> ingeschrevenSpelers;
    List<Entity> initieelIngeschrevenSpelers;

    Toernooi toernooi;

    List<Speler> mogelijkeScheidsrechters;

    public Wedstrijdgenerator(Reeks reeks, List<Entity> ingeschrevenSpelers, int inshcrijvingAanvul) {
        rand = new Random(System.currentTimeMillis());
        this.reeks = reeks;
        this.initieelIngeschrevenSpelers = ingeschrevenSpelers;
        this.ingeschrevenSpelers = new ArrayList<>(ingeschrevenSpelers);
        mogelijkeScheidsrechters = new ArrayList<>();
        toernooi = new Toernooi(querier.getByID("toernoois", reeks.getToernooiID()));
        vulInshcrijvingenEnMogelijkeScheidsRechtersAan(inshcrijvingAanvul);
    }

    public List<Entity> getDeelnemers(){
        return ingeschrevenSpelers;
    }

    public Toernooi getToernooi() {
        return toernooi;
    }

    public void generate(){
        int aantalVrijstellingen = aantalVrijstellingen();

        final int aantalSpelersTotaal = ingeschrevenSpelers.size();
        final int aantalSpelers2deRonde = aantalVrijstellingen + (aantalSpelersTotaal-aantalVrijstellingen)/2;
        final int aantalRondes = (int) (Math.log(aantalSpelers2deRonde)/Math.log(2) ) + 1;

        long matchID = (long) querier.queryToMap1Item("SELECT MAX(id) AS m FROM matchen;").get("m") +1;
        int scheidsIndex = 0;

        List<Entity> spelersInRonde = new ArrayList<>(ingeschrevenSpelers);

        for(int ronde = 1; ronde <= aantalRondes; ronde ++){

            Collections.shuffle(spelersInRonde);

            //INSERT VRIJSTELLINGEN
            List<Entity> vrijgesteldeSpelers = genereerVrijstellingen(aantalVrijstellingen, spelersInRonde, matchID);
            aantalVrijstellingen = 0;

            List<Speler> spelersInMatchen = new ArrayList<>();
            List<Speler> verliezers = new ArrayList<>();


            //GENEREER MATCHEN
            for(Entity speler : spelersInRonde){
                //conains manueel zoeken want speler info zoals hoogsterank kan veranderen tussen matchen
                boolean contains = false;
                for(Entity vrijgesteldeSpeler : vrijgesteldeSpelers) {
                    if (vrijgesteldeSpeler.getId() == speler.getId()){
                        contains = true;
                        break;
                    }
                }
                if(!contains) spelersInMatchen.add((Speler) speler);
            }

            int aantalMatchen = spelersInMatchen.size() / 2;
            int spelerIndex = 0;

            for(int i = 0; i<aantalMatchen; i++){

                //INSERT match in DB
                scheidsIndex = insertMatchInDB(matchID, ronde, aantalRondes, scheidsIndex);

                //INSERT deelnames in DB
                genereerDeelnamesEnUpdateSpelers(spelersInMatchen, spelerIndex, ronde, matchID, verliezers);

                matchID++;
                spelerIndex += 2;
            }
            for(Entity verliezer : verliezers){
                spelersInRonde.remove(verliezer);
            }
        }
        clearInschrijvingenUitDBEnSetReeksNaarGespeeld();
    }

    private int insertMatchInDB(long matchID, int ronde, int aantalRondes, int scheidsIndex) {
        Map<String, Object> match = new HashMap<>(Map.ofEntries(
                Map.entry("id", matchID),
                Map.entry("ronde", ronde),
                Map.entry("reeks_id", reeks.getId())));
        if(ronde >= aantalRondes -1){
            match.put("scheidsrechter_id", mogelijkeScheidsrechters.get(scheidsIndex).getId());
            scheidsIndex++;
        }
        querier.insert("matchen", match);
        return scheidsIndex;
    }

    private List<Entity> genereerVrijstellingen(int aantalVrijstellingen, List<Entity> spelersInRonde, long matchID){
        List<Entity> vrijgesteldeSpelers = new ArrayList<>();
        if(aantalVrijstellingen > 0){
            vrijgesteldeSpelers = spelersInRonde.subList(0, aantalVrijstellingen);
            for(Entity speler : vrijgesteldeSpelers){
                querier.insert("deelnames", List.of("speler_id", "vrijstelling", "match_id"), List.of(speler.getId(), 1, matchID));
            }
        }
        return vrijgesteldeSpelers;
    }

    private void genereerDeelnamesEnUpdateSpelers(List<Speler> spelersInMatchen, int spelerIndex, int ronde, long matchID, List<Speler> verliezers) {
        Speler speler1 = spelersInMatchen.get(spelerIndex);
        Speler speler2 = spelersInMatchen.get(spelerIndex +1);
        int score1 = rand.nextInt(3, 11);
        int score2 = rand.nextInt(3, 11);
        if(score1 == score2) score2++;  //simuleer een penalty (of hoe dat ook heet bij tennis) bij gelijkspel
        Speler verliezer = score1 < score2 ? speler1 : speler2;
        Speler winnaar = score1 > score2 ? speler1 : speler2;

        updateSpelerInfo(speler1, speler2, ronde, winnaar);
        insertDeelnamesInDB(speler1, matchID, score1, speler2, score2);

        verliezers.add(verliezer);
    }

    private void updateSpelerInfo(Speler speler1, Speler speler2, int ronde, Speler winnaar) {
        speler1.verhoogAantalGespeeldeMatchen();
        speler2.verhoogAantalGespeeldeMatchen();
        if(ronde > speler1.getHoogste_rank())  speler1.setHoogste_rank(ronde);
        if(ronde > speler2.getHoogste_rank())  speler2.setHoogste_rank(ronde);
        winnaar.verhoogAantalGewonnenMatchen();
        querier.update("spelers",
                List.of("hoogste ranking", "aantal gespeelde matches", "aantal gewonnen matches"),
                List.of(speler1.getHoogste_rank(), speler1.getMatches__gespeeld(), speler1.getMatches__gewonnenen()),
                speler1.getId());
        querier.update("spelers",
                List.of("hoogste ranking", "aantal gespeelde matches", "aantal gewonnen matches"),
                List.of(speler2.getHoogste_rank(), speler2.getMatches__gespeeld(), speler2.getMatches__gewonnenen()),
                speler2.getId());
    }

    private void insertDeelnamesInDB(Speler speler1, long matchID, int score1, Speler speler2, int score2) {
        querier.insert("deelnames",
                List.of("speler_id","match_id","score", "vrijstelling"),
                List.of(speler1.getId(), matchID, score1, false));
        querier.insert("deelnames",
                List.of("speler_id","match_id","score", "vrijstelling"),
                List.of(speler2.getId(), matchID, score2, false));
    }

    private boolean isMachtVan2(int getal){
        return ((getal & (getal - 1)) == 0) && getal != 0;
    }

    private int aantalVrijstellingen(){
        final int aantalSpelers = ingeschrevenSpelers.size();
        for(int aantalMatches = aantalSpelers/2; aantalMatches >= 1; aantalMatches--){
            final int spelersInMatch = aantalMatches*2;
            final int spelersVrij = aantalSpelers - spelersInMatch;
            final int spelersNaRonde = aantalMatches + spelersVrij;
            if(isMachtVan2(spelersNaRonde)) return spelersVrij;
        }
        return 0;
    }


    private void vulInshcrijvingenEnMogelijkeScheidsRechtersAan(int inshcrijvingAanvul){
        int size = ingeschrevenSpelers.size();
        if(size == inshcrijvingAanvul) return;

        List<Speler> alleSpelers= querier.getFullTable("spelers").stream().map(Speler::new).collect(Collectors.toList());
        Collections.shuffle(alleSpelers);
        int i = 0;
        while (size < inshcrijvingAanvul){
            Speler mogelijkeSpeler = alleSpelers.get(i);
            i++;
            if(reeks.gepasteLeeftijd(mogelijkeSpeler.getLeeftijd())
                    && reeks.getGeslacht().equals(mogelijkeSpeler.getGeslacht())
                    && mogelijkeSpeler.getId() != toernooi.getWedstrijdleider_id()){
                ingeschrevenSpelers.add(mogelijkeSpeler);
                size ++;
            }
        }
        System.out.println(ingeschrevenSpelers);
        for(Speler speler : alleSpelers){
            if(!ingeschrevenSpelers.contains(speler)){
                mogelijkeScheidsrechters.add(speler);
            }
        }
    }

    private void clearInschrijvingenUitDBEnSetReeksNaarGespeeld(){
        for(Entity speler : initieelIngeschrevenSpelers){
            querier.remove("inschrijvingen", "speler_id", speler.getId());
        }
        querier.update("reeksen", List.of("gespeeld"), List.of(true), reeks.getId());
    }

}
