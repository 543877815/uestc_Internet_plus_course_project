//
// Created by PC on 2018/11/3.
// 单源最短路径Dijkestra算法
//

#include <time.h>
#include <stdio.h>
#include <stdlib.h>

#define VEX_NUM 6  // 节点个数
#define MAXINT 100000 // 定义无穷大
#define DataType int

typedef int dataType;

typedef struct graph {
    char vexs[VEX_NUM]; // 顶点序列VEX_NUM为顶点数目
    dataType arcs[VEX_NUM][VEX_NUM];  // 邻接矩阵
} Mgraph, *MgraphP;


void graphInit(MgraphP *graph, int row, int col); // 初始化邻接矩阵

MgraphP graphCreate();  // 初始化图

void Traversing(dataType *array, int row, int col); // 遍历

void Dijkstra(MgraphP graph, int v0, int *path, dataType *dist); // 单源最短路径

void printPath(int v0, int *path, int *dist); // 打印该节点到各节点的最短路径

void createDisFile(MgraphP *graph, int row, int col);

void createPathFile(MgraphP *graph, int v0, int *path, dataType *dist);

int main() {
    MgraphP graph = graphCreate();
    printf("Init:\n");

    graphInit(&graph, VEX_NUM, VEX_NUM);
    createDisFile(&graph, VEX_NUM, VEX_NUM);

    Traversing(&(graph->arcs[0][0]), VEX_NUM, VEX_NUM);

    int path[VEX_NUM]; // 保存最短路径的前驱
    int dist[VEX_NUM]; // 保存最短路径长度
    int v0 = 4; // 初始节点

    Dijkstra(graph, v0, path, dist);

    printPath(v0, path, dist);
    createPathFile(&graph, v0, path, dist);

    return 0;
}

// 可视化部分
void createPathFile(MgraphP *graph, int v0, int *path, dataType *dist) {
    for (int i = 0; i < VEX_NUM; i++) {
        if (v0 != i) {
            // 创建文件
            char *filename = (char *) malloc(100);
            sprintf(filename, "./dotFile/v%d_to_v%d.dot", v0, i);
            FILE *fp = fopen(filename, "w"); // 文件指针
            if (fp == NULL) {   // 为NULL则返回
                printf("File cannot open!");
                exit(0);
            }
            char *title = (char *) malloc(100);
            sprintf(title, "v%d -> v%d", v0, i);    // 文件名
            fprintf(fp, "digraph G {\n");   // 开头

            // 构建原始领接图
            for (int j = 0; j < VEX_NUM; j++) {
                fprintf(fp, "v%d[shape=ellipse];\n", j);
                for (int k = 0; k < VEX_NUM; k++) {
                    if ((*graph)->arcs[j][k] < MAXINT) {
                        fprintf(fp, "v%d->v%d[label=\"%d\"];\n", j, k, (*graph)->arcs[j][k]);
                    }
                }
            }

            fprintf(fp, "graph[label=\"%s, minDist: %d\"];\n", title, dist[i]); // 标题生成，记录最短距离
            fprintf(fp, "edge[labelfontcolor=red,fontcolor=red,color=red];\n");
            int temp = path[i];
            // 初始路径
            fprintf(fp, "v%d[color=red];\n", i);
            fprintf(fp, "v%d->v%d[color=red,label=\"%d\"];\n", temp, i, (*graph)->arcs[temp][i]);
            // 遍历前驱路径并标红
            while (v0 != temp) {
                fprintf(fp, "v%d[color=red];\n", temp);
                fprintf(fp, "v%d->v%d[label=\"%d\"];\n", path[temp], temp,
                        (*graph)->arcs[path[temp]][temp]);
                temp = path[temp];
            }
            // 最终节点标红
            fprintf(fp, "v%d[color=red];\n", v0);
            fprintf(fp, "}\n"); // 结尾
            fclose(fp); // 关闭IO
            char *order = (char *) malloc(100);
            sprintf(order, "dot -Tpng ./dotFile/v%d_to_v%d.dot -o ./dotFile/v%d_to_v%d.png", v0, i, v0, i);
            system(order);
        }
    }
}

