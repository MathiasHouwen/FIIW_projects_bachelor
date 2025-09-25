package be.kuleuven.dbproject.view;

import be.kuleuven.dbproject.model.entities.Entity;
import be.kuleuven.dbproject.model.entities.Speler;
import javafx.geometry.Pos;
import javafx.scene.Node;
import javafx.scene.control.Label;
import javafx.scene.layout.AnchorPane;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.scene.shape.Rectangle;

import java.util.List;
import java.util.Map;

import static be.kuleuven.dbproject.Application.querier;

public class MatchOverzichtView {

    private static double boxWidth = 60;
    private static double boxHeight = 50;
    private static double fullHeight = 80;

    public static void fillMatchesOverzicht(VBox rondesPane, VBox matchenPane, List<Entity> spelers, long[] vrijGestelden, Speler speler, Map<Integer, List<Map<String, Object>>> rondes){

        rondesPane.setSpacing(10);
        matchenPane.setSpacing(10);

        HBox vrijstellingenBox = new HBox();
        for(long speler_id : vrijGestelden){

            AnchorPane container = new AnchorPane();
            Rectangle rectangle1 = new Rectangle(boxWidth, boxHeight, Color.LIGHTYELLOW);
            Speler vrijgesteldeSpeler = getSpeler(speler_id, spelers);
            Label lbl = new Label(vrijgesteldeSpeler.getNummer()+" - "+toAfkorting(vrijgesteldeSpeler.getClub()));
            if(vrijgesteldeSpeler.getId() == speler.getId()){
                lbl.setTextFill(Color.BLUE);
            }
            container.getChildren().addAll(rectangle1, lbl);
            vrijstellingenBox.getChildren().add(container);
        }
        if(vrijGestelden.length > 0){
            Label vrijstelLbl = new Label("vrijgesteld");
            vrijstelLbl.setPrefHeight(boxHeight);
            rondesPane.getChildren().add(vrijstelLbl);
        }
        matchenPane.getChildren().add(vrijstellingenBox);

        for(int ronde=1; ronde<=rondes.size(); ronde++){
            HBox rijInOverzicht = new HBox();
            rijInOverzicht.setPrefWidth(matchenPane.getWidth());
            rijInOverzicht.setSpacing(10);
            rijInOverzicht.setAlignment(Pos.CENTER);
            for(Map<String, Object> match : rondes.get(ronde)){
                boolean linksWint = (int) match.get("score1") > (int) match.get("score2");

                VBox versusEnSchieds = new VBox();
                versusEnSchieds.setAlignment(Pos.CENTER);
                versusEnSchieds.setPrefHeight(fullHeight);

                Label scheids = new Label("");
                if(match.get("scheids") != null){
                    scheids.setText("Scheid: " + match.get("scheids"));
                }

                HBox versus = new HBox();
                versus.setStyle("-fx-border-color: black");



                AnchorPane container1 = new AnchorPane();
                AnchorPane container2 = new AnchorPane();
                Rectangle rectangle1 = new Rectangle(boxWidth, boxHeight, linksWint? Color.LIGHTGREEN : Color.LIGHTCORAL);
                Rectangle rectangle2 = new Rectangle(boxWidth, boxHeight, linksWint? Color.LIGHTCORAL : Color.LIGHTGREEN);


                VBox info1 = new VBox();
                VBox info2 = new VBox();


                info1.setPrefWidth(boxWidth);
                info2.setPrefWidth(boxWidth);
                info1.setAlignment(Pos.CENTER);
                info2.setAlignment(Pos.CENTER);


                Speler speler1 = getSpeler((Long) match.get("speler1_id"), spelers);
                Speler speler2 = getSpeler((Long) match.get("speler2_id"), spelers);

                info1.getChildren().add(new Label(" Nr: "+speler1.getNummer()));
                info1.getChildren().add(new Label(" Club: "+toAfkorting(speler1.getClub())));
                info1.getChildren().add(new Label(" score: "+match.get("score1")));
                info2.getChildren().add(new Label(" Nr: "+speler2.getNummer()));
                info2.getChildren().add(new Label(" Club: "+toAfkorting(speler2.getClub())));
                info2.getChildren().add(new Label(" score: "+match.get("score2")));

                if(speler1.getId() == speler.getId()){
                    for(Node l : info1.getChildren()){
                        ((Label)l).setTextFill(Color.BLUE);
                    }
                }
                if(speler2.getId() == speler.getId()){
                    for(Node l : info2.getChildren()){
                        ((Label)l).setTextFill(Color.BLUE);
                    }
                }

                versusEnSchieds.getChildren().addAll(versus, scheids);
                versus.getChildren().addAll(container1, container2);
                container1.getChildren().addAll(rectangle1, info1);
                container2.getChildren().addAll(rectangle2, info2);
                rijInOverzicht.getChildren().add(versusEnSchieds);
            }
            Label rondeLbl = new Label("Ronde "+(ronde));
            rondeLbl.setPrefHeight(fullHeight);
            rondesPane.getChildren().add(rondeLbl);
            matchenPane.getChildren().add(rijInOverzicht);
        }

        vrijstellingenBox.setSpacing(10);
        vrijstellingenBox.setPrefWidth(matchenPane.getWidth());
        vrijstellingenBox.setAlignment(Pos.CENTER);
    }

    private static String toAfkorting(String clubNaam){
        StringBuilder afkorting = new StringBuilder();
        for(char letter : clubNaam.toCharArray()){
            if(Character.isUpperCase(letter)) afkorting.append(letter);
        }
        return afkorting.toString();
    }


    private static Speler getSpeler(long spelerID, List<Entity> spelers){
        for(Entity spelerE : spelers){
            Speler speler = (Speler) spelerE;
            if(speler.getId() == spelerID){
                return speler;
            }
        }
        return null;
    }
}
