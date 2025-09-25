module be.kuleuven.dbproject {
    requires javafx.controls;
    requires javafx.fxml;

    requires org.controlsfx.controls;
    requires java.sql;

    opens be.kuleuven.dbproject to javafx.fxml;
    exports be.kuleuven.dbproject;
    exports be.kuleuven.dbproject.controller;
    opens be.kuleuven.dbproject.controller to javafx.fxml;
    exports be.kuleuven.dbproject.model.db;
    opens be.kuleuven.dbproject.model.db to javafx.fxml;
}