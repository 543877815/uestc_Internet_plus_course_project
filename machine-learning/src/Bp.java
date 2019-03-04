/**
 * Bp神经网络
 * reference https://www.cnblogs.com/hesi/p/7218602.html
 */
public class Bp {
    private double[] hide1_x; // 输入层即第一层隐含层的输入; hide1_x[数据的特征数目+1]，hide1_w[0]为1
    private double[][] hide1_w; // 隐含层权值，hide1_w[本层节点数目][数据的特征数目+1]；hide_w[0][0]为偏置量
    private double[] hide1_errors; // 隐含层的误差，hide1_errors[节点个数]
    private double[] hide1_theta; // 隐含层的阈值,hide1_errors[节点个数]

    private double[] out_x; // 输出层的输入值即第二层隐含层的输出 out_x[上一层的节点数+1], out_x[0]为1
    private double[][] out_w; // 输出层的权值，hide1_w[节点的数目][上一层的节点数目+1]， out_w[0][0]为偏置量
    private double[] out_errors; // 输出层的误差，hide1_error[节点个数]
    private double[] pre_out_errors; // 上一次输出层的误差，hide1_error[节点个数]
    private double[] out_theta; // 输出层的阈值,out_node[节点个数]

    private double[] target; // 目标值，target[输出层的节点个数]

    private double MS_error; // 计算均方误差

    private double rate; // 学习速率


    Bp(int input_node, int hide1_node, int out_node, double rate) {
        super();

        // 输入层即第一层隐含层的输入
        hide1_x = new double[input_node + 1];

        // 第一层隐含层
        hide1_w = new double[hide1_node][input_node + 1];
        hide1_errors = new double[hide1_node];
        hide1_theta = new double[hide1_node];

        // 输出层
        out_x = new double[hide1_node + 1];
        out_w = new double[out_node][hide1_node + 1];
        out_errors = new double[out_node];
        out_theta = new double[out_node];
        pre_out_errors = new double[out_node];

        // 输出层
        target = new double[out_node];

        // 均方误差为0
        MS_error = 0;

        // 学习速率
        this.rate = rate;

        init_weight();// 1.初始化网络的权值
        init_theta(); // 2.初始化网络的阈值
    }

    /**
     * 初始化阈值
     */
    private void init_theta() {
        set_theta(hide1_theta);
        set_theta(out_theta);
    }

    /**
     * 初始化阈值
     *
     * @param theta 阈值
     */
    private void set_theta(double[] theta) {
        for (int i = 0; i < theta.length; i++) {
            theta[i] = Math.random();
        }
    }

    /**
     * 初始化权值
     */
    private void init_weight() {
        set_weight(hide1_w);
        set_weight(out_w);
    }

    /**
     * 权值初始化为0
     *
     * @param weight 传入初始权值
     */
    private void set_weight(double[][] weight) {
        for (int i = 0; i < weight.length; i++) {
            for (int j = 0; j < weight[i].length; j++) {
                weight[i][j] = Math.random();
            }
        }
    }

    /**
     * 传入原始数据
     *
     * @param Data 传入数据
     */
    private void setHide1_x(double[] Data) {
        if (Data.length != hide1_x.length - 1) {
            throw new IllegalArgumentException("数据大小与输出层节点不匹配");
        }
        System.arraycopy(Data, 0, hide1_x, 1, Data.length);
        hide1_x[0] = 1.0;
    }

    /**
     * 设置目标数据
     *
     * @param target 目标数据
     */
    private void setTarget(double[] target) {
        this.target = target;
    }

    public void train(double[] TrainData, double[] target) {
        // 2.1.导入训练数据集和目标值
        setHide1_x(TrainData);
        setTarget(target);

        // 2.2.向前传播得到输出值
        double[] output = new double[out_w.length + 1];
        forword(hide1_x, output);

        // 2.3.反向传播
        backpropagation(output);
    }

    /**
     * 反向传播过程
     *
     * @param output 预测结果
     */
    private void backpropagation(double[] output) {
        // 2.3.1.获取输出层的误差；
        get_out_error(output, target, out_errors);
        // 2.3.2.获取隐含层的误差；
        get_hide_error(out_errors, out_w, out_x, hide1_errors);
        // 2.3.3.更新输入层到隐含层的权值；
        update_weight(hide1_errors, hide1_w, hide1_x);
        // 2.3.4 更新隐含层的阈值；
        update_theta(hide1_errors, hide1_theta);
        // 2.3.5.更新隐含层到输出层的权值；
        update_weight(out_errors, out_w, out_x);
        // 2.3.6.更新输出层的阈值；
        update_theta(out_errors, out_theta);
    }

    /**
     * 新的阈值=原阈值+(-学习速率×该节点的误差)
     *
     * @param hide1_errors 该层误差
     * @param hide1_theta  原阈值
     */
    private void update_theta(double[] hide1_errors, double[] hide1_theta) {
        double newTheta = 0.0;
        for (int i = 0; i < hide1_errors.length; i++) {
            newTheta = - rate * hide1_errors[i];
            hide1_theta[i] += newTheta;
        }
    }

