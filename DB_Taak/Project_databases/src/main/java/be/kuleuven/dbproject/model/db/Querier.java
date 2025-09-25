package be.kuleuven.dbproject.model.db;

import java.sql.ResultSet;
import java.sql.ResultSetMetaData;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Querier {

    private final ConnectionManager connectionManager;
    public Querier(ConnectionManager connectionManager) {
        this.connectionManager = connectionManager;
    }
    private ResultSet query(String queryString){
        try {
            Statement s = connectionManager.getConnection().createStatement();
            return s.executeQuery(queryString);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
    private void queryZonderResult(String queryString){
        try {
            Statement s = connectionManager.getConnection().createStatement();
            s.execute(queryString);
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
    }
    public void insert(String table, Map<String, Object> dbMap){
        List<String> cols = new ArrayList<>();
        List<Object> vals = new ArrayList<>();
        for(Map.Entry<String, Object> entry: dbMap.entrySet()){
            cols.add(entry.getKey());
            vals.add(entry.getValue());
        }
        insert(table, cols, vals);
    }
    public void insert(String table, List<String> cols, List<Object> vals){
        String colsString = colsToSql(cols);
        String valsString = valsToSql(vals);
        queryZonderResult("""
                INSERT INTO %s (%s)
                VALUES (%s);
                """.formatted(table, colsString, valsString));
    }
    public void remove(String table, String idCol, long id){
        queryZonderResult("""
                DELETE FROM %s
                WHERE %s = %d;
                """.formatted(table, idCol, id));
    }

    public void removeInschrijving(String table, String idCol1, long id1, String idCol2, long id2){
        queryZonderResult("""
                DELETE FROM %s
                WHERE %s = %d
                AND %s = %d;
                """.formatted(table, idCol1, id1, idCol2, id2));
    }

    public void update(String table, List<String> cols, List<Object> vals, long id){
        String setString = setToSql(cols, vals);
        queryZonderResult("""
                UPDATE %s
                SET %s
                WHERE id = %d;
                """.formatted(table, setString, id));
    }

    /*
        QUERY SHORTCUTS
     */

    public Map<String, Object> queryToMap1Item(String queryString){
        List<Map<String, Object>> entities = queryToMapList(queryString);
        if(entities.isEmpty()) return null;
        return entities.getFirst();
    }
    public Map<String, Object> get1Equals(String table, String col, Object value){
        String valueStr = value instanceof String ? "'"+value+"'" : ""+value;
        return queryToMap1Item("SELECT * FROM "+table+" WHERE "+col+" = "+valueStr);
    }
    public List<Map<String, Object>> getEquals(String table, String col, Object value){
        String valueStr = value instanceof String ? "'"+value+"'" : ""+value;
        return queryToMapList("SELECT * FROM "+table+" WHERE "+col+" = "+valueStr);
    }
    public Map<String, Object> getByID(String table, long id){
        return queryToMap1Item("SELECT * FROM "+table+" WHERE id = "+id);
    }
    public List<Map<String, Object>> getFullTable(String table){
        return queryToMapList("SELECT * FROM "+table);
    }

    /*
        HOOFDFUNCTIE
     */

    public List<Map<String, Object>> queryToMapList(String queryString){
        ResultSet result = query(queryString);
        ArrayList<Map<String, Object>> entities = new ArrayList<>();

        while (true){
            try {
                final ResultSetMetaData meta = result.getMetaData();
                final int cols = meta.getColumnCount();
                if(result.next()){
                    final Map<String, Object> entity = new HashMap<>();
                    for (int i =1; i<=cols; i++) {
                        Object value = result.getObject(i);
                        entity.put(meta.getColumnLabel(i), value);
                    }
                    entities.add(entity);
                } else{
                    break;
                }
            } catch (SQLException e) {
                throw new RuntimeException(e);
            }
        }
        return entities;
    }

    private String colsToSql(List<String> cols){
        StringBuilder colsString = new StringBuilder();
        for(int i = 0; i < cols.size(); i++){
            colsString.append(colToStr(cols.get(i)));
            if(i < cols.size() - 1){
                colsString.append(", ");
            }
        }
        return colsString.toString();
    }
    private String valsToSql(List<Object> vals){
        StringBuilder valsString = new StringBuilder();
        for(int i = 0; i < vals.size(); i++){
            Object val = vals.get(i);
            valsString.append(objectToStr(val));
            if(i < vals.size() - 1){
                valsString.append(", ");
            }
        }
        return valsString.toString();
    }
    private String objectToStr(Object obj){
        boolean isString = obj instanceof String;
        return (isString ? "'" : "") + obj.toString() + (isString ? "'" : "");
    }
    private String colToStr(String col){
        return "`"+col+"`";
    }

    private String setToSql(List<String> cols, List<Object> vals){
        StringBuilder setString = new StringBuilder();
        for(int i = 0; i < cols.size(); i++){
            String col = cols.get(i);
            Object val = vals.get(i);
            setString.append(colToStr(col)).append(" = ");
            setString.append(objectToStr(val));
            if(i < vals.size() - 1){
                setString.append(", ");
            }
        }
        return setString.toString();
    }


}
