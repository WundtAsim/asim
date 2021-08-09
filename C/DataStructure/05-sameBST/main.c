#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
typedef struct node {
    int v;
    struct node *left, *right;
    int flag;  //标志域，1代表被访问过
} Node, *Tree;

//函数声明
Tree MakeTree(int N);
int Judge(Tree T, int N);
Tree NewNode(int V);
Tree Insert(Tree T, int V);
int check(Tree T, int V);
void ResetT(Tree T);
void FreeTree(Tree T);

int main() {
    int N, L, i;
    Tree T;

    scanf("%d", &N);
    while (N) {
        scanf("%d", &L);
        T = MakeTree(N);
        for (int i = 0; i < L; i++) {
            if (Judge(T, N))
                printf("Yes\n");
            else
                printf("No\n");
            ResetT(T);  //清楚T中标记flag
        }
        FreeTree(T);
        scanf("%d", &N);
    }
    return 0;
}

Tree MakeTree(int N) {
    Tree T;
    int i, V;

    scanf("%d", &V);
    T = NewNode(V);
    for (i = 1; i < N; i++) {
        scanf("%d", &V);
        T = Insert(T, V);
    }
    return T;
}
Tree NewNode(int V) {
    Tree T = (Tree)malloc(sizeof(Node));
    T->v = V;
    T->left = NULL;
    T->right = NULL;
    T->flag = 0;
    return T;
}
Tree Insert(Tree T, int V) {
    if (T == NULL)
        T = NewNode(V);
    else {
        if (V > T->v)
            T->right = Insert(T->right, V);
        else
            T->left = Insert(T->left, V);
    }
    return T;
}

int check(Tree T, int V) {
    // flag = 1表示被访问过，继续下一个判断
    if (T->flag == 1) {
        if (V < T->v)
            return check(T->left, V);
        else if (V > T->v)
            return check(T->right, V);
        else
            return 0;
    } else {
        if (V == T->v) {
            T->flag = 1;
            return 1;
        } else
            return 0;
    }
}
int Judge(Tree T, int N) {
    // flag: 0代表目前还一致，1代表已经不一致了
    int i, V, flag = 0;

    scanf("%d", &V);
    if (V != T->v)
        flag = 1;
    else
        T->flag = 1;
    for (i = 1; i < N; i++) {
        scanf("%d", &V);
        if ((flag == 0) && (0 == check(T, V)))
            flag = 1;
    }
    if (flag)
        return 0;
    else
        return 1;
}
void ResetT(Tree T) {
    if (T->left)
        ResetT(T->left);
    if (T->right)
        ResetT(T->right);
    T->flag = 0;
}
void FreeTree(Tree T) {
    if (T->left)
        FreeTree(T->left);
    if (T->right)
        FreeTree(T->right);
    free(T);
}