    /**
     * 新的权值=原权值+学习速率×该节点的误差×激励函数的导函数的值
     *
     * @param error  该层误差
     * @param weight 原来权重
     * @param input  上层输出
     */
    private void update_weight(double[] error, double[][] weight, double[] input) {
        double newWeight = 0.0;
        for (int i = 0; i < weight.length; i++) {
            for (int j = 0; j < weight[i].length; j++) {
                newWeight = rate * error[i] * input[j];
                weight[i][j] = weight[i][j] + newWeight;
            }
        }
    }

    /**
     * 获取隐含层的误差，西瓜书eh
     *
     * @param NextLayorError 下一层的误差
     * @param NextWeight     下一层的权值
     * @param NextOutput     下一层的输入
     * @param error          本层误差数组
     */
    private void get_hide_error(double[] NextLayorError, double[][] NextWeight, double[] NextOutput, double[] error) {
        for (int i = 0; i < error.length; i++) {
            double sum = 0;
            for (int j = 0; j < NextWeight.length; j++) {
                sum += NextWeight[j][i + 1] * NextLayorError[j];
            }
            error[i] = sum * NextOutput[i + 1] * (1d - NextOutput[i + 1]);
        }
    }

    /**
     * 获取输出层的误差，西瓜树gj
     *
     * @param output     预测输出值
     * @param target     目标值
     * @param out_errors 输出层误差
     */
    private void get_out_error(double[] output, double[] target, double[] out_errors) {
        for (int i = 0; i < target.length; i++) {
            pre_out_errors[i] = out_errors[i];
            out_errors[i] = (target[i] - output[i + 1]) * output[i + 1] * (1d - output[i + 1]);
        }
    }

    /**
     * 向前传播
     *
     * @param input  输入层输入
     * @param output 输出层输出
     */
    private void forword(double[] input, double[] output) {
        // 2.2.1.获取隐含层的输出
        get_net_out(input, hide1_w, hide1_theta, out_x);
        // 2.2.2.获取输出层的输出
        get_net_out(out_x, out_w, out_theta, output);
    }

    /**
     * 获取网络层的输出
     *
     * @param input  输入矩阵
     * @param weight 权值矩阵
     * @param theta  阈值
     * @param output 接受网络层的输出数据
     */
    private void get_net_out(double[] input, double[][] weight, double[] theta, double[] output) {
        output[0] = 1d;
        for (int i = 0; i < weight.length; i++) {
            output[i + 1] = get_node_put(input, weight[i], theta[i]);
        }
    }

    /**
     * 获取单个节点的输出
     *
     * @param input  输入矩阵
     * @param weight 权值
     * @param theta  阈值
     * @return 输出值
     */
    private double get_node_put(double[] input, double[] weight, double theta) {
        double z = 0d;

        for (int i = 0; i < input.length; i++) {
            z += input[i] * weight[i];
        }

        // 激励函数
        return sigmoid(z + theta);
    }

    /**
     * sigmoid激励函数
     *
     * @param x 输入
     * @return 输出
     */
    private double sigmoid(double x) {
        return 1d / (1d + Math.exp(-x));
    }

    /**
     * 预测函数
     *
     * @param data   预测输入
     * @param output 预测输出
     */
    public void predict(double[] data, double[] output, double[] target) {
        double[] out_y = new double[out_w.length + 1];
        setHide1_x(data);
        forword(hide1_x, out_y);
        System.arraycopy(out_y, 1, output, 0, output.length);
        calc_error(target, output);
    }

    /**
     * 计算前后两次训练的误差
     */
    private void calc_error(double[] target, double[] output) {
        for (int i = 0; i < target.length; i++) {
            MS_error += 0.5 * (Math.pow(target[i], 2) - Math.pow(output[i], 2));
        }
    }

    /**
     * 返回均方误差
     *
     * @return 均方误差
     */
    public double getMSError() {
        return MS_error;
    }

    /**
     * 计算前后两次训练误差
     *
     * @return 返回训练误差的绝对值
     */
    public double CalcErrDiff() {
        double min = 10000;
        for (int i = 0; i < pre_out_errors.length; i++) {
            double diff = out_errors[i] - pre_out_errors[i];
            min = min > diff ? diff : min;
        }
        return Math.abs(min);
    }

    /**
     * 返回隐含层第一层的权重
     *
     * @return 权重矩阵
     */
    public double[][] getWeightHide1() {
        return hide1_w;
    }

    /**
     * 返回输出层的权重
     *
     * @return 权重矩阵
     */
    public double[][] getWeightOutput() {
        return out_w;
    }

    /**
     * 返回隐层的阈值
     * @return 阈值
     */
    public double[] getThetaHide1(){
        return hide1_theta;
    }

    /**
     * 返回输出层的阈值
     * @return 阈值
     */
    public double[] getThetaOutput(){
        return out_theta;
    }
}
