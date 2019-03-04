package cn.uestc.preprocessing;

import weka.core.Instances;
import weka.core.converters.ConverterUtils.DataSink;
import weka.core.converters.ConverterUtils.DataSource;

public class ReplaceMissingData {
    public static void main(String[] args) throws Exception {
        System.out.println("++++++++++++++Example 2: Missing Value Handing. +++++++++++++");

        System.out.println("Step 1. 读取数据...........");
        String fn = "E://Weka-3-8/data/labor.arff";
        DataSource source = new DataSource(fn);
        Instances instances = source.getDataSet();

        System.out.println("Step 2.缺失值处理...");
        int numOfAttributes = instances.numAttributes();
        int numOfInstances = instances.numInstances();

        //计算全局平均数
        double[] meanV = new double[numOfInstances];
        for (int i = 0; i < numOfAttributes; i++) {
            meanV[i] = 0;
            int count = 0;
            for (int j = 0; j < numOfInstances; j++) {
                if (!instances.instance(j).isMissing(i)) {
                    meanV[i] += instances.instance(j).value(i);
                    count++;
                }
            }
            meanV[i] = meanV[i] / count;
        }
        for (int i = 0; i < numOfAttributes; i++) {
            for (int j = 0; j < numOfInstances; j++) {
                if (instances.instance(j).isMissing(i)) {
                    instances.instance(j).setValue(i, meanV[i]);
                }
            }
        }
        System.out.println("Step 3. 保存数据到新文件...");
        DataSink.write(fn.substring(0, fn.length() - 5) + "_handle.arff", instances);
        System.out.println("Finish.");
    }
}
