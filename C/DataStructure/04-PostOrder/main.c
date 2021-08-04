// Tree traversal again
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Max 30
int pre[Max], in[Max], post[Max];

typedef struct node {
    int data;
    struct node* next;
} Node, *Stack;
typedef struct tnode {
    int data;
    struct tnode *lchild, *rchild;
} TNode, *Tree;

//函数声明
Stack Init_stack();
void push(Stack S, int x);
bool pop(Stack S, int* x);
bool isempty(Stack S);
void buildTree(int N);
void PostTree(int N);

//主函数
int main() {
    int N;
    scanf("%d", &N);
    buildTree(N);
    PostTree(N);
    return 0;
}

//函数定义
Stack Init_stack() {
    Stack p = (Stack)malloc(sizeof(Node));
    p->next = NULL;
    return p;
}
void push(Stack S, int x) {
    Node* p = (Node*)malloc(sizeof(Node));
    p->data = x;
    p->next = S->next;
    S->next = p;
}
bool pop(Stack S, int* x) {
    if (isempty(S))
        return false;
    Node* p = S->next;
    *x = p->data;
    S->next = p->next;
    free(p);
    return true;
}
bool isempty(Stack S) {
    if (S->next == NULL)
        return true;
    else
        return false;
}

void buildTree(int N) {
    Stack S = Init_stack();

    int index_in = 0;   //中序数组角标
    int index_pre = 0;  //前序数组角标
    for (int i = 0; i < 2 * N; i++) {
        char order[5];
        int data;
        scanf("%s", order);
        if (strcmpi(order, "Push") == 0) {
            scanf("%d", &data);
            pre[index_pre++] = data;
            push(S, data);
        } else {
            pop(S, in + index_in);
            index_in++;
        }
    }
    return;
}
void PostTree(int N) {
    if (N == 0)
        return;
    if (N == 1)
        post[0] = in[0];
    else {
    }
}