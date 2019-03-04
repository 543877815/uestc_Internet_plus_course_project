//
// Created by PC on 2018/10/27.
//
#include <stdio.h>
#include <stdlib.h>

#define MaxSize 100

typedef int DataType;

// 平衡二叉树
typedef struct AVLNode {
    DataType data;
    int bf; // 平衡因子
    struct AVLNode *lchild, *rchild;
} AVLTree, *AVLTreeP;

AVLTreeP InitNode(DataType value);  // AVL节点的初始化

void AVLInsertNode(AVLTreeP *TreeRoot, DataType data);  // AVL树的插入

int getRchildMin(AVLTreeP *TreeRoot);    //  返回右子树的最小值

int updateBF(AVLTreeP *TreeRoot);     //  更新平衡因子

AVLTreeP DeleteAVL(AVLTreeP *TreeRoot, int data);   // AVL树的删除

void AVLTreeFix(AVLTreeP *TreeRoot, int data, int type);    //  将二叉排序树调整为平衡二叉树

int SearchAVL(AVLTreeP TreeRoot, int value, AVLTreeP *Node, AVLTreeP *ParentNode); // AVL树的查找

int GetHeight(AVLTreeP TreeRoot);   // 获取树的高度

void LL_Rotation(AVLTreeP *TreeRoot);   // LL型调整

void LR_Rotation(AVLTreeP *TreeRoot);   // LR型调整

void RR_Rotation(AVLTreeP *TreeRoot);   // RR型调整

void RL_Rotation(AVLTreeP *TreeRoot);   // RL型调整

void LevelOrder(AVLTreeP TreeRoot);    // 层次遍历

void InOrder(AVLTreeP TreeRoot);    // 中序遍历

void NodeVisit(DataType data);  // 打印值

int max(int a, int b);  // 返回最大值


void createDotFile(char *fileName, AVLTreeP TreeRoot);

int main() {
    FILE *fp = fopen("./data/data.txt", "r+");
    if (fp == NULL)
        exit(0x01);
    AVLTreeP AVLTree = NULL;
    DataType keynumber;
    //    DataType A[8] = {10, 5, 12, 4, 6, 11, 13, 1};
    //    for (int i = 0; i < size; i++) {
    //        AVLInsertNode(&AVLTree, A[i]);
    //    }
    while (EOF != fscanf(fp, "%d", &keynumber)) {
        AVLInsertNode(&AVLTree, keynumber);
    }
    fclose(fp);
    createDotFile("./dotFile/AVL.dot", AVLTree);
    system("dot -Tpng ./dotFile/AVL.dot -o ./dotFile/AVL.png");

    // 层次遍历
    LevelOrder(AVLTree);
    printf("-->LevelOrder\n");

    // 中序遍历
    InOrder(AVLTree);
    printf("-->InOrder\n");

    // 查找某节点
    int value = 20;
    AVLTreeP ParentNode = NULL, Node = NULL;
    int result = SearchAVL(AVLTree, value, &Node, &ParentNode);
    if (Node != NULL) {
        printf("result: %d, value is: %d", result, Node->data);
    } else {
        printf("result: %d", result);
    }
    printf("\n");

    // 删除某节点
    DeleteAVL(&AVLTree, 269);
    DeleteAVL(&AVLTree, 288);
    DeleteAVL(&AVLTree, 367);
    DeleteAVL(&AVLTree, 272);
    //    DeleteAVL(&AVLTree, 20);
    //    DeleteAVL(&AVLTree, 18);
    createDotFile("./dotFile/AVL_Delete_RL.dot", AVLTree);
    system("dot -Tpng ./dotFile/AVL_Delete_RL.dot -o ./dotFile/AVL_Delete_RL.png");

    DeleteAVL(&AVLTree, 250);
    DeleteAVL(&AVLTree, 418);
    DeleteAVL(&AVLTree, 466);
    DeleteAVL(&AVLTree, 382);
    DeleteAVL(&AVLTree, 470);
    createDotFile("./dotFile/AVL_Delete_LR.dot", AVLTree);
    system("dot -Tpng ./dotFile/AVL_Delete_LR.dot -o ./dotFile/AVL_Delete_LR.png");

    DeleteAVL(&AVLTree, 697);
    createDotFile("./dotFile/AVL_Delete_RR.dot", AVLTree);
    system("dot -Tpng ./dotFile/AVL_Delete_RR.dot -o ./dotFile/AVL_Delete_RR.png");

    DeleteAVL(&AVLTree, 678);
    createDotFile("./dotFile/AVL_Delete_LL.dot", AVLTree);
    system("dot -Tpng ./dotFile/AVL_Delete_LL.dot -o ./dotFile/AVL_Delete_LL.png");

    LevelOrder(AVLTree);
    printf("-->LevelOrder\n");
    InOrder(AVLTree);
    printf("-->DeleteBST InOrder\n");

    return 0;
}

