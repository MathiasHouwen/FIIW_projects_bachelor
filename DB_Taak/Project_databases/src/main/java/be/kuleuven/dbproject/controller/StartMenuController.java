package be.kuleuven.dbproject.controller;

import be.kuleuven.dbproject.Application;
import be.kuleuven.dbproject.model.db.GroteQueries;
import be.kuleuven.dbproject.model.db.Wedstrijdgenerator;
import be.kuleuven.dbproject.model.entities.*;
import be.kuleuven.dbproject.view.EasyTableView;
import javafx.collections.ObservableArray;
import javafx.collections.ObservableList;
import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.scene.control.*;
import javafx.util.Pair;

import java.time.LocalDate;
import java.util.Date;
import java.util.List;
import java.util.Map;
import java.util.Random;
import java.util.stream.Collectors;

import static be.kuleuven.dbproject.Application.querier;

public class StartMenuController {

    @FXML
    public Label errorLbl;  //login
    @FXML
    public Label errorLbl1; //new
    @FXML
    public TextField newEmailInput;
    @FXML
    public TextField newNaamInput;
    @FXML
    public ChoiceBox clubSelect;
    @FXML
    public Button newSpelerBtn;
    @FXML
    public ChoiceBox geslachtSelect;
    @FXML
    public TextField leeftijdInput;

    //DEVCHEATS
    @FXML
    public TableView devCheats_spelersTbl;
    public TableView devCheat_ongespeeldeReeksenTbl;
    public Label devCheats_reeksenLbl;
    public Label devCHeats_inschrijvingLbl;
    public ChoiceBox<Integer> devCheats_inschrijvingAanvulInput;
    public Button devCheat_wedstrijdGenerateBtn;
    public TableView devCheat_deelnemersTbl;
    public ChoiceBox devCheats_clubSelect;
    public CheckBox devCheats_alleenVolwassenInput;
    public DatePicker devCheats_datumInput;
    public Button devCheats_insertBtn;

    private Reeks devCheatReeks = null;
    private List<Entity> devCheatInschrijvingenInReeks = List.of();

    @FXML
    private Button loginBtn;

    @FXML
    private TextField emailInput;

    @FXML
    public void initialize(){
        errorLbl.setText("");
        errorLbl1.setText("");
        loginBtn.setOnAction(e -> goToView(emailInput.getText()));

        initSelectMenus();


        devCheats_maakSpelersTbl();
        devCheats_updateMatchGeneratorView();
        devCheats_insertBtn.setOnAction(this::devCheats_insertToernooi);
        devCheats_alleenVolwassenInput.setSelected(true);
    }

    private void initSelectMenus(){
        newSpelerBtn.setOnAction(this::voegNieuweSpelerToe);
        geslachtSelect.getItems().addAll("man", "vrouw");
        List<String> alleClubs = querier.getFullTable("tennisclubs")
                .stream().map(Tennisclub::new).map(Tennisclub::getNaam).collect(Collectors.toList());
        clubSelect.getItems().addAll(alleClubs);
        devCheats_clubSelect.getItems().addAll(alleClubs);

        geslachtSelect.getSelectionModel().select(0);
        clubSelect.getSelectionModel().select(0);
        devCheats_clubSelect.getSelectionModel().select(0);
    }

    private void voegNieuweSpelerToe(ActionEvent actionEvent) {
        String naam = newNaamInput.getText();
        String email = newEmailInput.getText();
        String leeftijdString = leeftijdInput.getText();
        int leeftijd = 0;
        try {
            leeftijd = Integer.parseInt(leeftijdString);
            if(leeftijd < 5){
                errorLbl1.setText("leeftijd moet minstens 5 zijn");
                return;
            }
        } catch (Exception e){
            errorLbl1.setText("leeftijd moet getal zijn");
            return;
        }
        String geslacht = (String) geslachtSelect.getSelectionModel().getSelectedItem();
        String club = (String) clubSelect.getSelectionModel().getSelectedItem();
        if(List.of(geslacht, club, naam, leeftijd).contains("")){
            errorLbl1.setText("Vul alle velden in");
            return;
        }
        Map<String, Object> clubInfo = GroteQueries.getNummerEnClubIDVoorNewSpeler(club);
        errorLbl1.setText("");
        Map<String, Object> dbMap = Map.ofEntries(
                Map.entry("persoonlijk_naam", naam),
                Map.entry("persoonlijk_email", email),
                Map.entry("fysiek_leeftijd", leeftijd),
                Map.entry("fysiek_geslacht", geslacht),
                Map.entry("tennisclub_id", clubInfo.get("id")),
                Map.entry("nummer", (int)clubInfo.get("max_num")+1)
        );
        querier.insert("spelers", dbMap);
        devCheats_maakSpelersTbl();
    }

    private void goToView(String spelerEmail) {

        Map<String, Object> spelerMap = querier.queryToMap1Item("SELECT * FROM spelers WHERE persoonlijk_email = '"+spelerEmail+"'");
        if(spelerMap == null){
            errorLbl.setText("Kon deze speler niet vinden");
            return;
        }

        Application.controllerShareData = new Speler(spelerMap);
        Application.setScene("dashboard.fxml");
    }

