package be.kuleuven.dbproject.controller;

import be.kuleuven.dbproject.Application;
import be.kuleuven.dbproject.model.db.GroteQueries;
import be.kuleuven.dbproject.model.entities.Entity;
import be.kuleuven.dbproject.model.entities.Tennisclub;
import be.kuleuven.dbproject.model.entities.Speler;
import be.kuleuven.dbproject.view.EasyTableView;
import javafx.fxml.FXML;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.TableView;
import javafx.util.Pair;

import java.util.List;
import java.util.Map;

import static be.kuleuven.dbproject.Application.querier;

public class DashboardController  {

    @FXML
    public TableView reeksTbl;

    @FXML
    public TableView toernooienTbl;
    @FXML
    public Label leeftijdLbl;
    @FXML
    public Label geslachtLbl;
    @FXML
    public Label matchenLbl;
    @FXML
    public Label verlorenLbl;
    @FXML
    public Label gewonnenLbl;

    @FXML
    public TableView inschrijvingsTbl;

    @FXML
    private Label clubLbl;

    @FXML
    private Label naamLbl;

    @FXML
    private Label rankingLbl;

    @FXML
    private Button scheidsrechterBtn;

    @FXML
    private Button wedstrijdleiderBtn;

    private Speler speler;
    private Tennisclub club;

    private enum Scherm{ TOERNOOI, SCHEIDS, LEIDER}

    @FXML
    void initialize() {
        speler = (Speler) Application.controllerShareData;
        club = new Tennisclub(querier.getByID("tennisclubs", speler.getTennisclubID()));

        checkButtons();
        scheidsrechterBtn.setOnAction(e -> switchView(Scherm.SCHEIDS));
        wedstrijdleiderBtn.setOnAction(e -> switchView(Scherm.LEIDER));
        updateLabels();

        // TABLE VOOR MOGELIJK DEELNAMES
        loadReeksTable();

        List<Entity> gespeeldeToernooien = GroteQueries.gespeeldeToernooienVanSpeler(speler);
        EasyTableView.fillTable(toernooienTbl, gespeeldeToernooien, this::gotoToernooiScherm);
    }

    private void loadReeksTable(){
        reeksTbl.getItems().clear();
        inschrijvingsTbl.getItems().clear();

        List<Entity> reeksen = GroteQueries.gepasteOngespeeldeReeksVoorSpeler(speler);
        EasyTableView.fillTable(reeksTbl, reeksen, this::schrijfSpelerIn);

        List<Entity> inschrijvingen = GroteQueries.gepasteOpkomendeReeksVoorSpeler(speler);
        EasyTableView.fillTable(inschrijvingsTbl, inschrijvingen, this::schrijfSpelerUit);
    }

    private void schrijfSpelerIn(Entity reeks){
        GroteQueries.insertSpelerInschrijvingen(speler, reeks);
        loadReeksTable();
    }

    private void schrijfSpelerUit(Entity reeks){
        GroteQueries.schrijfSpelerUit(speler, reeks);
        loadReeksTable();
    }

    private void gotoToernooiScherm(Entity toernoi){
        Application.controllerShareData = new Pair(speler, toernoi);
        switchView(Scherm.TOERNOOI);
    }

    private void checkButtons(){
        Map<String, Object> scheidsCount = querier.queryToMap1Item("SELECT count(*) AS cnt FROM matchen WHERE scheidsrechter_id = '"+speler.getId()+"'");
        Map<String, Object> leidersCount = querier.queryToMap1Item("SELECT count(*) AS cnt FROM toernoois WHERE wedstrijdleider_id = '"+speler.getId()+"'");
        wedstrijdleiderBtn.setDisable((long)leidersCount.get("cnt") == 0);
        scheidsrechterBtn.setDisable((long)scheidsCount.get("cnt") == 0);
    }

    void switchView(Scherm soort) {
        switch (soort){
            case SCHEIDS: Application.setScene("scheidsrechter-view.fxml"); break;
            case LEIDER: Application.setScene("wedstrijdleider-view.fxml"); break;
            case TOERNOOI: Application.setScene("toernooi-view.fxml"); break;
        }
    }

    void updateLabels(){
        naamLbl.setText(speler.getNaam());
        rankingLbl.setText(String.valueOf(speler.getHoogste_rank()));
        clubLbl.setText(club.getNaam() + " - " + club.getLocatie());
        leeftijdLbl.setText(speler.getFysiek__leeftijd()+"");
        geslachtLbl.setText(speler.getGeslacht()+"");
        matchenLbl.setText(speler.getMatches__gespeeld()+"");
        verlorenLbl.setText(speler.getMatches__verloren()+"");
        gewonnenLbl.setText(speler.getMatches__gewonnenen()+"");
    }
}