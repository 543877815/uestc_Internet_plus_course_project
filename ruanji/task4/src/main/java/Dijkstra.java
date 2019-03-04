//public class Dijkstra {
//    //    public static void main(String[] args) {
////        minStep(0, Graph);
////    }
//    private static int N = 1000;
//
//    /**
//     * Dijkstra最短路径。
//     * 即图中"节点vs"到其它各个节点的最短路径。
//     *
//     * @param vs    起始节点
//     * @param Graph 图
//     */
//    public static void minStep(int vs, int[][] Graph) {
//        int NUM = Graph[0].length;
//        // 前驱节点数组
//        int[] prenode = new int[NUM];
//        // 最短距离数组
//        int[] mindist = new int[NUM];
//        // 该节点是否已经找到最短路径
//        boolean[] find = new boolean[NUM];
//
//        int vnear = 0;
//
//        for (int i = 0; i < mindist.length; i++) {
//            prenode[i] = i;
//            mindist[i] = Graph[vs][i];
//            find[i] = false;
//        }
//
//        find[vs] = true;
//
//        for (int v = 1; v < Graph.length; v++) {
//
//            // 每次循环求得距离vs最近的节点vnear和最短距离min
//            int min = N;
//            for (int j = 0; j < Graph.length; j++) {
//                if (!find[j] && mindist[j] < min) {
//                    min = mindist[j];
//                    vnear = j;
//                }
//            }
//            find[vnear] = true;
//
//            // 根据vnear修正vs到其他所有节点的前驱节点及距离
//            for (int k = 0; k < Graph.length; k++) {
//                if (!find[k] && (min + Graph[vnear][k]) < mindist[k]) {
//                    prenode[k] = vnear;
//                    mindist[k] = min + Graph[vnear][k];
//                }
//            }
//        }
//
//        for (int i = 0; i < NUM; i++) {
//            System.out.println("v" + vs + "...v" + prenode[i] + "->v" + i + ", s=" + mindist[i]);
//        }
//    }
//}

import java.util.ArrayList;
import java.util.List;

public class Dijkstra {

    public static void main(String[] args) {
        //此路不通
        int m = 10000;
        int[][] weight1 = {//邻接矩阵
                {0, 3, 2000, 7, m},
                {3, 0, 4, 2, m},
                {m, 4, 0, 5, 4},
                {7, 2, 5, 0, 6},
                {m, m, 4, 6, 0}
        };

        int[][] weight2 = {
                {0, 10, m, 30, 100},
                {m, 0, 50, m, m},
                {m, m, 0, m, 10},
                {m, m, 20, 0, 60},
                {m, m, m, m, 0}
        };

        List<String> regions = new ArrayList<String>(){{
            add("A");
            add("B");
            add("C");
            add("D");
            add("E");
        }};

        int start = 0;
        int[] shortPath = minStep(weight1, start, -1, regions);
//        for (int i = 0; i < shortPath.length; i++)
//            System.out.println("从" + start + "出发到" + i + "的最短距离为：" + shortPath[i]);
    }

    public static int[] minStep(int[][] weight, int start, int end, List<String> regions) {
        //接受一个有向图的权重矩阵，和一个起点编号start（从0编号，顶点存在数组中）
        //返回一个int[] 数组，表示从start到它的最短路径长度
        int n = weight.length;      //顶点个数
        int[] shortPath = new int[n];  //保存start到其他各点的最短路径
        String[] path = new String[n];  //保存start到其他各点最短路径的字符串表示
        for (int i = 0; i < n; i++)
            path[i] = regions.get(start) + "-->" + regions.get(i);
        int[] visited = new int[n];   //标记当前该顶点的最短路径是否已经求出,1表示已求出

        //初始化，第一个顶点已经求出
        shortPath[start] = 0;
        visited[start] = 1;

        for (int count = 1; count < n; count++) {   //要加入n-1个顶点
            int k = -1;        //选出一个距离初始顶点start最近的未标记顶点
            int dmin = Integer.MAX_VALUE;
            for (int i = 0; i < n; i++) {
                if (visited[i] == 0 && weight[start][i] < dmin) {
                    dmin = weight[start][i];
                    k = i;
                }
            }

            //将新选出的顶点标记为已求出最短路径，且到start的最短路径就是dmin
            shortPath[k] = dmin;
            visited[k] = 1;

            //以k为中间点，修正从start到未访问各点的距离
            for (int i = 0; i < n; i++) {
                if (visited[i] == 0 && weight[start][k] + weight[k][i] < weight[start][i]) {
                    weight[start][i] = weight[start][k] + weight[k][i];
                    path[i] = path[k] + "-->" + regions.get(i);
                }
            }
        }
        if (end == -1) {
            for (int i = 0; i < n; i++) {
                System.out.println("从" + regions.get(start) + "出发到" + regions.get(i) + "的最短路径为：" + path[i] + "，最短距离为：" + shortPath[i]);
            }
            System.out.println("=====================================");
        } else {
            System.out.println("从" + regions.get(start) + "出发到" + regions.get(end) + "的最短路径为：" + path[end] + "，最短距离为：" + shortPath[end]);
        }
        return shortPath;
    }
}