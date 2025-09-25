package be.kuleuven.dbproject;

import be.kuleuven.dbproject.model.db.ConnectionManager;
import be.kuleuven.dbproject.model.db.Querier;
import be.kuleuven.dbproject.model.entities.Entity;
import be.kuleuven.dbproject.model.entities.Reeks;
import be.kuleuven.dbproject.model.entities.Speler;
import javafx.fxml.FXMLLoader;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Parent;
import javafx.scene.Scene;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;

import java.io.BufferedInputStream;
import java.io.IOException;
import java.util.List;
import java.util.stream.Collectors;

public class Application extends javafx.application.Application {
    private static Stage stage;
    private static final int width = 1024;
    private static final int height = 740;

    private static ConnectionManager connectionManager;
    public static Querier querier;
    public static Object controllerShareData;


    public static void setScene(String fxmlfile){
        FXMLLoader fxmlLoader = new FXMLLoader(Application.class.getResource(fxmlfile));
        Parent root;
        try {
            root = fxmlLoader.load();
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
        VBox echteRoot = new VBox();
        echteRoot.setAlignment(Pos.CENTER);
        Button startBtn = new Button("Ga naar start scherm");
        startBtn.setDisable(fxmlfile.equals("start-menu.fxml"));
        startBtn.setOnAction(e -> setScene("start-menu.fxml"));
        echteRoot.getChildren().addAll(new Label(""), startBtn, root);
        Scene scene = new Scene(echteRoot, width, height);
        stage.setWidth(width);
        stage.setHeight(height);
        stage.setScene(scene);
    }

    @Override
    public void start(Stage stage) throws IOException {
        connectionManager = new ConnectionManager();
        querier = new Querier(connectionManager);
        Application.stage = stage;
        setScene("start-menu.fxml");
        stage.setTitle("Hello!");
        stage.show();
    }

    public static void main(String[] args) {
        launch();
    }
}