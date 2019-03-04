package cn.uestc.preprocessing;//package cn.uestc.preprocessing;

import weka.core.Attribute;
import weka.core.Instance;
import weka.core.Instances;
import weka.core.converters.ConverterUtils;
import weka.core.converters.ConverterUtils.DataSource;
import weka.filters.Filter;
import weka.filters.unsupervised.attribute.Normalize;

public class TestNormalize {
    public static void main(String[] args) throws Exception {
        System.out.println("+++++++++++++++Example 1: Normalize Data via weka.++++++++++++++++");

        //读取数据
        System.out.println("Step 1. 读取数据");
        DataSource source = new DataSource("E://Weka-3-8/data/iris.arff");
        Instances instances = source.getDataSet();

        //归一化
        System.out.println("Step 2. 归一化...");
        Normalize norm = new Normalize();
        norm.setInputFormat(instances);
        Instances newInstances = Filter.useFilter(instances, norm);

        System.out.println("Step 3. 归一化之后的数据（打印）...");

        System.out.println("-------------------------------------");

        try {
            //打印属性名
            int numOfAtrributes = newInstances.numAttributes();
            for (int i = 0; i < numOfAtrributes; ++i) {
                Attribute attribute = newInstances.attribute(i);
            }
            int numOfInstance = newInstances.numInstances();
            for (int j = 0; j < numOfInstance; j++) {
                Instance instance = newInstances.instance(j);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }

        System.out.println("Step 4. 保存归一化后的数据到新文件...");
        System.out.println("--------------------------------------");
        ConverterUtils.DataSink.write("E://Weka-3-8/data/iris_norm.arff", newInstances);
        System.out.println("Congratulations");
    }
}
