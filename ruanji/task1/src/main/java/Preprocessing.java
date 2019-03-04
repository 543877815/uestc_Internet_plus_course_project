
import org.apache.commons.io.FileUtils;
import org.apache.poi.hssf.usermodel.HSSFCell;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.ss.usermodel.CellType;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class Preprocessing {
    public static void main(String[] args) {
        // 需要解析的excel文件
        File file = new File("src/main/resources/input.xls");
        try {
            // 创建excel，读取文件
            HSSFWorkbook workbook = new HSSFWorkbook(FileUtils.openInputStream(file));

            // 获取第一个工作表workbook.getSheet("Sheet0")
//            HSSFSheet sheet = workbook.getSheet("Sheet0");
            // 读取默认第一个工作表sheet
            HSSFSheet sheet = workbook.getSheetAt(0);

            // 创建excel，用于存储数据
            HSSFWorkbook workbook2 = new HSSFWorkbook();
            // 创建一个工作表sheet
            HSSFSheet sheet2 = workbook2.createSheet();

            int lastRowNum = sheet.getLastRowNum();
            boolean trigger = true;
            for (int i = 0; i <= lastRowNum; i++) {
                HSSFRow row = sheet.getRow(i);
                // 获取当前行最后单元格列号
                int lastCellNum = row.getLastCellNum();

                // 所属地
                String belonging = null;
                HSSFRow row2 = sheet2.createRow(i);
                for (int j = 0; j < lastCellNum; j++) {
                    HSSFCell cell = row.getCell(j);
                    // 转化为String类型
                    cell.setCellType(CellType.STRING);
                    String value = cell.getStringCellValue();
                    if (j == 2) {
                        belonging = value;
                    } else if (j == 3 && belonging == value) {
                        if (trigger == true) {
                            value = "H";
                        } else {
                            belonging = "H";
                        }
                        HSSFCell cell2 = row2.createCell(j - 1);
                        cell2.setCellValue(belonging);
                        trigger = !trigger;
                    }

                    // 创建处理过后的excel
                    HSSFCell cell2 = row2.createCell(j);
                    cell2.setCellValue(value);

                    System.out.print(value + " ");
                }
                System.out.println();
            }

            File file2 = new File("src/main/resources/goodsInfo.xls");
            try {
                System.out.println("save");
                file2.createNewFile();
                // 将excel存盘
                FileOutputStream stream = FileUtils.openOutputStream(file2);
                workbook2.write(stream);
                stream.close();
            } catch (IOException e) {
                e.printStackTrace();
            }

        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
