//
// Created by PC on 2018/11/8.
//

#include <stdio.h>
#include <stdlib.h>

typedef int DataType;
typedef struct TTNode {
    struct TTNode *lchild, *rchild;
    int ltag;
    int rtag;
    DataType data;
} TTNode, *TTNodeP;

TTNodeP pre; // 全局变量，记录前驱

void NodeVisit(DataType data);      // 打印值

void InOrder(TTNodeP TreeRoot);     // 中序遍历

void TTreeInsertNode(TTNodeP *TreeRoot, DataType data);

TTNodeP initNode(DataType data);

void Inthread(TTNodeP TreeRoot);

TTNodeP InPre(TTNodeP Node);

TTNodeP InNext(TTNodeP Node);

TTNodeP TinFirst(TTNodeP Node);

void TinOrder(TTNodeP TreeRoot);

#define size 11

int main() {
    TTNodeP TTree = NULL;
    DataType A[size] = {1, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
    for (int i = 0; i < size; ++i) {
        TTreeInsertNode(&TTree, A[i]);
    }
    // 中序遍历
    InOrder(TTree);
    printf("-->InOrder\n");

    pre = NULL;
    Inthread(TTree);

    TTNodeP p = TTree->rchild->lchild->lchild;

    TTNodeP q = InPre(p);
    if (q != NULL) {
        printf("\n前驱为%d", q->data);
    } else {
        printf("\n前驱为NULL");
    }

    q = InNext(p);
    if (q != NULL) {
        printf("\n后继为%d", q->data);
    } else {
        printf("\n后继为NULL");
    }

    q = TinFirst(TTree);
    printf("\n第一个结点为%d", q->data);

    printf("\n");
    TinOrder(TTree);

    return 0;
}

// 根据节点打印
void TinOrder(TTNodeP TreeRoot) {
    if (TreeRoot == NULL) {
        return;
    }
    do{
        printf("%d ", TreeRoot->data);
        TreeRoot = InNext(TreeRoot);
    }while (TreeRoot!= NULL);
}

// 返回中序遍历的第一个节点
TTNodeP TinFirst(TTNodeP Node) {
    if (Node == NULL) {
        return NULL;
    }
    while (Node->lchild != NULL && Node->ltag == 0) {
        Node = Node->lchild;
    }
    return Node;
}

// 返回节点的后继
TTNodeP InNext(TTNodeP Node) {
    if (Node == NULL) {
        return NULL;
    }
    if (Node->rtag == 1) {
        return Node->rchild;
    } else {
        if (Node->rchild != NULL) {
            Node = Node->rchild;
            while (Node->lchild != NULL && Node->ltag == 0) {
                Node = Node->lchild;
            }
        } else {
            return NULL;
        }
    }
    return Node;
}

// 返回节点的前驱
TTNodeP InPre(TTNodeP Node) {
    if (Node == NULL) {
        return NULL;
    }
    pre = NULL;
    if (Node->ltag == 1) {
        return Node->lchild;
    } else {
        Node = Node->lchild;
        while (Node->rchild != NULL && Node->rtag == 0) {
            Node = Node->rchild;
            pre = Node;
        }
    }
    return pre;
}

// 中序线索化
void Inthread(TTNodeP TreeRoot) {
    if (TreeRoot != NULL) { // 不为NULL才能继续
        Inthread(TreeRoot->lchild);
        if (TreeRoot->lchild == NULL) { // 如果该节点左孩子为空，则lchild指其向前驱
            TreeRoot->ltag = 1;
            TreeRoot->lchild = pre;
        }
        if (pre != NULL && pre->rchild == NULL) { // 如果前驱右孩子为空，则其rhild指向该节点
            pre->rtag = 1;
            pre->rchild = TreeRoot;
        }
        pre = TreeRoot; // 访问右子树的时候会改变前驱
        Inthread(TreeRoot->rchild);
    }
}

// 按照二叉排序树的算法生成该线索二叉树，这样待会遍历比较好判断对错
void TTreeInsertNode(TTNodeP *TreeRoot, DataType data) {
    // 新建一个节点
    TTNodeP Node = initNode(data);
    // 如果树根还没有创建则将该新建的节点赋值给根
    if (*TreeRoot == NULL) {
        *TreeRoot = Node;
    } // 新插入的节点数值比根小或等，走根的左边
    else if (data <= (*TreeRoot)->data) {
        // 左子树递归结束处
        if ((*TreeRoot)->lchild == NULL) {
            (*TreeRoot)->lchild = Node;
        } else { // 左递归
            TTreeInsertNode(&((*TreeRoot)->lchild), data);
        }
    } else {
        // 右子树递归结束处
        if ((*TreeRoot)->rchild == NULL) {
            (*TreeRoot)->rchild = Node;
        } else { // 右递归
            TTreeInsertNode(&((*TreeRoot)->rchild), data);
        }
    }
}

// 中序遍历
void InOrder(TTNodeP TreeRoot) {
    if (TreeRoot != NULL) {
        if (TreeRoot->ltag == 0) {
            InOrder(TreeRoot->lchild);
        }
        NodeVisit(TreeRoot->data);
        if (TreeRoot->rtag == 0) {
            InOrder(TreeRoot->rchild);
        }
    }
}

// 节点初始化
TTNodeP initNode(DataType data) {
    TTNode *L = (TTNode *) malloc(sizeof(TTNode));
    L->lchild = L->rchild = NULL;
    L->ltag = L->rtag = 0;
    L->data = data;
    return L;
}

// 打印值
void NodeVisit(DataType data) {
    printf("%d ", data);
}