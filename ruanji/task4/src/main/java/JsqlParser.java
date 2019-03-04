import net.sf.jsqlparser.JSQLParserException;
import net.sf.jsqlparser.expression.Expression;
import net.sf.jsqlparser.expression.operators.relational.ExpressionList;
import net.sf.jsqlparser.parser.CCJSqlParserManager;
import net.sf.jsqlparser.parser.CCJSqlParserUtil;
import net.sf.jsqlparser.schema.Column;
import net.sf.jsqlparser.schema.Table;
import net.sf.jsqlparser.statement.Statement;
import net.sf.jsqlparser.statement.create.table.ColumnDefinition;
import net.sf.jsqlparser.statement.create.table.CreateTable;
import net.sf.jsqlparser.statement.delete.Delete;
import net.sf.jsqlparser.statement.insert.Insert;
import net.sf.jsqlparser.statement.select.PlainSelect;
import net.sf.jsqlparser.statement.select.Select;
import net.sf.jsqlparser.statement.select.SelectItem;
import net.sf.jsqlparser.statement.update.Update;
import net.sf.jsqlparser.util.TablesNamesFinder;

import java.io.StringReader;
import java.util.ArrayList;
import java.util.List;

public class JsqlParser {

    // *******createTable table
    public static String createTable_table(String sql){
        CCJSqlParserManager parserManager = new CCJSqlParserManager();
        try {
            CreateTable createTable = (CreateTable) parserManager.parse(new StringReader(sql));
            return createTable.getTable().getName();
        }catch (Exception e){
            return null;
        }

    }

    // *******createTable column
    public static List<ColumnDefinition> createTable_column(String sql){
        CCJSqlParserManager parserManager = new CCJSqlParserManager();
        try {
            CreateTable createTable = (CreateTable) parserManager.parse(new StringReader(sql));
            return createTable.getColumnDefinitions();
        }catch (Exception e){
            return null;
        }
    }

    // *******select where
    public static String select_where(String sql) {
        CCJSqlParserManager parserManager = new CCJSqlParserManager();
        Select select;
        try {
            select = (Select) parserManager.parse(new StringReader(sql));
            PlainSelect plain = (PlainSelect) select.getSelectBody();
            Expression where_expression = plain.getWhere();
            return where_expression.toString();
        } catch (Exception e) {
            return null;
        }
    }

    // **********select table
    // **********TablesNamesFinder:Find all used tables within an select
    public static List<String> select_table(String sql)
            throws JSQLParserException {
        Statement statement = (Statement) CCJSqlParserUtil.parse(sql);
        Select selectStatement = (Select) statement;
        TablesNamesFinder tablesNamesFinder = new TablesNamesFinder();
        return tablesNamesFinder
                .getTableList(selectStatement);
    }

    // *********select body items内容
    public static List<String> select_column(String sql) throws JSQLParserException {
        CCJSqlParserManager parserManager = new CCJSqlParserManager();
        Select select = (Select) parserManager.parse(new StringReader(sql));
        PlainSelect plain = (PlainSelect) select.getSelectBody();
        List<SelectItem> selectitems = plain.getSelectItems();
        List<String> str_items = new ArrayList<String>();
        if (selectitems != null) {
            for (SelectItem selectitem : selectitems) {
                str_items.add(selectitem.toString());
            }
        }
        return str_items;
    }


    // ****insert table
    public static String insert_table(String sql)
            throws JSQLParserException {
        Statement statement = CCJSqlParserUtil.parse(sql);
        Insert insertStatement = (Insert) statement;
        String string_tablename = insertStatement.getTable().getName();
        return string_tablename;
    }

    // ********* insert table column
    public static List<String> insert_column(String sql)
            throws JSQLParserException {
        Statement statement = CCJSqlParserUtil.parse(sql);
        Insert insertStatement = (Insert) statement;
        List<Column> table_column = insertStatement.getColumns();
        List<String> str_column = new ArrayList<String>();
        try {
            for (Column aTable_column : table_column) {
                str_column.add(aTable_column.toString());
            }
        } catch (Exception e) {
            return null;
        }
        return str_column;
    }

    // ********* Insert values ExpressionList
    public static List<String> insert_values(String sql)
            throws JSQLParserException {
        Statement statement = CCJSqlParserUtil.parse(sql);
        Insert insertStatement = (Insert) statement;
        List<Expression> insert_values_expression = ((ExpressionList) insertStatement
                .getItemsList()).getExpressions();
        List<String> str_values = new ArrayList<String>();
        for (int i = 0; i < insert_values_expression.size(); i++) {
            str_values.add(insert_values_expression.get(i).toString());
        }
        return str_values;
    }

    // *********delete table name
    public static String delete_table(String sql){
        CCJSqlParserManager parserManager = new CCJSqlParserManager();
        try {
            Delete delete = (Delete) parserManager.parse(new StringReader(sql));
            return delete.getTable().getName();
        }catch (Exception e){
            return null;
        }
    }

    public static String delete_where(String sql){
        CCJSqlParserManager parserManager = new CCJSqlParserManager();
        try {
            Delete delete = (Delete) parserManager.parse(new StringReader(sql));
            return delete.getWhere().toString();
        }catch (Exception e){
            return null;
        }
    }


    // *********update table name
    public static String update_table(String sql)
            throws JSQLParserException {
        Statement statement = CCJSqlParserUtil.parse(sql);
        Update updateStatement = (Update) statement;
        Table update_table = updateStatement.getTable();
//        List<String> str_table = new ArrayList<String>();
//        if (update_table != null) {
//            for (int i = 0; i < update_table.size(); i++) {
//                str_table.add(update_table.get(i).toString());
//            }
//        }
        return String.valueOf(update_table);
    }

    // *********update column
    public static List<String> update_column(String sql)
            throws JSQLParserException {
        Statement statement = CCJSqlParserUtil.parse(sql);
        Update updateStatement = (Update) statement;
        List<Column> update_column = updateStatement.getColumns();
        List<String> str_column = new ArrayList<String>();
        if (update_column != null) {
            for (int i = 0; i < update_column.size(); i++) {
                str_column.add(update_column.get(i).toString());
            }
        }
        return str_column;

    }

    // *********update values
    public static List<String> update_values(String sql)
            throws JSQLParserException {
        Statement statement = CCJSqlParserUtil.parse(sql);
        Update updateStatement = (Update) statement;
        List<Expression> update_values = updateStatement.getExpressions();
        List<String> str_values = new ArrayList<String>();
        if (update_values != null) {
            for (int i = 0; i < update_values.size(); i++) {
                str_values.add(update_values.get(i).toString());
            }
        }
        return str_values;

    }

    // *******update where
    public static String update_where(String sql)
            throws JSQLParserException {
        Statement statement = CCJSqlParserUtil.parse(sql);
        Update updateStatement = (Update) statement;
        Expression where_expression = updateStatement.getWhere();
        String str = null;
        try {
            str = where_expression.toString();
            return str;
        } catch (Exception e) {
            return null;
        }
    }

}