void createDotFile(char *fileName, AVLTreeP TreeRoot) {
    FILE *fp = fopen(fileName, "w");
    if (fp == NULL) {
        printf("File cannot open!");
        exit(0);
    }
    fprintf(fp, "digraph G {\n");

    // 利用层次遍历构造
    AVLTreeP Queue[MaxSize]; // 定义队列
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

    fprintf(fp, "}\n");
    fclose(fp);
}

//  返回右子树的最小值
int getRchildMin(AVLTreeP *TreeRoot) {
    if ((*TreeRoot)->lchild == NULL) {
        return (*TreeRoot)->data;
    } else {
        return getRchildMin(&((*TreeRoot)->lchild));
    }
}

// AVL删除节点，参考自 https://blog.csdn.net/pjmike233/article/details/81545136
AVLTreeP DeleteAVL(AVLTreeP *TreeRoot, int data) {
    if (TreeRoot == NULL) {
        return NULL;
    }
    if (data < (*TreeRoot)->data) { // 左递归
        (*TreeRoot)->lchild = DeleteAVL(&((*TreeRoot)->lchild), data);
    } else if (data > (*TreeRoot)->data) {  // 右递归
        (*TreeRoot)->rchild = DeleteAVL(&((*TreeRoot)->rchild), data);
    } else {  // 找到待删除的节点
        if ((*TreeRoot)->lchild != NULL && (*TreeRoot)->rchild != NULL) {  // 删除的节点有两个孩子
            (*TreeRoot)->data = getRchildMin(&((*TreeRoot)->rchild));   // 找到右子树的最小值节点并替换该值
            (*TreeRoot)->rchild = DeleteAVL(&((*TreeRoot)->rchild), (*TreeRoot)->data);   // 删除右子树的最小值节点
        } else {    // 删除的节点只有一个孩子或者没有孩子
            AVLTreeP temp = *(TreeRoot);
            (*TreeRoot) = ((*TreeRoot)->lchild != NULL) ? (*TreeRoot)->lchild : (*TreeRoot)->rchild;    // 判断删除是否为左孩子，若是则赋给左孩子，否则赋给右孩子
            free(temp); // 释放空间
        }
    }
    // 恢复二叉树的平衡
    if (*TreeRoot == NULL) {    //  如果根为NULL，则返回NULL
        return *TreeRoot;
    }
    (*TreeRoot)->bf = updateBF(&(*TreeRoot));    // 更新权重
    AVLTreeFix(&(*TreeRoot), data, 0);  //  恢复二叉树的平衡性
    return *TreeRoot;
}

//  将二叉排序树调整为平衡二叉树
void AVLTreeFix(AVLTreeP *TreeRoot, int data, int type) {
    if (type == 1) { // 插入后进行调整
        if (updateBF(&(*TreeRoot)) >= 2) {  // 如果左子树高度比右子树高度大2
            if (data < (*TreeRoot)->lchild->data) { // 如果是插入在左孩子的左子树，做LL调整
                LL_Rotation(&(*TreeRoot));
            } else {                                // 如果是插入在左孩子的右子树，做LR调整
                LR_Rotation(&(*TreeRoot));
            }
        }
        if (updateBF(&(*TreeRoot)) <= -2) { // 如果右子树高度比左子树高度大2
            if (data > (*TreeRoot)->rchild->data) { // 如果是插入在右孩子的右子树，做RR调整
                RR_Rotation(&(*TreeRoot));
            } else {                                // 如果是插入在右孩子的左子树，做RL调整
                RL_Rotation(&(*TreeRoot));
            }
        }
    }
    if (type == 0) { // 删除后进行调整
        if (updateBF(&(*TreeRoot)) >= 2) {  // 如果左子树高度比右子树高度大2
            // 删除与插入要判断的符号逆向
            if (updateBF(&((*TreeRoot)->lchild)) <= -1) { // 如果是删除左孩子的左子树，做LR调整
                LR_Rotation(&(*TreeRoot));
            } else {                                // 如果是删除左孩子的右子树，做LL调整
                LL_Rotation(&(*TreeRoot));
            }
        }
        if (updateBF(&(*TreeRoot)) <= -2) { // 如果右子树高度比左子树高度大2
            if (updateBF(&((*TreeRoot)->rchild)) >= 1) { // 如果是删除右孩子的右子树，做RL调整
                RL_Rotation(&(*TreeRoot));
            } else {                                // 如果是删除右孩子的左子树，做RR调整
                RR_Rotation(&(*TreeRoot));
            }
        }
    }
}

