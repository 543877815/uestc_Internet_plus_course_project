import org.junit.Test;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class DateTest {

    @Test
    public void testSimpleDateFormat() {
        //注意：SimpleDateFormat构造函数的样式与strDate的样式必须相符
        SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd");
//        SimpleDateFormat sDateFormat=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss"); //加上时间
        //必须捕获异常
        try {
            String strDate = "2005-4-2";
            Date date = simpleDateFormat.parse(strDate);
            System.out.println(date);
            System.out.println(date.getTime());
        } catch (ParseException px) {
            px.printStackTrace();
        }
    }
}