    /*
        DEVCHEATS
     */

    private void devCheats_maakSpelersTbl(){
        devCheats_spelersTbl.getItems().clear();
        List<Entity> spelers = querier.getFullTable("spelers").stream().map(Speler::new).collect(Collectors.toList());
        EasyTableView.fillTable(devCheats_spelersTbl, spelers, e -> emailInput.setText(((Speler)e).getEmail()));
    }

    private void devCheats_maakReeksenTbl(){
        devCheat_ongespeeldeReeksenTbl.getItems().clear();
        List<Entity> reeksen = GroteQueries.getAlleOngespeeldeReeksen();
        EasyTableView.fillTable(devCheat_ongespeeldeReeksenTbl, reeksen, e -> {
            devCheatReeks = (Reeks) e;
            devCheats_updateMatchGeneratorView();
        });
    }
    private void devCheats_maakDeelnemersTbl(Wedstrijdgenerator gen){
        List<Entity> deelnemers = gen.getDeelnemers();
        Toernooi toernooi = gen.getToernooi();
        devCheat_deelnemersTbl.getItems().clear();
        EasyTableView.fillTable(devCheat_deelnemersTbl, deelnemers, s -> {
            Application.controllerShareData = new Pair(s, toernooi);
            Application.setScene("toernooi-view.fxml");
        });
    }

    private void devCheats_updateMatchGeneratorView(){
        devCheats_maakReeksenTbl();
        if(devCheatReeks == null) return;
        devCheats_inschrijvingAanvulInput.getItems().clear();

        devCheatInschrijvingenInReeks = GroteQueries.getInschrijvingenVoorReeks(devCheatReeks);
        devCheats_reeksenLbl.setText(devCheatReeks.toMooieZin()+" - "+devCheatReeks.getToernooi());
        int inschrijvingenInitieel = devCheatInschrijvingenInReeks.size();
        devCHeats_inschrijvingLbl.setText(inschrijvingenInitieel+"");
        for(int i=inschrijvingenInitieel > 5 ? inschrijvingenInitieel : 6; i<=20; i++){
            devCheats_inschrijvingAanvulInput.getItems().add(i);
        }
        devCheats_inschrijvingAanvulInput.getSelectionModel().select(0);

        devCheat_wedstrijdGenerateBtn.setOnAction(e -> {
            int inschrijvingenAanvul = devCheats_inschrijvingAanvulInput.getSelectionModel().getSelectedItem();
            Wedstrijdgenerator gen = new Wedstrijdgenerator(devCheatReeks, devCheatInschrijvingenInReeks, inschrijvingenAanvul);
            gen.generate();
            devCheats_maakDeelnemersTbl(gen);
            devCheats_updateMatchGeneratorView();
        });
    }

    private void devCheats_insertToernooi(ActionEvent actionEvent) {
        String clubString = (String) devCheats_clubSelect.getSelectionModel().getSelectedItem();
        LocalDate datum = devCheats_datumInput.getValue();
        if(datum == null) return;
        boolean alleenVolwassen = devCheats_alleenVolwassenInput.isSelected();

        Tennisclub club = new Tennisclub(querier.get1Equals("tennisclubs", "naam", clubString));
        List<Entity> spelers = GroteQueries.getAlleSpelersVanClub(club);
        Random rand = new Random(System.currentTimeMillis());
        int leiderIndex = rand.nextInt(spelers.size());
        Entity leider = spelers.get(leiderIndex);

        querier.insert("toernoois", List.of("datum", "tennisclub_id", "wedstrijdleider_id"),
                List.of(datum.toString(), club.getId(), leider.getId()));

        long toernooiID = (long) querier.queryToMap1Item("SELECT MAX(id) AS m FROM toernoois;").get("m");

        querier.insert("reeksen", List.of("leeftijdsgroep", "geslacht", "toernooi_id", "gespeeld"), List.of("18+", "man", toernooiID, false));
        querier.insert("reeksen", List.of("leeftijdsgroep", "geslacht", "toernooi_id", "gespeeld"), List.of("18+", "vrouw", toernooiID, false));
        if(!alleenVolwassen){
            querier.insert("reeksen", List.of("leeftijdsgroep", "geslacht", "toernooi_id", "gespeeld"), List.of("5-10", "man", toernooiID, false));
            querier.insert("reeksen", List.of("leeftijdsgroep", "geslacht", "toernooi_id", "gespeeld"), List.of("5-10", "vrouw", toernooiID, false));
            querier.insert("reeksen", List.of("leeftijdsgroep", "geslacht", "toernooi_id", "gespeeld"), List.of("11-17", "man", toernooiID, false));
            querier.insert("reeksen", List.of("leeftijdsgroep", "geslacht", "toernooi_id", "gespeeld"), List.of("11-17", "vrouw", toernooiID, false));
        }
        devCheats_updateMatchGeneratorView();
    }




}