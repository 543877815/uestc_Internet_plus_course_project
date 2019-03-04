import net.sf.jsqlparser.parser.CCJSqlParserManager;
import net.sf.jsqlparser.parser.CCJSqlParserUtil;
import net.sf.jsqlparser.schema.Column;
import net.sf.jsqlparser.statement.Statement;
import net.sf.jsqlparser.statement.create.table.ColumnDefinition;
import net.sf.jsqlparser.statement.create.table.CreateTable;
import net.sf.jsqlparser.statement.delete.Delete;
import net.sf.jsqlparser.statement.insert.Insert;
import net.sf.jsqlparser.statement.select.Select;
import net.sf.jsqlparser.statement.update.Update;
import org.apache.commons.io.FileUtils;
import org.apache.poi.hssf.usermodel.HSSFCell;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.ss.usermodel.Sheet;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.StringReader;
import java.nio.channels.FileChannel;
import java.nio.channels.FileLock;
import java.util.*;


public class Main3 {
    private static HSSFWorkbook workbook;
    private static File file = new File("src/main/resources/data.xls");
    private static FileOutputStream outStream = null;
    private static FileLock lock = null;

    public static void main(String[] args) {
        System.out.println("welcome!");
        while (true) {
            Scanner input = new Scanner(System.in);
            String sql = input.nextLine();
//            String sql1 = input.nextLine();
//            String sql = "select id, name, origin from goodsList where id > 5 and name <= b and origin >= D";
//            String sql = "INSERT INTO goodsList VALUES ('Gates', 'Bill', 'Xuanwumen 10', 'Beijing', '33', '33')";
//            String sql = "INSERT INTO goodsList (type, name) VALUES (type, name)";
//            String sql = "UPDATE goodsList SET origin = 1111, type = 1111 WHERE id = 5";
//            String sql = "DELETE FROM goodsList WHERE id = 5 and type = 112211";
//            String sql = "CREATE TABLE Persons\n" +
//                    "(\n" +
//                    "Id_P int,\n" +
//                    "LastName varchar(255),\n" +
//                    "FirstName varchar(255),\n" +
//                    "Address varchar(255),\n" +
//                    "City varchar(255)\n" +
//                    ")";
            if (sql.equals("exit")) {
                System.out.println("see you!");
                return;
            }
            try {
                Statement statement = CCJSqlParserUtil.parse(sql);

                if (statement instanceof Select) {
                    List<String> table = JsqlParser.select_table(sql);
                    List<String> column = JsqlParser.select_column(sql);
                    String where = JsqlParser.select_where(sql);
//                    System.out.println(table);
//                    System.out.println(column);
//                    System.out.println(where);
                    int sheetIndex = getSheetIndex(table.get(0));
                    if (sheetIndex == -1) {
                        System.out.println("table not exits");
                        continue;
                    }
                    if (where != null) {
                        String[] filter_and = where.split("AND");
                        String[][] filters = new String[filter_and.length][3];
                        filterAnd(filter_and, filters);
                        if (column.indexOf("*") != -1) {
                            QueryAll(sheetIndex, filters);
                        } else {
                            QuerySpecifiedColumn(sheetIndex, column, filters);
                        }
                    } else {
                        if (column.indexOf("*") != -1) {
                            QueryAll(sheetIndex);
                        } else {
                            QuerySpecifiedColumn(sheetIndex, column);
                        }
                    }
                }

                if (statement instanceof Insert) {
                    String table = JsqlParser.insert_table(sql);
                    List columns = JsqlParser.insert_column(sql);
                    List values = JsqlParser.insert_values(sql);
                    int sheetIndex = getSheetIndex(table);
                    if (sheetIndex == -1) {
                        System.out.println("table not exits");
                        continue;
                    }
                    HSSFSheet sheet = workbook.getSheetAt(sheetIndex);
                    HSSFRow titleRow = sheet.getRow(0);
                    int titleNumber = titleRow.getLastCellNum();
                    if (columns == null && values.size() != titleNumber - 2) {
                        System.out.println("input error!");
                        continue;
                    }

                    if ((columns != null) && (columns.size() != values.size() || columns.size() > titleNumber - 2)) {
                        System.out.println("input error!");
                        continue;
                    }

                    dataAdd(sheetIndex, columns, values);
//                    System.out.println(table);
//                    System.out.println(columns);
//                    System.out.println(values);
                }

                if (statement instanceof Delete) {
                    String table = JsqlParser.delete_table(sql);
                    String where = JsqlParser.delete_where(sql);

                    int sheetIndex = getSheetIndex(table);
                    String[] filter_and = where.split("AND");
                    String[][] filters = new String[filter_and.length][3];
                    filterAnd(filter_and, filters);

//                    System.out.println(table);
//                    System.out.println(where);

                    dataDelete(sheetIndex, filters);
                }

                if (statement instanceof Update) {
                    String table = JsqlParser.update_table(sql);
                    List columns = JsqlParser.update_column(sql);
                    List values = JsqlParser.update_values(sql);
                    String where = JsqlParser.update_where(sql);
                    if (where == null) {
                        System.out.println("input error!");
                        continue;
                    }
                    int sheetIndex = getSheetIndex(table);
                    String[] filter_and = where.split("AND");
                    String[][] filters = new String[filter_and.length][3];
                    filterAnd(filter_and, filters);
//
//                    System.out.println(table);
//                    System.out.println(columns);
//                    System.out.println(values);
//                    System.out.println(where);
                    dataModify(sheetIndex, columns, values, filters);
                }

                if (statement instanceof CreateTable) {
                    String table = JsqlParser.createTable_table(sql);
                    List<ColumnDefinition> column = JsqlParser.createTable_column(sql);

                    createSheet(table, column);
//                    System.out.println(column);
//                    System.out.println(table);
                }
            } catch (Exception e) {
                e.printStackTrace();
                System.out.println("input error!");
            }
            System.out.println();
        }
    }