// 中序遍历
void InOrder(AVLTreeP TreeRoot) {
    if (TreeRoot != NULL) {
        InOrder(TreeRoot->lchild);
        NodeVisit(TreeRoot->data);
        InOrder(TreeRoot->rchild);
    }
}

// 搜索AVL树
int SearchAVL(AVLTreeP TreeRoot, int value, AVLTreeP *Node, AVLTreeP *ParentNode) {
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
        return SearchAVL(TreeRoot->lchild, value, Node, ParentNode);
    } else { // 右子树继续查找
        *ParentNode = TreeRoot;
        return SearchAVL(TreeRoot->rchild, value, Node, ParentNode);
    }
}

// 层次遍历
void LevelOrder(AVLTreeP TreeRoot) {
    AVLTreeP Queue[MaxSize]; // 定义队列
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

void NodeVisit(DataType data) {
    printf("%d ", data);
}

int max(int a, int b) {
    if (a > b) return a;
    return b;
}

// 求树的深度
int GetHeight(AVLTreeP TreeRoot) {
    if (TreeRoot == NULL) return 0;
    return 1 + max(GetHeight(TreeRoot->lchild), GetHeight(TreeRoot->rchild));
}

// 计算节点的平衡因子
int updateBF(AVLTreeP *TreeRoot) {
    return GetHeight((*TreeRoot)->lchild) - GetHeight((*TreeRoot)->rchild);
}

// 平衡二叉树插入节点
void AVLInsertNode(AVLTreeP *TreeRoot, DataType data) {
    // 新建一个节点
    AVLTreeP NodeP = InitNode(data);
    // 如果树根还没有创建则将该新建的节点赋值给根
    if (*TreeRoot == NULL) {
        *TreeRoot = NodeP;
    } else if (data <= (*TreeRoot)->data) { // 新插入的节点数值比根小或等，走根的左边
        // 左子树递归结束处
        if ((*TreeRoot)->lchild == NULL) {
            (*TreeRoot)->lchild = NodeP;
        } else { // 左递归
            AVLInsertNode((&(*(TreeRoot))->lchild), data);
            AVLTreeFix(&(*TreeRoot), data, 1);
        }
    } else {
        // 右子树递归结束处
        if ((*TreeRoot)->rchild == NULL) {
            (*TreeRoot)->rchild = NodeP;
        } else { // 右递归
            AVLInsertNode((&(*TreeRoot)->rchild), data);
            AVLTreeFix(&(*TreeRoot), data, 1);
        }
    }
    (*TreeRoot)->bf = updateBF(&(*TreeRoot)); // 树高等于子树高度加一
}

// 先右旋，后左旋
void RL_Rotation(AVLTreeP *TreeRoot) {
    LL_Rotation(&((*TreeRoot)->rchild));
    RR_Rotation(&(*TreeRoot));
}

// 右旋转
void RR_Rotation(AVLTreeP *TreeRoot) {
    AVLTreeP temp = (*TreeRoot)->rchild;
    (*TreeRoot)->rchild = temp->lchild;
    temp->lchild = *TreeRoot;
    *TreeRoot = temp;
    (*TreeRoot)->bf = max(GetHeight((*TreeRoot)->lchild), GetHeight((*TreeRoot)->rchild));
    temp->bf = max(GetHeight(temp->lchild), GetHeight(temp->rchild));
}

// 先左旋，后右旋
void LR_Rotation(AVLTreeP *TreeRoot) {
    RR_Rotation(&((*TreeRoot)->lchild));
    LL_Rotation(&(*TreeRoot));
}

// 左旋转
void LL_Rotation(AVLTreeP *TreeRoot) {
    AVLTreeP temp = (*TreeRoot)->lchild;
    (*TreeRoot)->lchild = temp->rchild;
    temp->rchild = *TreeRoot;
    *TreeRoot = temp;
    (*TreeRoot)->bf = max(GetHeight((*TreeRoot)->lchild), GetHeight((*TreeRoot)->rchild));
    temp->bf = max(GetHeight(temp->lchild), GetHeight(temp->rchild));
}

// 初始一个空节点
AVLTreeP InitNode(DataType value) {
    AVLTreeP Node = (AVLTreeP) malloc(sizeof(AVLTree)); // 分配内存
    Node->data = value; // 赋值
    Node->bf = 0;   // 初始平衡因子为0
    Node->lchild = Node->rchild = NULL; //  左右指针指向NULL
    return Node;
}