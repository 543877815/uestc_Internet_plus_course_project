package cn.uestc.preprocessing;

import weka.attributeSelection.ASEvaluation;
import weka.attributeSelection.InfoGainAttributeEval;
import weka.attributeSelection.Ranker;
import weka.attributeSelection.ReliefFAttributeEval;
import weka.core.Instance;
import weka.core.Instances;
import weka.core.converters.ConverterUtils.DataSink;
import weka.core.converters.ConverterUtils.DataSource;
import weka.filters.Filter;
import weka.filters.supervised.attribute.AttributeSelection;

public class FeatureSelection {
    public static void main(String[] args) throws Exception {
        System.out.println("+++++++++++Example 2: Feature Selection via weka.++++++++++");

        System.out.println("Step 1. 读取数据...");
        String fn = "E://Weka-3-8/data/iris.arff";
        DataSource source = new DataSource(fn);
        Instances instances = source.getDataSet();

        System.out.println("Step 2. 特征筛选...");

        //select features from data
        int k = 2;
        AttributeSelection as = new AttributeSelection();//特征筛选类
        Ranker rank = new Ranker();
        rank.setThreshold(0.0);//参数设置，筛选大于某阈值的特征
        rank.setNumToSelect(k);//Number of features want to select

        ASEvaluation ae = new InfoGainAttributeEval();//change here: different feature selection
//        ASEvaluation ae = new ReliefFAttributeEval();
        as.setEvaluator(ae);
        as.setSearch(rank);
        as.setInputFormat(instances);
        Instances reductData = Filter.useFilter(instances, as);

        System.out.println("Step 3. 保存规约后的数据到新文件");
        DataSink.write(fn.substring(0, fn.length()-5)+"_reducted.arff", reductData);
        System.out.println("Finish.");
    }
}