    private static void filterAnd(String[] filter_and, String[][] filters) {
        for (int i = 0; i < filter_and.length; i++) {
            if (!relation_filter(filter_and[i]).equals("0")) {
                String[] condition = filter_and[i].split(relation_filter(filter_and[i]));
                filters[i][0] = condition[0].trim();
                filters[i][1] = relation_filter(filter_and[i]);
                filters[i][2] = condition[1].trim();
            }
        }
    }


    private static boolean readDataFromFile() {
        try {
            workbook = new HSSFWorkbook(FileUtils.openInputStream(file));
        } catch (IOException e) {
            System.out.print(".");
            try {
                Thread.sleep(100);
            } catch (InterruptedException e1) {
                e1.printStackTrace();
            }
            return false;
        }
        return true;
    }

    private static int getSheetIndex(String table) {
        readDataFromFile();
        int sheetNumbers = workbook.getNumberOfSheets();
        for (int i = 0; i < sheetNumbers; i++) {
            String sheetName = workbook.getSheetAt(i).getSheetName();
            if (sheetName.equals(table)) {
                return i;
            }
        }
        return -1;
    }

    private static void createSheet(String sheetName, List<ColumnDefinition> columnName) {
        while (true) {
            boolean readFileSuccess = readDataFromFile();
            if (!readFileSuccess) continue;
            HSSFSheet sheet = workbook.getSheet(sheetName);
            if (sheet == null) {
                HSSFSheet newSheet = workbook.createSheet(sheetName);
                HSSFRow titleRow = newSheet.createRow(0);
                for (int i = 0; i < columnName.size(); i++) {
                    HSSFCell titleCell = titleRow.createCell(i);
                    titleCell.setCellValue(columnName.get(i).toString().trim().split(" ")[0]);
                }
            } else {
                System.out.println("sheet already exists! ");
                return;
            }
            saveFile();
            System.out.println();
            System.out.println("修改成功！");
            return;
        }
    }

    private static void dataAdd(int sheetIndex, List<String> column, List<String> values) {
        while (true) {
            readDataFromFile();
            boolean readFileSuccess = readDataFromFile();
            if (!readFileSuccess) continue;
            HSSFSheet sheet = workbook.getSheetAt(sheetIndex);
            HSSFRow titleRow = sheet.getRow(0);
            int lastCellNum = titleRow.getLastCellNum();
            int lastRowNum = sheet.getLastRowNum();
            HSSFRow nextRow = sheet.createRow(lastRowNum + 1);
            for (int i = 0; i < lastCellNum; i++) {
                HSSFCell addCell = nextRow.createCell(i);
                addCell.setCellValue("/");
                if (i == 0) {
                    addCell.setCellValue(String.valueOf(lastRowNum + 1));
                } else if (i == lastCellNum - 1) {
                    addCell.setCellValue("1");
                } else {
                    if (column == null) {
                        addCell.setCellValue(values.get(i - 1));
                    } else {
                        for (String aColumn1 : column) {
                            boolean flag = false;
                            for (int k = 0; k < lastCellNum; k++) {
                                if (aColumn1.equals(titleRow.getCell(k).getStringCellValue())) {
                                    flag = true;
                                }
                            }
                            if (!flag) {
                                System.out.println("input error!");
                                return;
                            }
                        }
                        for (int k = 0; k < column.size(); k++) {

                            if (column.get(k).equals(titleRow.getCell(i).getStringCellValue())) {
                                addCell.setCellValue(values.get(k));
                            }
                        }
                    }
                }
            }
            saveFile();
            System.out.println();
            System.out.println("添加成功！");
            return;
        }
    }

