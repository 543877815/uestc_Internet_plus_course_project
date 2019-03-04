package cn.uestc.preprocessing;

import weka.core.Instances;
import weka.core.converters.ConverterUtils.DataSink;
import weka.core.converters.ConverterUtils.DataSource;

public class ReplaceMissingData2 {
    public static void main(String[] args) throws Exception {
        System.out.println("++++++++++++++Example 2: Missing Value Handing. +++++++++++++");

        System.out.println("Step 1. 读取数据...........");
        String fn = "E://Weka-3-8/data/labor.arff";
        DataSource source = new DataSource(fn);
        Instances instances = source.getDataSet();

        System.out.println("Step 2.缺失值处理...");
        int numOfAttributes = instances.numAttributes();
        int numOfInstances = instances.numInstances();

        final int duration = 0,                     //工龄
                wageIncreaseFirstYear = 1,          //第一年年薪增长
                wageIncreaseSecondYear = 2,         //第二年年薪增长
                wageIncreaseThirdYear = 3,          //第三年年薪增长
                costOfLivingAdjustment = 4,         //生活费用调整
                workingHours = 5,                   //工作时间
                pension = 6,                        //退休金
                standbyPay = 7,                     //待命薪酬
                shiftDifferential = 8,              //加班费
                educationAllowance = 9,             //教育津贴
                statutoryHolidays = 10,             //法定假日
                vacation = 11,                      //假期
                longtermDisabilityAssistance = 12,  //长期的残疾援助
                contributionToDentalPlan = 13,      //对牙科计划的贡献
                bereavementAssitance = 14,          //丧亲之助
                contributionToHealthPlan = 15,      //对健康计划的贡献
                Class = 16;                         //评级

    }
}
