package be.kuleuven.dbproject.model.db;

import be.kuleuven.dbproject.model.entities.*;

import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

import static be.kuleuven.dbproject.Application.querier;

public class GroteQueries {


    public static List<Entity> toernooienVanLeider(Speler leider){
        return querier.queryToMapList("""
                    SELECT DISTINCT s.*, c.naam AS club_naam
                    FROM toernoois s
                    JOIN tennisclubs c ON s.tennisclub_id = c.id
                    WHERE s.wedstrijdleider_id = """+leider.getId()+";")
            .stream()
            .map(Toernooi::new)
            .collect(Collectors.toList());
    }
    public static List<Entity> matchenVanScheids(Speler scheids){
        return querier.queryToMapList("""
                SELECT m.*,
                r.geslacht AS reeks_geslacht,
                r.leeftijdsgroep AS reeks_leeftijdsgroep,
                t.datum AS toernooi_datum,
                c.naam AS club_naam
                FROM matchen m
                JOIN reeksen r ON r.id = m.reeks_id
                JOIN toernoois t ON r.toernooi_id = t.id
                JOIN tennisclubs c ON t.tennisclub_id = c.id
                WHERE m.scheidsrechter_id = """+scheids.getId()+";")
                .stream()
                .map(Match::new)
                .collect(Collectors.toList());
    }
    public static List<Entity> gespeeldeToernooienVanSpeler(Speler speler){
        return querier.queryToMapList("""
                SELECT DISTINCT t.*, c.naam AS club_naam
                FROM toernoois t
                JOIN tennisclubs c on t.tennisclub_id = c.id
                JOIN reeksen r ON t.id = r.toernooi_id
                JOIN matchen m ON m.reeks_id = r.id
                JOIN deelnames d ON d.match_id = m  .id
                WHERE d.speler_id = %d
                """.formatted(speler.getId()))
                .stream()
                .map(Toernooi::new)
                .collect(Collectors.toList());
    }


    public static List<Entity> gepasteOngespeeldeReeksVoorSpeler(Speler speler){
        return querier.queryToMapList("""
                 SELECT r.*, t.datum AS toernooi_datum, c.naam AS club_naam
                 FROM reeksen r
                 JOIN toernoois t on r.toernooi_id = t.id
                 JOIN tennisclubs c on t.tennisclub_id = c.id
                 WHERE r.leeftijdsgroep = '%s'
                   AND r.geslacht = '%s'
                   AND r.gespeeld = 0
                   AND r.id NOT IN
                    (SELECT i.reeks_id FROM inschrijvingen i
                    WHERE i.speler_id = '%s')
                 """.formatted(speler.getLeeftijdsRange(), speler.getGeslacht(), speler.getId()))
                .stream()
                .map(Reeks::new)
                .collect(Collectors.toList());
    }

    public static List<Entity> gepasteOpkomendeReeksVoorSpeler(Speler speler){
        return querier.queryToMapList("""
                 SELECT r.*, t.datum AS toernooi_datum, c.naam AS club_naam
                 FROM reeksen r
                 JOIN toernoois t on r.toernooi_id = t.id
                 JOIN tennisclubs c on t.tennisclub_id = c.id
                 WHERE r.leeftijdsgroep = '%s'
                   AND r.geslacht = '%s'
                   AND r.gespeeld = 0
                   AND r.id IN
                    (SELECT i.reeks_id FROM inschrijvingen i
                    WHERE i.speler_id = '%s')
                 """.formatted(speler.getLeeftijdsRange(), speler.getGeslacht(), speler.getId()))
                .stream()
                .map(Reeks::new)
                .collect(Collectors.toList());
    }

    public static List<Entity> getSpelersInReeks(Reeks reeks){
        return querier.queryToMapList("""
                SELECT DISTINCT s.*, c.naam AS club_naam
                FROM spelers s
                JOIN tennisclubs c ON s.tennisclub_id = c.id
                JOIN deelnames d ON s.id = d.speler_id
                JOIN matchen m ON d.match_id = m.id
                WHERE m.reeks_id = """+reeks.getId()+";").stream()
                .map(Speler::new)
                .collect(Collectors.toList());
    }

