package be.kuleuven.dbproject.controller;

import be.kuleuven.dbproject.Application;
import be.kuleuven.dbproject.model.db.GroteQueries;
import be.kuleuven.dbproject.model.entities.*;
import be.kuleuven.dbproject.model.entities.Speler;
import be.kuleuven.dbproject.view.EasyTableView;
import javafx.fxml.FXML;
import javafx.scene.control.TableView;

import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

import static be.kuleuven.dbproject.Application.querier;


public class ScheidsController {

    @FXML
    public TableView matchTbl;

    @FXML
    void initialize() {
        Speler speler = (Speler) Application.controllerShareData;
        List<Entity> matchen = GroteQueries.matchenVanScheids(speler);
        System.out.println(matchen);
        EasyTableView.fillTable(matchTbl, matchen, e -> {});
    }
}
