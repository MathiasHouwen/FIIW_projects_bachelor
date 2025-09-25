package be.kuleuven.dbproject.controller;

import be.kuleuven.dbproject.Application;
import be.kuleuven.dbproject.model.db.GroteQueries;
import be.kuleuven.dbproject.model.entities.Entity;
import be.kuleuven.dbproject.model.entities.Toernooi;
import be.kuleuven.dbproject.model.entities.Speler;
import be.kuleuven.dbproject.view.EasyTableView;
import javafx.fxml.FXML;
import javafx.scene.control.TableView;

import java.util.List;

public class LeiderController {
    @FXML
    public TableView<Toernooi> playersTbl;

    @FXML
    void initialize() {
        Speler speler = (Speler) Application.controllerShareData;
        List<Entity> toernooien = GroteQueries.toernooienVanLeider(speler);
        EasyTableView.fillTable(playersTbl, toernooien, e -> {});
    }
}