    public static Reeks getDeelgenomenReeksVanSpelerIn1Toernooi(Speler speler, Toernooi toernooi){
        return new Reeks(querier.queryToMap1Item("""
                SELECT DISTINCT r.*
                FROM reeksen r
                JOIN matchen m ON r.id = m.reeks_id
                JOIN deelnames d ON m.id = d.match_id
                WHERE d.speler_id = """+speler.getId()+
                "\nAND r.toernooi_id = "+toernooi.getId()+";"));
    }
    public static Map<Integer, List<Map<String, Object>>> getComplexeRondeMapsVoorReeks(Reeks reeks){
        return querier.queryToMapList("""
                SELECT
                    m.id AS match_id,
                    m.ronde,
                    d1.speler_id AS speler1_id,
                    d1.score AS score1,
                    d2.speler_id AS speler2_id,
                    d2.score AS score2,
                    s.persoonlijk_naam AS scheids
                FROM matchen m
                JOIN reeksen r ON r.id = m.reeks_id
                JOIN deelnames d1 ON m.id = d1.match_id
                JOIN deelnames d2 ON m.id = d2.match_id
                LEFT JOIN spelers s ON s.id = m.scheidsrechter_id
                WHERE d1.vrijstelling = 0
                AND d2.vrijstelling = 0
                AND r.id = """+reeks.getId()+
                "\n AND d1.speler_id < d2.speler_id;")
                .stream()
                .collect(Collectors.groupingBy(match -> (Integer) match.get("ronde")));
    }
    public static long[] getVrijgesteldeSpelerIDsVoorReeks(Reeks reeks){
        return querier.queryToMapList("""
                SELECT d.speler_id
                FROM deelnames d
                JOIN matchen m ON d.match_id = m.id
                JOIN reeksen r ON r.id = m.reeks_id
                WHERE d.vrijstelling = 1
                AND r.id = """+reeks.getId()+";").stream()
                .mapToLong(s -> (Long) s.get("speler_id"))
                .toArray();
    }
    public static void insertSpelerInschrijvingen(Entity speler, Entity reeks){
        querier.insert("inschrijvingen", List.of("speler_id", "reeks_id"), List.of(speler.getId(), reeks.getId()));
    }

    public static void schrijfSpelerUit(Entity speler, Entity reeks){
        querier.removeInschrijving("inschrijvingen", "speler_id", speler.getId(), "reeks_id", reeks.getId());
    }

    public static Map<String, Object> getNummerEnClubIDVoorNewSpeler(String clubNaam){
        return querier.queryToMap1Item("""
                SELECT t.id AS id, max(s.nummer) AS max_num
                FROM tennisclubs t
                JOIN spelers s ON t.id = s.tennisclub_id
                WHERE t.naam = '%s';
                """.formatted(clubNaam));
    }

    public static List<Entity> getAlleOngespeeldeReeksen(){
        return querier.queryToMapList("""
                SELECT r.*, c.naam AS club_naam, t.datum AS toernooi_datum
                FROM reeksen r
                JOIN toernoois t ON r.toernooi_id = t.id
                JOIN tennisclubs c ON t.tennisclub_id = c.id
                WHERE r.gespeeld = 0;""").stream()
                .map(Reeks::new)
                .collect(Collectors.toList());
    }

    public static List<Entity> getInschrijvingenVoorReeks(Reeks reeks) {
        return querier.queryToMapList("""
                SELECT DISTINCT s.*
                FROM spelers s
                JOIN inschrijvingen i ON i.speler_id = s.id
                WHERE i.reeks_id = """+reeks.getId()+";").stream()
                .map(Speler::new)
                .collect(Collectors.toList());
    }

    public static List<Entity> getAlleSpelersVanClub(Tennisclub club){
        return querier.queryToMapList("""
                SELECT s.*
                FROM spelers s
                JOIN tennisclubs c ON c.id = s.tennisclub_id
                WHERE c.id = """+club.getId()+";").stream()
                .map(Speler::new)
                .collect(Collectors.toList());
    }
}
