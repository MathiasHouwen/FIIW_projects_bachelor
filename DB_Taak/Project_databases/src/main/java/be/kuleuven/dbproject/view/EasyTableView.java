package be.kuleuven.dbproject.view;
import be.kuleuven.dbproject.model.entities.Entity;
import javafx.beans.property.ReadOnlyObjectWrapper;
import javafx.collections.ObservableList;
import javafx.scene.control.TableColumn;
import javafx.scene.control.TableView;
import javafx.scene.input.MouseEvent;

import java.lang.reflect.Field;
import java.util.HashSet;
import java.util.List;
import java.util.Set;
import java.util.function.Consumer;

public class EasyTableView{

    /*

            AFBLIJVEN
        !!! NEGEER DE WARNIGNS VAN DE IDE!!!

        1 generic type aanpassen en CellValueFactory wil niet werken, als die wel werkt dan werkt getColumns niet
        als je de obverable lists zelf met for loops volledig cast, werkt dat lijntje code wel,
        maar zal ergens een interne javafx functie toch een class cast exception gooien.
        " no possible instance can be a capture of ? "

     */

    public static void fillTable(TableView tableView, List<Entity> entities, Consumer<Entity> onEntityClick){

        filltableExtraIgnore(tableView, entities, onEntityClick, Set.of());
    }

    public static void filltableExtraIgnore(TableView tableView, List<Entity> entities, Consumer<Entity> onEntityClick, Set<String> extraIgnore) {
        if(entities.isEmpty()) return;
        Field[] fields = entities.getFirst().getClass().getDeclaredFields();

        //tableIgnore is niet static want zelfs met T extends Entity kan de functie niet direct ge-called worden op Class<T> type
        final Set<String> ignore = entities.getFirst().tableIgnore();

        final Set<String> ignoreCopy = new HashSet<>(ignore);
        ignoreCopy.addAll(extraIgnore);

        for(Field field : fields){
            field.setAccessible(true);
            if(ignoreCopy.contains(field.getName())) continue;
            addColumn(field, tableView);
        }
        tableView.getItems().addAll(entities);
        tableView.setOnMouseClicked(e -> handleClick(e, tableView, entities, onEntityClick));
    }

    private static void handleClick(MouseEvent e, TableView tableView, List<Entity> entities, Consumer<Entity> onEntityClick) {
        if (e.getClickCount() == 2 && tableView.getSelectionModel().getSelectedItem() != null) {
            var selectedRow = tableView.getSelectionModel().getSelectedIndex();
            Entity clickedEntity = entities.get(selectedRow);
            onEntityClick.accept(clickedEntity);
        }
    }

    private static void addColumn(Field field, TableView tableView) {
        String[] subNames = field.getName().split("__");

        ObservableList<TableColumn> columns = tableView.getColumns();


        for (String name : subNames) {

            name = name.replace('_', ' ');

            TableColumn column = null;

            //als een kolom al bestaat: zoek die
            for(TableColumn col : columns){
                if(col.getText().equals(name)){
                    column = col;
                    break;
                }
            }
            //als niet bestaat voeg nieuwe kolom toe met de naam
            if(column == null){
                column = new TableColumn<>(name);
                columns.add(column);
            }

            columns = column.getColumns();

            
            column.setCellValueFactory(f -> {
                try {
                    return new ReadOnlyObjectWrapper<>(field.get(((TableColumn.CellDataFeatures)f).getValue()));
                } catch (IllegalAccessException e) {
                    throw new RuntimeException(e);
                }
            });
        }
    }
}
