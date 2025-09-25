package be.kuleuven.dbproject.controller;

import be.kuleuven.dbproject.Application;
import be.kuleuven.dbproject.model.entities.Entity;
import be.kuleuven.dbproject.model.entities.Speler;
import be.kuleuven.dbproject.view.EasyTableView;
import javafx.fxml.FXML;
import javafx.scene.control.TableView;

import java.util.List;
import java.util.stream.Collectors;

import static be.kuleuven.dbproject.Application.querier;

public class SpelersViewController {

    @FXML
    public TableView playersTbl;

    public void initialize() {
        List<Entity> spelers = querier.getFullTable("spelers").stream()
                .map(Speler::new)
                .collect(Collectors.toList());

        EasyTableView.fillTable(playersTbl, spelers, this::spelerClicked);
    }
    private void spelerClicked(Entity speler){
        System.out.println("Geklikt: "+speler);
        Application.controllerShareData = speler;
        Application.setScene("dashboard.fxml");
    }
}
