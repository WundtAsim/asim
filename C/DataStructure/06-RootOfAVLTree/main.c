#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int data;
    struct node *lchild, *rchild;
    int height;
} Node, *Tree;

//函数声明
Tree BuildTree(int N);          //根据输入建立树
Tree Insert(Tree T, int data);  //在树中插入新节点
Tree NewNode(int data);         //新建结点
int GetLevel(Tree T);           //获得本树层数
Tree LLrotation(Tree T);        // LL旋转
Tree LRrotation(Tree T);        // LR旋转
Tree RRrotation(Tree T);        // RR旋转
Tree RLrotation(Tree T);        // RL旋转

//主函数
int main() {
    int N;
    scanf("%d", &N);
    Tree T = BuildTree(N);
    printf("%d", T->data);
    return 0;
}

Tree BuildTree(int N) {
    int i, data;
    scanf("%d", &data);
    Tree T = NewNode(data);

    for (i = 1; i < N; i++) {
        scanf("%d", &data);
        T = Insert(T, data);
    }
    return T;
}
Tree NewNode(int data) {
    Tree T = (Tree)malloc(sizeof(Node));
    T->data = data;
    T->lchild = NULL;
    T->rchild = NULL;
    T->height = 0;
    return T;
}
Tree Insert(Tree T, int data) {
    if (T == NULL)
        T = NewNode(data);
    else {
        if (data < T->data) {
            /*插入左子树*/
            T->lchild = Insert(T->lchild, data);
            /* 如果需要左旋 */
            if (GetLevel(T->lchild) - GetLevel(T->rchild) == 2)
                if (data < T->lchild->data)
                    T = LLrotation(T); /* 左单旋 */
                else
                    T = LRrotation(T); /* 左-右双旋 */
        }

        else if (data > T->data) {
            //插入右子树
            T->rchild = Insert(T->rchild, data);
            /* 如果需要右旋 */
            if (GetLevel(T->lchild) - GetLevel(T->rchild) == -2)
                if (data > T->rchild->data)
                    T = RRrotation(T); /* 右单旋 */
                else
                    T = RLrotation(T); /* 右-左双旋 */
        }
    }

    /* 别忘了更新树高 */
    int L = GetLevel(T->lchild);
    int R = GetLevel(T->rchild);
    T->height = L > R ? L + 1 : R + 1;
    return T;
}

int GetLevel(Tree T) {
    if (T) {
        int l = GetLevel(T->lchild);
        int r = GetLevel(T->rchild);
        return l > r ? l + 1 : r + 1;
    } else
        return 0;
}

Tree LLrotation(Tree T) {
    //右单旋转，需保障有左孩子
    Tree root = T->lchild;
    T->lchild = root->rchild;
    root->rchild = T;
    int TL = GetLevel(T->lchild);
    int TR = GetLevel(T->rchild);
    T->height = TL >= TR ? TL + 1 : TR + 1;

    int RL = GetLevel(root->lchild);
    int RR = GetLevel(root->rchild);
    root->height = RL >= RR ? RL + 1 : RR + 1;

    return root;
}
Tree RRrotation(Tree T) {
    //需保障T有右孩子
    Tree root = T->rchild;
    T->rchild = root->lchild;
    root->lchild = T;
    int TL = GetLevel(T->lchild);
    int TR = GetLevel(T->rchild);
    T->height = TL >= TR ? TL : TR;

    int RL = GetLevel(root->lchild);
    int RR = GetLevel(root->rchild);
    root->height = RL >= RR ? RL : RR;

    return root;
}
Tree LRrotation(Tree T) {
    /* T必须有一个左子结点B，且B必须有一个右子结点C
           将T、B与C做两次单旋，返回新的根结点C */

    /* 将B与C做RR旋转，C被返回 */
    T->lchild = RRrotation(T->lchild);
    /* 将T与C做左单旋，C被返回 */
    return LLrotation(T);
}
Tree RLrotation(Tree T) {
    /* T必须有一个右子结点B，且B必须有一个左子结点C
        将T、B与C做两次单旋，返回新的根结点C */

    /* 将B与C做LL旋转，C被返回 */
    T->rchild = LLrotation(T->rchild);
    /* 将T与C做左单旋，C被返回 */
    return RRrotation(T);
}