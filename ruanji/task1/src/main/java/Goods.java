import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class Goods {
    public int ID;
    public String name;
    public String belongingArea;
    public String sendingArea;
    public int type;
    public int clientGrade;
    public String date;
    public double priority;

    private final float typeWeight = 0.2f;
    private final float clientGradeWeight = 0.3f;
    private final float dateWeight = 0.4f;
    private static long todayTimestamp = new Date().getTime();
    private static long oneDayTimestamp = 24 * 60 * 60 * 1000;
    public Goods(int ID, String name, String belongingArea, String sendingArea, int type, int clientGrade, String date) {
        this.ID = ID;
        this.name = name;
        this.belongingArea = belongingArea;
        this.sendingArea = sendingArea;
        this.type = type;
        this.clientGrade = clientGrade;
        this.date = date;
        this.priority = weight(type, clientGrade, date);
    }

    public double getPriority(){
        return priority;
    }

    private double weight(int type, int clientGrade, String dateString) {
        double date = Math.ceil((todayTimestamp - SimpleDateFormat(dateString)) / oneDayTimestamp);
        return type * typeWeight + clientGrade * clientGradeWeight + date * dateWeight;
    }

    private long SimpleDateFormat(String strDate) {
        //注意：SimpleDateFormat构造函数的样式与strDate的样式必须相符
        SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd");
//        SimpleDateFormat sDateFormat=new SimpleDateFormat("yyyy-MM-dd HH:mm:ss"); //加上时间
        //必须捕获异常
        try {
            Date date = simpleDateFormat.parse(strDate);
            return date.getTime();
        } catch (ParseException px) {
            px.printStackTrace();
        }

        return 0;
    }

    @Override
    public String toString() {
        return "Goods{" +
                "ID=" + ID +
                ", name='" + name + '\'' +
                ", belongingArea='" + belongingArea + '\'' +
                ", sendingArea='" + sendingArea + '\'' +
                ", type=" + type +
                ", clientGrade=" + clientGrade +
                ", date='" + date + '\'' +
                ", priority=" + Utils.format(priority) +
                '}';
    }
}
