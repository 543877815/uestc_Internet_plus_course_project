//
// Created by PC on 2018/10/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MaxSize 100

typedef int DataType;
// 二叉排序树
typedef struct BSTNode {
    DataType data;
    struct BSTNode *lchild, *rchild;
} BSTree, *BSTreeP;

BSTreeP InitNode();  // 初始化一个二叉排序树节点

void BSTreeInsertNode(BSTreeP *TreeRoot, DataType data);    // 插入

void DeleteBST(BSTreeP *TreeRoot, int value);   // 删除

int SearchBST(BSTreeP TreeRoot, int value, BSTreeP *Node, BSTreeP *ParentNode); // 查找

void PreOrder(BSTreeP TreeRoot);    // 前序遍历

void InOrder(BSTreeP TreeRoot);     // 中序遍历

void PostOrder(BSTreeP TreeRoot);   // 后序遍历

void LevelOrder(BSTreeP TreeRoot);  // 层次遍历

void NodeVisit(DataType data);      // 打印值

int Depth(BSTreeP TreeRoot);    //  计算树的深度

int CountLeaf(BSTreeP TreeRoot);    // 计算叶子的个数

int CountBiNode(BSTreeP TreeRoot);  // 计算总节点个数

int max(int a, int b);  // 返回最大值

void Exchange(BSTreeP TreeRoot);    // 交换左右子树

void CBTreeInsertNode(BSTreeP *TreeRoot, DataType value); // 创建一个完全二叉树

void ChangeBST(BSTreeP TreeRoot, int oldValue, int newValue); // 改变

void createDotFile(const char *filename, BSTreeP TreeRoot); // 可视化

