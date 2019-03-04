//
// Created by PC on 2018/11/1.
// 自己写的，用的树的逻辑结构
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXNUM 10000

const int leftCode = 0;
const int rightCode = 1;

typedef struct HTNode {
    int character; // 该节点的字符
    int weight; // 权重
    struct HTNode *lchild, *rchild;
} HTNode, *HTNodeP;

typedef struct Hcode {
    int bit;
} Hcode;

void CreateHuffmanTree(HTNodeP *TreeRoot, struct HTNode array[], int size);

int findMin(struct HTNode array[], int size);

HTNodeP initHNode(int weight, int character);

void initCounter(struct HTNode array[], const int size);

int getMinWPL(HTNodeP *TreeRoot, int depth);

void HuffmanCoding(HTNodeP TreeRoot, struct Hcode codeArray[], int code);

int main() {
    HTNodeP HFTree = NULL;
    char string[100] = "AADBBccEEEEEE";
    const int size = 26;
    HTNode counter[size];
    initCounter(counter, size);

    // 只统计A-Z的大小写字符个数
    printf("编码前字符：");
    for (int j = 0; string[j] != '\0'; j++) {
        int asciiNum = toascii(string[j]);
        if (asciiNum >= 97 && asciiNum <= 122) { // A的ascii码为97，Z的ascii码为122
            asciiNum -= 32;
        }
        asciiNum -= 65; // a的ascii码为65
        counter[asciiNum].weight += 1;
        printf("%c", string[j]);
    }

    CreateHuffmanTree(&HFTree, counter, size);

    int minWPL = getMinWPL(&HFTree, 0);

    printf("\nminWPL is: %d", minWPL);

    Hcode codeArray[size];
    int code = 0;
    HuffmanCoding(HFTree, codeArray, code);
    printf("\n编码后字符：");

    // 转义
    for (int j = 0; string[j] != '\0'; j++) {
        int asciiNum = toascii(string[j]);
        if (asciiNum >= 97 && asciiNum <= 122) { // A的ascii码为97，Z的ascii码为122
            asciiNum -= 32;
        }
        asciiNum -= 65; // a的ascii码为65
        printf("%d ", codeArray[asciiNum].bit);
    }

    int z = 0;
    return 0;
}

// 初始化编码器
void initCounter(struct HTNode array[], const int size) {
    for (int i = 0; i < size; ++i) {
        array[i].weight = 0;
        array[i].character = i;
        array[i].lchild = array[i].rchild = NULL;
    }
}

// 哈夫曼编码
void HuffmanCoding(HTNodeP TreeRoot, struct Hcode codeArray[], int code) {
    if (TreeRoot->lchild != NULL && TreeRoot->rchild != NULL) {
        HuffmanCoding(TreeRoot->lchild, codeArray, 10 * code + leftCode);
        HuffmanCoding(TreeRoot->rchild, codeArray, 10 * code + rightCode);
    } else {
        int index = TreeRoot->character;
        codeArray[index].bit = code;
    }
}

// 构造哈夫曼树
void CreateHuffmanTree(HTNodeP *TreeRoot, struct HTNode array[], int size) {
    struct HTNode copyArray[size]; // 初始化
    // 复制数组
    memcpy(copyArray, array, size * sizeof(struct HTNode));

    // 找最小的两个数在数组的下标
    int minIndex1 = findMin(copyArray, size);
    int minIndex2 = findMin(copyArray, size);

    // 只剩下一棵树，则返回
    if (minIndex2 == -1) {
        return;
    }

    // 初始化连接这两个最小数的父节点
    HTNodeP Node = initHNode(array[minIndex1].weight + array[minIndex2].weight, -1);
    // 如果已有左孩子
    if (array[minIndex1].lchild == NULL && array[minIndex1].rchild == NULL) {
        Node->lchild = initHNode(array[minIndex1].weight, minIndex1);
    } else {
        Node->lchild = &array[minIndex1];
    }
    // 如果已有右孩子
    if (array[minIndex2].lchild == NULL && array[minIndex2].rchild == NULL) {
        Node->rchild = initHNode(array[minIndex2].weight, minIndex2);
    } else {
        Node->rchild = &array[minIndex2];
    }
    // 树根赋给新的节点
    *TreeRoot = Node;

    // 将原树替代为新的树，且权值叠加
    copyArray[minIndex1] = *Node;

    // 递归
    CreateHuffmanTree(TreeRoot, copyArray, size);
}

// 计算最小带权路径长度
int getMinWPL(HTNodeP *TreeRoot, int depth) {
    int left, right;
    if ((*TreeRoot)->lchild != NULL && (*TreeRoot)->rchild != NULL) {
        left = getMinWPL(&((*TreeRoot)->lchild), depth + 1);
        right = getMinWPL(&((*TreeRoot)->rchild), depth + 1);
    } else {
        return (*TreeRoot)->weight * depth;
    }
    return left + right;

}


HTNodeP initHNode(int weight, int character) {
    HTNode *Node = (HTNode *) malloc(sizeof(HTNode));
    Node->lchild = NULL;
    Node->rchild = NULL;
    Node->weight = weight;
    Node->character = character;
    return Node;
}

// 找到最小值后该最小值置零
int findMin(struct HTNode array[], int size) {
    int min = MAXNUM;
    int minIndex = -1;
    for (int i = 0; i < size; ++i) {
        if (array[i].weight != 0) {
            if (array[i].weight < min) {
                min = array[i].weight;
                minIndex = i;
            }
        }
    }
    array[minIndex].weight = 0; // 删除一棵树
    return minIndex == -1 ? -1 : minIndex; // 返回该树的下标
}

