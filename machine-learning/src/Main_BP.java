/**
 * 数据定义
 * 转化 色泽	根蒂	敲声	纹理	脐部	触感	好瓜
 * 1	青绿	蜷缩	浊响	清晰	凹陷	硬滑	是-1
 * 2	乌黑	稍蜷	沉闷	稍糊	稍凹	软粘	否-0
 * 3	浅白	硬挺	清脆	模糊	平坦
 */

/**
 * 西瓜数据集2.0
 * 训练集
 * 编号	色泽	根蒂	敲声	纹理	脐部	触感	好瓜
 * 1	     1	    1	    1	    1	    1	    1	    1
 * 2	     2	    1	    2	    1	    1	    1	    1
 * 3	     2	    1	    1	    1	    1	    1	    1
 * 6	     1	    2	    1	    1	    2	    2	    1
 * 7	     2	    2	    1	    2	    2	    2	    1
 * 10	     1	    3	    3	    1	    3	    2	    0
 * 14	     3	    2	    2	    2	    1	    1	    0
 * 15	     2	    2	    1	    1	    2	    2	    0
 * 16	     3	    1	    1	    3	    3	    1	    0
 * 17	     1	    1	    2	    2	    2	    1	    0
 * <p>
 * <p>
 * 验证集
 * 4	     1	    1	    2	    1	    1	    1	    1
 * 5	     3	    1	    1	    1	    1	    1	    1
 * 8	     2	    2	    1	    1	    2	    1	    1
 * 9	     2	    2	    2	    2	    2	    1	    0
 * 11	     3	    3	    3	    3	    3	    1	    0
 * 12	     3	    1	    1	    3	    3	    2	    0
 * 13	     1	    2	    1	    2	    1	    1	    0
 */

public class Main_BP {
    public static void main(String[] args) {
        int input_node = 6;
        int hide1_node = 7;
        int output_node = 1;
        double rate = 0.1;
        Bp bp = new Bp(input_node, hide1_node, output_node, rate);

        double[][] TrainingInput = {
                {1.0, 1.0, 1.0, 1.0, 1.0, 1.0},
                {2.0, 1.0, 2.0, 1.0, 1.0, 1.0},
                {2.0, 1.0, 1.0, 1.0, 1.0, 1.0},
                {1.0, 2.0, 1.0, 1.0, 2.0, 2.0},
                {2.0, 2.0, 1.0, 2.0, 2.0, 2.0},
                {1.0, 3.0, 3.0, 1.0, 3.0, 2.0},
                {3.0, 2.0, 2.0, 2.0, 1.0, 1.0},
                {2.0, 2.0, 1.0, 1.0, 2.0, 2.0},
                {3.0, 1.0, 1.0, 3.0, 3.0, 1.0},
                {1.0, 1.0, 2.0, 2.0, 2.0, 1.0}
        };

        double[][] TrainingOutput = {{1.0}, {1.0}, {1.0}, {1.0}, {1.0}, {0.0}, {0.0}, {0.0}, {0.0}, {0.0}};

        double endError = 0.001;
        int endLoop = 50;
        int times = 0;
        while (true) {
            for (int i = 0; i < TrainingOutput.length; i++) {
                bp.train(TrainingInput[i], TrainingOutput[i]);
            }
            if (bp.CalcErrDiff() < endError) {
                endLoop += 1;
                if (endLoop == 50) {
                    break;
                }
            } else {
                endLoop = 0;
            }
            times++;

        }

        System.out.println("训练完毕，迭代次数：" + times);

        double[][] TestInput = {
                {1.0, 1.0, 2.0, 1.0, 1.0, 1.0},
                {3.0, 1.0, 1.0, 1.0, 1.0, 1.0},
                {2.0, 2.0, 1.0, 1.0, 2.0, 1.0},
                {2.0, 2.0, 2.0, 2.0, 2.0, 1.0},
                {3.0, 3.0, 3.0, 3.0, 3.0, 1.0},
                {3.0, 1.0, 1.0, 3.0, 3.0, 2.0},
                {1.0, 2.0, 1.0, 2.0, 1.0, 1.0}
        };

        double[][] TestOutput = {{1.0}, {1.0}, {1.0}, {0.0}, {0.0}, {0.0}, {0.0}};

        double[][] PredictOutput = new double[TestInput.length][TrainingOutput[0].length];

        for (int i = 0; i < PredictOutput.length; i++) {
            bp.predict(TestInput[i], PredictOutput[i], TestOutput[i]);
            System.out.println("预测值：" + PredictOutput[i][0] + "，实际值：" + TestOutput[i][0]);
        }
        System.out.println("均方误差是：" + bp.getMSError());

        System.out.println("输入层到隐含层的权重：");
        double[][] hide_w = bp.getWeightHide1();
        for (int i = 0; i < hide_w.length; i++) {
            for (int j = 0; j < hide_w[i].length; j++) {
                System.out.print(hide_w[i][j] + "  ");
            }
            System.out.println();
        }

        System.out.println("隐含层到输出层的权重：");
        double[][] out_w = bp.getWeightOutput();
        for (int i = 0; i < out_w.length; i++) {
            for (int j = 0; j < out_w[i].length; j++) {
                System.out.println(out_w[i][j] + "  ");
            }
            System.out.println();
        }

        System.out.println("隐层的阈值：");
        double[] out_theta = bp.getThetaOutput();
        for (int i = 0; i < out_theta.length; i++) {
            System.out.println(out_theta[i] + "  ");
        }

        System.out.println("输出层的阈值：");
        double[] hide1_theta = bp.getThetaHide1();
        for (int i = 0; i < hide1_theta.length; i++) {
            System.out.println(hide1_theta[i] + "  ");
        }
    }
}