int main() {
    // 创建完全二叉树
    BSTreeP CBTree = NULL;
    DataType A[11] = {1, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
    for (int i = 0; i < 11; i++) {
        CBTreeInsertNode(&CBTree, A[i]);
    }
    LevelOrder(CBTree);
    printf("-->Complete BiTree LevelOrder\n");

    // 创建二叉排序树并绘制图片
    FILE *fp = fopen("./data/data.txt", "r+");
    if (fp == NULL)
        exit(0x01);
    BSTreeP BiTree = NULL;
    DataType keynumber;
    //    for (int i = 0; i < MaxSize; i++) {
    //        BSTreeInsertNode(&BiTree, A[i]);
    //    }
    while (EOF != fscanf(fp, "%d", &keynumber)) {
        BSTreeInsertNode(&BiTree, keynumber);
    }
    fclose(fp);
//    createDotFile("./dotFile/BST.dot", BiTree);
//    system("dot -Tpng ./dotFile/BST.dot -o ./dotFile/BST.png");

    // 前序遍历
    PreOrder(BiTree);
    printf("-->PreOrder\n");

    // 中序遍历
    InOrder(BiTree);
    printf("-->InOrder\n");

    // 后序遍历
    PostOrder(BiTree);
    printf("-->PostOrder\n");

    // 层次遍历
    LevelOrder(BiTree);
    printf("-->LevelOrder\n");

    // 求叶子数
    int LeafNum = CountLeaf(BiTree);
    printf("num of leaf is: %d\n", LeafNum);

    // 求节点数
    int BiNodeNum = CountBiNode(BiTree);
    printf("num of BiNode is: %d\n", BiNodeNum);

    // 求深度
    int depth = Depth(BiTree);
    printf("the depth of the tree is: %d\n", depth);

    // 查找某节点
    int value = 20;
    BSTreeP ParentNode = NULL, Node = NULL;
    int result = SearchBST(BiTree, value, &Node, &ParentNode);
    if (Node != NULL) {
        printf("result: %d, value is: %d", result, Node->data);
    } else {
        printf("result: %d", result);
    }
    printf("\n");

    // 改变某节点，但是会破坏排序树的结构
    // ChangeBST(BiTree, 20, 30);
    // LevelOrder(BiTree);
    // printf("-->ChangeBST LevelOrder\n");

    // 删除某节点
    DeleteBST(&BiTree, 370);
    InOrder(BiTree);
    printf("-->DeleteBST InOrder\n");
    createDotFile("./dotFile/BST_Delete.dot", BiTree);
    system("dot -Tpng ./dotFile/BST_Delete.dot -o ./dotFile/BST_Delete.png");

    // 交换左右子树b
    Exchange(BiTree);
    PreOrder(BiTree);
    printf("-->switch subtree\n");
    printf("\n");
    return 0;
}

void createDotFile(const char *filename, BSTreeP TreeRoot) {
    FILE *fp = fopen(filename, "w");    // 文件指针
    if (fp == NULL) {   // 为NULL则返回
        printf("File cannot open!");
        exit(0);
    }
    fprintf(fp, "digraph G {\n");   // 开头
    // 利用层次遍历构造
    BSTreeP Queue[MaxSize]; // 定义队列
    int front = -1, rear = 0;
    if (TreeRoot == NULL) return; // 空二叉树，遍历结束
    Queue[rear] = TreeRoot; // 根结点入队列
    while (rear != front) { // 若队列不空，继续遍历。否则，遍历结束
        front++; // 出队
        NodeVisit(Queue[front]->data); // 访问刚出队的元素
        fprintf(fp, "%d [shape=circle];\n", Queue[front]->data);
        if (Queue[front]->lchild != NULL) { // 如果有左孩子，左孩子入队
            rear++;
            Queue[rear] = Queue[front]->lchild;
            fprintf(fp, "%d->%d;\n", Queue[front]->data, Queue[front]->lchild->data);
        }
        if (Queue[front]->rchild != NULL) { // 如果有右孩子，右孩子入队
            rear++;
            Queue[rear] = Queue[front]->rchild;
            fprintf(fp, "%d->%d;\n", Queue[front]->data, Queue[front]->rchild->data);
        }
    }
    fprintf(fp, "}\n"); // 结尾
    fclose(fp); // 关闭IO
}

// 删除某节点，先搜索，后删除
void DeleteBST(BSTreeP *TreeRoot, int value) {
    BSTreeP Node = NULL, ParentNode = NULL;
    if (SearchBST(*TreeRoot, value, &Node, &ParentNode) == 0) { // 对该节点进行搜索，如果没有则返回，若有则继续
        printf("fail, not exit\n");
        return;
    } else {
        if (Node->lchild == NULL && Node->rchild == NULL) {     // 判断为叶子节点
            if (ParentNode == NULL) {   // 如果有且只有一个根节点
                free(Node);     //  释放该节点
            } else if (ParentNode->lchild == Node) {    // 如果该叶子节点是左孩子
                ParentNode->lchild = NULL;  // 其父节点的右孩子指向NULL
            } else {    // 如果该叶子节点是右孩子
                ParentNode->rchild = NULL;  //  其父节点的右孩子指向NULL
            }
            free(Node);     //  释放待删除节点
        } else if (Node->lchild == NULL && Node->rchild != NULL) { // 判断只有右子树
            if (ParentNode == NULL) {   //  如果父节点为根节点
                *TreeRoot = Node->rchild;   // 树根指针指向其右子树
            } else if (ParentNode->lchild == Node) {    // 如果为父节点的左子树
                ParentNode->lchild = Node->rchild;  //  父节点的左指针指向该节点的左孩子
            } else {    // 如果为父节点的右子树
                ParentNode->rchild = Node->rchild;  //  父节点的右指针指向该节点的右孩子
            }
            free(Node);     //  释放待删除节点
        } else if (Node->rchild == NULL && Node->lchild != NULL) { // 判断只有左子树
            if (ParentNode == NULL) {   //  如果父节点为根节点
                *TreeRoot = Node->lchild;   // 树根指针指向其左子树
            } else if (ParentNode->lchild == Node) {    // 如果为父节点的左子树
                ParentNode->lchild = Node->lchild;  //  父节点的左指针指向该节点的左孩子
            } else {    // 如果为父节点的右子树
                ParentNode->rchild = Node->lchild;  //  父节点的右指针指向该节点的右孩子
            }
            free(Node);     //  释放待删除节点
        } else { // 判断含有左右子树
            BSTreeP minParentNode = Node;
            // 查找右子树的最小值，来替换它
            BSTreeP minNode = Node->rchild;
            while (minNode->lchild != NULL) { // 判断是否为最小值，若是则停止，否则继续迭代查找最小值
                minParentNode = minNode;    //  记录最小值节点的父节点
                minNode = minNode->lchild;  //  记录最小值节点
            }
            Node->data = minNode->data;
            if (minParentNode != Node) { // 进了while，最小值节点为待删除节点右子树的最左节点
                minParentNode->lchild = minNode->rchild;    // 最小值父节点的左指针指向最小值节点的右子树
            } else {    // 没进while，最小值节点为待删除节点的右节点
                minParentNode->rchild = minNode->rchild;    // 最小值父节点的右指针指向最小值节点的右子树
            }
            free(minNode);  //  释放待删除节点
        }
    }
}

// 改变某节点
void ChangeBST(BSTreeP TreeRoot, int oldValue, int newValue) {
    BSTreeP Node = NULL, ParentNode = NULL;
    if (SearchBST(TreeRoot, oldValue, &Node, &ParentNode) == 0) {
        printf("fail, not exit");
        return;
    } else {
        Node->data = newValue;
    }
}

// 搜索排序二叉树
int SearchBST(BSTreeP TreeRoot, int value, BSTreeP *Node, BSTreeP *ParentNode) {
    // 在根指针bt所指二叉排序树中递归地查找关键字等于key的结点，若查找成功，指针Node指向该结点，并返回1；否则指针Node指向查找路径最后一个
    // 访问结点并返回0,指针ParentNode指向bt的双亲，初始调用时值为NULL
    if (TreeRoot == NULL) { // 查找失败
        *Node = *ParentNode;
        return 0;
    } else if (value == TreeRoot->data) { // 查找成功
        *Node = TreeRoot;
        return 1;
    } else if (value < TreeRoot->data) { // 左子树继续查找
        *ParentNode = TreeRoot;
        return SearchBST(TreeRoot->lchild, value, Node, ParentNode);
    } else { // 右子树继续查找
        *ParentNode = TreeRoot;
        return SearchBST(TreeRoot->rchild, value, Node, ParentNode);
    }
}

// 创建一个完全二叉树
void CBTreeInsertNode(BSTreeP *TreeRoot, DataType value) {
    // 新建一个节点
    BSTreeP NodeP = InitNode(value);
    // 如果树根还没有创建则将该新建的节点赋值给根
    if (*TreeRoot == NULL) {
        *TreeRoot = NodeP;
        return;
    }
    int length = CountBiNode(*TreeRoot);

    int front = -1, rear = 0;
    BSTreeP Queue[length]; // 定义队列
    Queue[rear] = *TreeRoot; // 根结点入队列
    while (rear != length) { // 若队列不空，继续遍历。否则，遍历结束
        front++; // 出队
        if (Queue[front]->lchild != NULL && rear != length) { // 如果有左孩子，左孩子入队
            rear++;
            Queue[rear] = Queue[front]->lchild;
        }
        if (Queue[front]->rchild != NULL && rear != length) { // 如果有右孩子，右孩子入队
            rear++;
            Queue[rear] = Queue[front]->rchild;
        }
        if (front == length - 1) {
            if (Queue[front]->lchild != NULL && Queue[front]->rchild == NULL) {
                Queue[front]->rchild = NodeP;
            }
            if (Queue[front]->lchild == NULL) {
                Queue[front]->lchild = NodeP;
            }
            break;
        }
    }
}

// 交换左右子树
void Exchange(BSTreeP TreeRoot) {
    if (TreeRoot == NULL) return;
    if (TreeRoot->lchild == NULL && TreeRoot->rchild == NULL)return;
    BSTreeP temp = TreeRoot->lchild;
    TreeRoot->lchild = TreeRoot->rchild;
    TreeRoot->rchild = temp;
    Exchange(TreeRoot->lchild);
    Exchange(TreeRoot->rchild);
}

// 求树的深度
int Depth(BSTreeP TreeRoot) {
    if (TreeRoot == NULL) return 0;
    return 1 + max(Depth(TreeRoot->lchild), Depth(TreeRoot->rchild));
}

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

// 计算节点总数
int CountBiNode(BSTreeP TreeRoot) {
    if (TreeRoot == NULL) return 0;
    int left = CountBiNode(TreeRoot->lchild),
            right = CountBiNode(TreeRoot->rchild);
    return left + right + 1;
}

// 计算叶子总数
int CountLeaf(BSTreeP TreeRoot) {
    if (TreeRoot == NULL) return 0;
    if (TreeRoot->rchild == NULL && TreeRoot->lchild == NULL) return 1;
    return (CountLeaf(TreeRoot->lchild) + CountLeaf(TreeRoot->rchild));
}

// 层次遍历
void LevelOrder(BSTreeP TreeRoot) {
    BSTreeP Queue[MaxSize]; // 定义队列
    int front = -1, rear = 0;
    if (TreeRoot == NULL) return; // 空二叉树，遍历结束
    Queue[rear] = TreeRoot; // 根结点入队列
    while (rear != front) { // 若队列不空，继续遍历。否则，遍历结束
        front++; // 出队
        NodeVisit(Queue[front]->data); // 访问刚出队的元素
        if (Queue[front]->lchild != NULL) { // 如果有左孩子，左孩子入队
            rear++;
            Queue[rear] = Queue[front]->lchild;
        }
        if (Queue[front]->rchild != NULL) { // 如果有右孩子，右孩子入队
            rear++;
            Queue[rear] = Queue[front]->rchild;
        }
    }
}


// 后序遍历
void PostOrder(BSTreeP TreeRoot) {
    if (TreeRoot != NULL) {
        PostOrder(TreeRoot->lchild);
        PostOrder(TreeRoot->rchild);
        NodeVisit(TreeRoot->data);
    }
}

// 中序遍历
void InOrder(BSTreeP TreeRoot) {
    if (TreeRoot != NULL) {
        InOrder(TreeRoot->lchild);
        NodeVisit(TreeRoot->data);
        InOrder(TreeRoot->rchild);
    }
}

// 前序遍历
void PreOrder(BSTreeP TreeRoot) {
    if (TreeRoot != NULL) {
        NodeVisit(TreeRoot->data);
        PreOrder(TreeRoot->lchild);
        PreOrder(TreeRoot->rchild);
    }
}

// 打印值
void NodeVisit(DataType data) {
    printf("%d ", data);
}

void BSTreeInsertNode(BSTreeP *TreeRoot, DataType data) {
    // 新建一个节点
    BSTreeP NodeP = InitNode(data);
    // 如果树根还没有创建则将该新建的节点赋值给根
    if (*TreeRoot == NULL) {
        *TreeRoot = NodeP;
    } // 新插入的节点数值比根小或等，走根的左边
    else if (data <= (*TreeRoot)->data) {
        // 左子树递归结束处
        if ((*TreeRoot)->lchild == NULL) {
            (*TreeRoot)->lchild = NodeP;
        } else { // 左递归
            BSTreeInsertNode(&((*TreeRoot)->lchild), data);
        }
    } else {
        // 右子树递归结束处
        if ((*TreeRoot)->rchild == NULL) {
            (*TreeRoot)->rchild = NodeP;
        } else { // 右递归
            BSTreeInsertNode(&((*TreeRoot)->rchild), data);
        }
    }
}

BSTreeP InitNode(DataType data) {
    BSTreeP NodeP = (BSTreeP) malloc(sizeof(BSTree));
    NodeP->data = data;
    NodeP->lchild = NodeP->rchild = NULL;
    return NodeP;
}

