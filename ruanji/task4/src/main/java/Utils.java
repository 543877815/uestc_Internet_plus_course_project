
import java.lang.reflect.Method;
import java.text.DecimalFormat;
import java.util.ArrayList;

public class Utils {

    private static DecimalFormat df = new DecimalFormat("#.00");

    public static void bubbleSort(int[] arr) {
        for (int i = 0; i < arr.length - 1; i++) {
            for (int j = 0; j < arr.length - i - 1; j++) {//-1为了防止溢出
                if (arr[j] > arr[j + 1]) {
                    int temp = arr[j];

                    arr[j] = arr[j + 1];

                    arr[j + 1] = temp;
                }
            }
        }
    }

    public static Object getFieldValueByName(String fieldName, Object o) {
        try {
            String firstLetter = fieldName.substring(0, 1).toUpperCase();
            String getter = "get" + firstLetter + fieldName.substring(1);
            Method method = o.getClass().getMethod(getter, new Class[] {});
            Object value = method.invoke(o, new Object[] {});
            return value;
        } catch (Exception e) {
            return null;
        }
    }

    public static ArrayList bubbleSort(ArrayList<Goods> goodsList, String belongRegion) {
        Goods[] newGoodsList = (Goods[])goodsList.toArray();
        for (int i = 0; i < newGoodsList.length; i++) {
            for (int j = 0; j < newGoodsList.length - i - 1; j++) {
                if(newGoodsList[j].priority > newGoodsList[j+1].priority){

                }
            }
        }
        ArrayList GoodsListSort = new ArrayList();
        return GoodsListSort;
    }


    public static String format(double value) {
        return df.format(value);
    }
}
