package be.kuleuven.dbproject.controller;

import be.kuleuven.dbproject.Application;
import be.kuleuven.dbproject.model.db.GroteQueries;
import be.kuleuven.dbproject.model.entities.*;
import be.kuleuven.dbproject.model.entities.Speler;
import be.kuleuven.dbproject.view.EasyTableView;
import be.kuleuven.dbproject.view.MatchOverzichtView;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.TableView;
import javafx.scene.layout.VBox;
import javafx.util.Pair;

import java.util.List;
import java.util.Map;
import java.util.Set;

import static be.kuleuven.dbproject.Application.querier;

public class ToernooiController {

    @FXML
    public Label naamLbl;
    @FXML
    public Label leeftijdLbl;
    @FXML
    public Label geslachtLbl;

    @FXML
    public Label clubLbl;
    @FXML
    public Label nummerLbl;
    @FXML
    public Label rankLbl;

    @FXML
    public Label datumLbl;
    @FXML
    public Label locatieLbl;
    @FXML
    public Label thuisclubLbl;

    @FXML
    public Label reeksLbl;

    @FXML
    public TableView spelersTbl;
    @FXML
    public VBox matchenPane;
    @FXML
    public VBox rondesPane;
    @FXML
    public Label leiderLbl;


    private Speler speler;
    private Tennisclub spelerClub;

    private Toernooi toernooi;
    private Tennisclub toernooiClub;
    private Speler leider;
    private Reeks reeks;
    private List<Entity> spelers;
    private Map<Integer, List<Map<String, Object>>> rondes;
    private long[] vrijGestelden;

    public void initialize() {
        Pair<Speler, Toernooi> data = (Pair) Application.controllerShareData;
        speler = data.getKey();
        toernooi = data.getValue();

        getdata();
        fillLabels();
        fillMatchesOverzicht();

        EasyTableView.filltableExtraIgnore(spelersTbl, spelers, e->{}, Set.of("persoonlijk__email", "matches__gespeeld", "matches__gewonnenen", "matches__verloren", "hoogste_rank"));
    }

    private void getdata() {
        leider =        new Speler(     querier.getByID("spelers", toernooi.getWedstrijdleider_id()));
        spelerClub =    new Tennisclub( querier.getByID("tennisclubs", speler.getTennisclubID()));
        toernooiClub =  new Tennisclub( querier.getByID("tennisclubs", toernooi.getTennisclubId()));
        reeks =         GroteQueries.getDeelgenomenReeksVanSpelerIn1Toernooi(speler, toernooi);
        spelers =       GroteQueries.getSpelersInReeks(reeks);
        rondes =        GroteQueries.getComplexeRondeMapsVoorReeks(reeks);
        vrijGestelden = GroteQueries.getVrijgesteldeSpelerIDsVoorReeks(reeks);
    }
    private void fillMatchesOverzicht() {
        MatchOverzichtView.fillMatchesOverzicht(rondesPane, matchenPane, spelers, vrijGestelden, speler, rondes);
    }

    private void fillLabels(){
        naamLbl.setText(speler.getNaam());
        leeftijdLbl.setText(speler.getLeeftijd()+"");
        geslachtLbl.setText(speler.getGeslacht());

        clubLbl.setText(spelerClub.mooieNaam());
        nummerLbl.setText(speler.getNummer()+"");

        datumLbl.setText(toernooi.getDatum());
        locatieLbl.setText(toernooiClub.getLocatie());
        thuisclubLbl.setText(toernooiClub.getNaam());

        reeksLbl.setText(reeks.toMooieZin());

        int hoogsteRank = 1;
        for(List<Map<String, Object>> matches : rondes.values()){
            for(Map<String, Object> match : matches){
                if((long)match.get("speler1_id") == speler.getId() || (long)match.get("speler2_id") == speler.getId()){
                    hoogsteRank = (int) match.get("ronde");
                }
            }
        }
        rankLbl.setText("ronde "+hoogsteRank);
        leiderLbl.setText(leider.getNaam());

    }
}