    private static void dataDelete(int sheetIndex, String[][] filters) {
        while (true) {
            boolean readFileSuccess = readDataFromFile();
            if (!readFileSuccess) continue;
            int[] conditionIndex = new int[filters.length];
            HSSFSheet sheet = workbook.getSheetAt(sheetIndex);
            HSSFRow titleRow = sheet.getRow(0);
            int titleNumber = titleRow.getLastCellNum();
            if (checkCondition(filters, titleRow, titleNumber, conditionIndex)) return;
            int lastRowNum = sheet.getLastRowNum();
            for (int i = 0; i < lastRowNum; i++) {
                HSSFRow row = sheet.getRow(i);
                int lastCellNum = row.getLastCellNum();
                HSSFCell flagCell = row.getCell(lastCellNum - 1);
                String flag = flagCell.getStringCellValue();
                if (flag.equals("0")) continue;

                for (int j = 0; j < lastCellNum - 1; j++) {
                    HSSFCell cell = row.getCell(j);
                    String value = cell.getStringCellValue();
                    boolean[] target = new boolean[filters.length];
                    for (int k = 0; k < filters.length; k++) {
                        if (conditionIndex[k] == j) {
                            if (checkIsFilter(filters[k][2], filters[k][1], value)) {
                                target[k] = true;
                            }
                        }
                    }
                    for (int k = 0; k < target.length; k++) {
                        if (!target[k]) continue;
                        if (k == target.length - 1) {
                            HSSFCell deleteCell = row.getCell(lastCellNum - 1);
                            deleteCell.setCellValue("0");
                        }
                    }

                }

            }
            saveFile();
            System.out.println();
            System.out.println("操作成功！");
            return;
        }
    }

    private static void dataModify(int sheetIndex, List<String> columns, List<String> values, String[][] filters) {
        while (true) {
            boolean readFileSuccess = readDataFromFile();
            if (!readFileSuccess) continue;
            HSSFSheet sheet = workbook.getSheetAt(sheetIndex);
            HSSFRow titleRow = sheet.getRow(0);
            int titleNumber = titleRow.getLastCellNum();
            for (String column : columns) {
                boolean flag = false;
                for (int j = 1; j < titleNumber; j++) {
                    if (column.trim().equals(titleRow.getCell(j).getStringCellValue())) {
                        flag = true;
                    }
                }
                if (!flag) {
                    System.out.println("input error! column not found");
                    return;
                }
            }
            int lastRowNum = sheet.getLastRowNum();
            int[] conditionIndex = new int[filters.length];
            if (checkCondition(filters, titleRow, titleNumber, conditionIndex)) return;
            QuerySpecifiedColumn(sheetIndex, columns, filters);
            System.out.println("--------------------------------");
            int[] changeIndex = new int[columns.size()];
            for (int i = 0; i < columns.size(); i++) {
                for (int j = 0; j < titleNumber; j++) {
                    HSSFCell cell = titleRow.getCell(j);
                    String titleName = cell.getStringCellValue();
                    if (columns.get(i).equals(titleName)) {
                        changeIndex[i] = j;
                    }
                }
            }

            sheet = workbook.getSheetAt(sheetIndex);
            for (int i = 0; i < lastRowNum; i++) {
                HSSFRow row = sheet.getRow(i);
                int lastCellNum = row.getLastCellNum();
                HSSFCell flagCell = row.getCell(lastCellNum - 1);
                String flag = flagCell.getStringCellValue();
                if (flag.equals("0")) continue;
                for (int j = 0; j < lastCellNum - 1; j++) {
                    HSSFCell cell = row.getCell(j);
                    String value = cell.getStringCellValue();
                    for (int k = 0; k < filters.length; k++) {
                        if (conditionIndex[k] == j) {
                            if (checkIsFilter(filters[k][2], filters[k][1], value)) {
                                for (int n = 0; n < changeIndex.length; n++) {
                                    HSSFCell modifyCell = row.getCell(changeIndex[n]);
                                    modifyCell.setCellValue(values.get(n));
                                    System.out.print(values.get(n) + " ");
                                }
                            }
                        }
                    }
                }
            }
            saveFile();
            System.out.println();
            System.out.println("修改成功！");
            return;
        }
    }

