import java.io.IOException;

/**
 * 西瓜数据集3.0a
 * 1 0.697 0.460 1
 * 2 0.774 0.376 1
 * 3 0.634 0.264 1
 * 4 0.608 0.318 1
 * 5 0.556 0.215 1
 * 6 0.403 0.237 1
 * 7 0.481 0.149 1
 * 8 0.437 0.211 1
 * 9 0.666 0.091 0
 * 10 0.243 0.267 0
 * 11 0.245 0.057 0
 * 12 0.343 0.099 0
 * 13 0.639 0.161 0
 * 14 0.657 0.198 0
 * 15 0.360 0.370 0
 * 16 0.593 0.042 0
 * 17 0.719 0.103 0
 * <p>
 * 训练集
 * 1 0.697 0.460 1
 * 2 0.774 0.376 1
 * 3 0.634 0.264 1
 * 4 0.608 0.318 1
 * 5 0.556 0.215 1
 * 6 0.403 0.237 1
 * 9 0.666 0.091 0
 * 10 0.243 0.267 0
 * 11 0.245 0.057 0
 * 12 0.343 0.099 0
 * 13 0.639 0.161 0
 * 14 0.657 0.198 0
 * <p>
 * 测试集
 * 7 0.481 0.149 1
 * 8 0.437 0.211 1
 * 15 0.360 0.370 0
 * 16 0.593 0.042 0
 * 17 0.719 0.103 0
 */
public class Main_SVM {
    public static void main(String[] args) throws IOException {
        String path = "D:/Project/java/src/data/";
        String[] arg = {"-c", "100000000", "-t", "0", path + "SVM_train.txt", path + "SVM_model.txt"};
        String[] parg = {path + "SVM_test.txt", path + "SVM_model.txt", path + "SVM_out.txt"};
        svm_train training = new svm_train();
        svm_predict predict = new svm_predict();
        training.main(arg);
        predict.main(parg);
    }
}
