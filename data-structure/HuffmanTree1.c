//
// Created by PC on 2018/11/7.
// 使用数组来写的
//

#include <stdio.h>
#include <stdlib.h>

#define MAXBIT 10
#define MAXNUM 1000
typedef struct HNode {
    int weight;
    int parent, lchild, rchild;
} HNode;

typedef struct HCode {
    int bit[MAXBIT];
    int start;
} HCode;

void HuffmanCoding(HNode *HT, HCode *HC, int *weight, const int size);

int main() {
    const int size = 5;
    int weight[5] = {2, 1, 2, 2, 6};
    int totalSize = 2 * size - 1; // 哈夫曼树一共有2n-1个节点，叶节点有n个，另外增加了n-1个将他们连起来

    HNode *HuffmanTree = (HNode *) malloc(totalSize * sizeof(HNode));
    HCode *HuffmanCode = (HCode *) malloc(size * sizeof(HCode));

    HuffmanCoding(HuffmanTree, HuffmanCode, weight, size);

    return 0;
}

void HuffmanCoding(HNode *HT, HCode *HC, int *weight, const int size) {
    if (size <= 1) {
        return;
    }
    int totalSize = 2 * size - 1; // 哈夫曼树一共有2n-1个节点，叶节点有n个，另外增加了n-1个将他们连起来

    HNode *p = HT;

    // 哈夫曼树的初始化
    int i;
    for (i = 0; i < size; i++, p++, weight++) {
        p->parent = p->lchild = p->rchild = -1;
        p->weight = *weight;
    }
    for (; i < totalSize; i++, p++) {
        p->parent = p->lchild = p->rchild = -1;
        p->weight = 0;
    }

    // 构造哈夫曼树
    for (int k = size; k < totalSize; k++) {
        int min1 = MAXNUM, min2 = MAXNUM;   // 最小值
        int x1 = 0, x2 = 0; // 最小值的下标
        for (int j = 0; j < k; j++) {
            if (HT[j].parent == -1 && HT[j].weight < min1) {
                min2 = min1;
                x2 = x1;
                min1 = HT[j].weight;
                x1 = j;
            } else if (HT[j].parent == -1 && HT[j].weight < min2) {
                x2 = j;
                min2 = HT[j].weight;
            }
        }
        HT[x1].parent = HT[x2].parent = k;
        HT[k].lchild = x1;
        HT[k].rchild = x2;
        HT[k].weight = min1 + min2;
    }

    // 字符编码
    for (int j = 0; j < size; j++) {
        int start = size - 1;
        for (int k = j, f = HT[j].parent; f != -1; k = f, f = HT[k].parent) {
            if (HT[f].lchild == k) {
                HC[j].bit[start] = 0;
                start--;
            } else {
                HC[j].bit[start] = 1;
                start--;
            }

        }
        HC[j].start = start + 1;
    }
}