    private static void QueryAll(int sheetIndex) {
        while (true) {
            boolean readFileSuccess = readDataFromFile();
            if (!readFileSuccess) continue;
            HSSFSheet sheet = workbook.getSheetAt(sheetIndex);
            int lastRowNum = sheet.getLastRowNum();
            for (int i = 0; i <= lastRowNum; i++) {
                HSSFRow row = sheet.getRow(i);
                int lastCellNum = row.getLastCellNum();

                HSSFCell flagCell = row.getCell(lastCellNum - 1);
                String flag = flagCell.getStringCellValue();
                if (flag.equals("0")) continue;

                for (int j = 0; j < lastCellNum - 1; j++) {
                    HSSFCell cell = row.getCell(j);
                    String value = cell.getStringCellValue();
                    System.out.print(value + " ");
                }
                System.out.println();
            }
            break;
        }
    }

    private static void QueryAll(int sheetIndex, String filters[][]) {
        while (true) {
            boolean readFileSuccess = readDataFromFile();
            if (!readFileSuccess) continue;
            HSSFSheet sheet = workbook.getSheetAt(sheetIndex);
            int lastRowNum = sheet.getLastRowNum();
            HSSFRow titleRow = sheet.getRow(0);
            int titleNumber = titleRow.getLastCellNum();
            int[] conditionIndex = new int[filters.length];

            if (checkCondition(filters, titleRow, titleNumber, conditionIndex)) return;

            for (int i = 0; i <= lastRowNum; i++) {
                HSSFRow row = sheet.getRow(i);
                int lastCellNum = row.getLastCellNum();
                HSSFCell flagCell = row.getCell(lastCellNum - 1);
                String flag = flagCell.getStringCellValue();
                if (flag.equals("0")) continue;

                boolean print = checkPrint(filters, conditionIndex, i, row, lastCellNum);

                if (!print) continue;
                for (int j = 0; j < lastCellNum - 1; j++) {
                    HSSFCell cell = row.getCell(j);
                    String value = cell.getStringCellValue();
                    System.out.print(value + " ");
                    if (j == lastCellNum - 2) System.out.println();
                }
            }
            break;
        }
    }

    private static boolean checkPrint(String[][] filters, int[] conditionIndex, int i, HSSFRow row, int lastCellNum) {
        boolean print = true;
        if (i > 0) {
            for (int j = 0; j < lastCellNum - 1; j++) {
                for (int k = 0; k < filters.length; k++) {
                    HSSFCell cell = row.getCell(j);
                    String value = cell.getStringCellValue();
                    if (conditionIndex[k] == j) {
                        if (!checkIsFilter(filters[k][2], filters[k][1], value)) {
                            print = false;
                            break;
                        }
                    }
                }
            }
        }
        return print;
    }


    private static void QuerySpecifiedColumn(int sheetIndex, List<String> columns, String filters[][]) {
        while (true) {
            boolean readFileSuccess = readDataFromFile();
            if (!readFileSuccess) continue;
            int[] columnIndex = new int[columns.size()];
            HSSFSheet sheet = workbook.getSheetAt(sheetIndex);
            HSSFRow titleRow = sheet.getRow(0);
            int lastCellNum = titleRow.getLastCellNum();
            filterColumn(columns, columnIndex, titleRow, lastCellNum);
            if (!checkIsRepeat(columnIndex)) {
                System.out.println("input error！");
                break;
            }

            int[] conditionIndex = new int[filters.length];
            int titleNumber = titleRow.getLastCellNum();
            if (checkCondition(filters, titleRow, titleNumber, conditionIndex)) return;

            int lastRowNum = sheet.getLastRowNum();

            for (int i = 0; i < lastRowNum; i++) {
                HSSFRow row = sheet.getRow(i);
                HSSFCell flagCell = row.getCell(lastCellNum - 1);
                String flag = flagCell.getStringCellValue();
                if (flag.equals("0")) continue;

                boolean print = checkPrint(filters, conditionIndex, i, row, lastCellNum);

                if (!print) continue;
                printColumn(columnIndex, lastCellNum, row);
                System.out.println();
            }
            return;
        }
    }