// 打印该节点到各节点的最短路径
void printPath(int v0, int *path, int *dist) {
    for (int i = 0; i < VEX_NUM; i++) {
        // 不打印该节点到本节点的最短路径
        if (v0 != i) {
            printf("v%d -> v%d, minDist: %d, path: v%d <- ", v0, i, dist[i], i);
            int temp = path[i];
            // 如果该节点的前驱不等于源节点，则继续递归访问
            while (v0 != temp) {
                printf("v%d <- ", temp);
                // 记录前驱
                temp = path[temp];
            }
            printf("v%d", v0);
            printf("\n");
        }
    }
}

// 单源最短路径
void Dijkstra(MgraphP graph, int v0, int *path, dataType *dist) {
    for (int i = 0; i < VEX_NUM; i++) {
        // 初始化距离
        dist[i] = graph->arcs[v0][i];
        // 如果不可达，则前驱置为-1
        if (dist[i] < MAXINT) { // 如果可达，则前驱置为该单源初始点
            path[i] = v0;
        } else {  // 如果不可达，则前驱置为-1
            path[i] = -1;
        }
    }

    int s[VEX_NUM] = {0}; // 记录没有遍历到的节点，初始为0
    dist[v0] = 0; // 节点到自身的路径长度为0
    s[v0] = 1; // 该节点已经遍历完成，置为1

    for (int i = 1; i < VEX_NUM; i++) { // 循环剩余n-1个节点
        int v = -1; // 记录点的位置，初始化为-1
        int min = MAXINT; // 记录点的最小值，初始化为最大值
        for (int j = 0; j < VEX_NUM; j++) {
            if (s[j] != 1 && dist[j] < min) { // 该节点未被遍历，并且该值最小
                min = dist[j]; // 记录该值
                v = j;  // 记录该点位置
            }
        }

        // 如果不存在该值，则跳过
        if (v == -1) {
            break;
        }

        // 否则进行下面
        s[v] = 1; // 表示该点已经遍历
        for (int j = 0; j < VEX_NUM; j++) {
            // 如果该点没被遍历，并且更新后的路径比原路径短，则替换
            if (s[j] != 1 && (min + graph->arcs[v][j] < dist[j])) {
                dist[j] = min + graph->arcs[v][j];
                path[j] = v;
            }
        }
    }
}

// 遍历
void Traversing(dataType *array, int row, int col) {
    for (int i = 0; i < row; i++) {
        printf("v%d          ", i);
        for (int j = 0; j < col; j++) {
            printf("%d ", *(array + i * col + j));
        }
        printf("\n");
    }
}

// 初始化图
MgraphP graphCreate() {
    Mgraph *graph = (Mgraph *) malloc(sizeof(Mgraph)); // 申请节点空间
    if (!graph) { // 判断是否有足够的内存空间
        printf("申请内存空间失败！\n");
    }
    return graph;
}

// 初始化邻接矩阵
void graphInit(MgraphP *graph, int row, int col) {
    int size = 100;
    DataType A[size];
    // 读取文件数据，保存在数组A中
    FILE *fp = fopen("./data/distance.txt", "r+");
    if (fp == NULL)
        exit(0x01);
    DataType keynumber;
    for (int i = 0; i < size; i++) {
        fscanf(fp, "%d", &keynumber);
        A[i] = keynumber;
    }
    fclose(fp);
    // 将读取的数据赋值到graph中
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            (*graph)->arcs[i][j] = A[i * 10 + j];
        }
    }
}

// 创建领接图
void createDisFile(MgraphP *graph, int row, int col) {
    FILE *fp = fopen("./dotFile/Dijkestra_Dis.dot", "w");
    if (fp == NULL) {
        printf("File cannot open!");
        exit(0);
    }
    fprintf(fp, "digraph G {\n");
    for (int i = 0; i < row; i++) {
        fprintf(fp, "v%d[shape=ellipse];\n", i);
        for (int j = 0; j < col; j++) {
            if ((*graph)->arcs[i][j] < MAXINT) {
                fprintf(fp, "v%d->v%d\n[label=\"%d\"];\n", i, j, (*graph)->arcs[i][j]);
            }
        }
    }
    fprintf(fp, "}\n");
    fclose(fp);
    system("dot -Tpng ./dotFile/Dijkestra_Dis.dot -o ./dotFile/Dijkestra_Dis.png");
}

