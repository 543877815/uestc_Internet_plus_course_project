package cn.uestc.preprocessing;

import weka.core.Instances;
import weka.core.converters.ConverterUtils.DataSink;
import weka.core.converters.ConverterUtils.DataSource;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class Apriori_finish {
    private static final int minSupport = 2;                //最小支持度
    private static final double minMetric = 0.1;            //最小置信度
    static List<List<String>> record = new ArrayList<List<String>>();   //数据集

    public static void main(String[] args) throws Exception {
        System.out.println("++++++++++++++Example Apriori_finish+++++++++++++");

        System.out.println("Step 1. 读取数据...........");
        String fn = "E://Weka-3-8/data/Apriori_finish.arff";
        DataSource source = new DataSource(fn);
        Instances instances = source.getDataSet();
        System.out.print(instances.instance(8));
        System.out.println();
        final int numOfAttributes = instances.numAttributes();
        final int numOfInstances = instances.numInstances();

        //打印读取的数据集
        for (int i = 0; i < numOfInstances; i++) {
            System.out.print("T" + (i + 1) + "00 ");
            for (int j = 0; j < numOfAttributes; j++) {
                if (instances.instance(i).value(j) == 1.0) {
                    System.out.print("I" + (j + 1));
                    if((j+1) != numOfAttributes){
                        System.out.print(",");
                    }
                }
            }
            System.out.println();
        }

        //第一次扫描


    }
}