    private static void printColumn(int[] columnIndex, int lastCellNum, HSSFRow row) {
        for (int j = 0; j < lastCellNum; j++) {
            for (int aColumnIndex : columnIndex) {
                if (j == aColumnIndex) {
                    HSSFCell cell = row.getCell(j);
                    String value = cell.getStringCellValue();
                    System.out.print(value + " ");
                }
            }
        }
    }

    private static void filterColumn(List<String> column, int[] columnIndex, HSSFRow titleRow, int lastCellNum) {
        for (int i = 0; i < lastCellNum; i++)
            for (int k = 0; k < column.size(); k++) {
                String newColumn = column.get(k).trim();
                HSSFCell titleCell = titleRow.getCell(i);
                String title = titleCell.getStringCellValue();
                if (newColumn.equals(title)) {
                    columnIndex[k] = i;
                }
            }
    }

    private static boolean checkCondition(String[][] filters, HSSFRow titleRow, int titleNumber,
                                          int[] conditionIndex) {
        for (int i = 0; i < filters.length; i++) {
            boolean flag = false;
            for (int j = 0; j < titleNumber; j++) {
                HSSFCell cell = titleRow.getCell(j);
                String titleName = cell.getStringCellValue();
                if (filters[i][0].equals(titleName)) {
                    conditionIndex[i] = j;
                    flag = true;
                }
            }
            if (!flag) {
                System.out.println("input error!");
                return true;
            }
        }
        return false;
    }


    private static void QuerySpecifiedColumn(int sheetIndex, List<String> column) {
        while (true) {
            boolean readFileSuccess = readDataFromFile();
            if (!readFileSuccess) continue;
            int[] columnIndex = new int[column.size()];

            HSSFSheet sheet = workbook.getSheetAt(sheetIndex);
            HSSFRow titleRow = sheet.getRow(0);
            int lastCellNum = titleRow.getLastCellNum();
            filterColumn(column, columnIndex, titleRow, lastCellNum);

            if (!checkIsRepeat(columnIndex)) {
                System.out.println("input error！");
                break;
            }

            int lastRowNum = sheet.getLastRowNum();
            for (int i = 0; i < lastRowNum; i++) {
                HSSFRow row = sheet.getRow(i);
                HSSFCell flagCell = row.getCell(lastCellNum - 1);
                String flag = flagCell.getStringCellValue();
                if (flag.equals("0")) continue;
                printColumn(columnIndex, lastCellNum, row);
                System.out.println();
            }
            return;
        }
    }


    private static boolean checkIsFilter(String filterValue, String relation, String compareValue) {
        if (relation.equals(">=")) {
            return filterValue.compareTo(compareValue) <= 0;
        }
        if (relation.equals("<=")) {
            return filterValue.compareTo(compareValue) >= 0;
        }
        if (relation.equals(">")) {
            return filterValue.compareTo(compareValue) < 0;
        }
        if (relation.equals("<")) {
            return filterValue.compareTo(compareValue) > 0;
        }
        if (relation.equals("=")) {
            return filterValue.equals(compareValue);
        }
        return false;
    }

    private static boolean checkIsRepeat(int[] array) {
        HashSet<Integer> hashSet = new HashSet<Integer>();
        for (int anArray : array) {
            hashSet.add(anArray);
        }
        return hashSet.size() == array.length;
    }

    private static String relation_filter(String filter) {
        if (filter.contains("<=")) {
            return "<=";
        }
        if (filter.contains(">=")) {
            return ">=";
        }
        if (filter.contains("<")) {
            return "<";
        }
        if (filter.contains(">")) {
            return ">";
        }
        if (filter.contains("=")) {
            return "=";
        }
        return "0";
    }

    private static void saveFile() {
        try {
            file.createNewFile();
            outStream = FileUtils.openOutputStream(file);   // 将excel存盘
            FileChannel channel = outStream.getChannel();
            try {
                //方法一
                lock = channel.lock();
                workbook.write(outStream);
//                Thread.sleep(10000); //for test
                //方法二
                //lock = channel.tryLock();
                //if(lock != null){
                //  do something..
                //}
            } catch (IOException e) {
                e.printStackTrace();
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (null != lock) {
                try {
                    lock.release();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
            if (outStream != null) {
                try {
                    outStream.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}
