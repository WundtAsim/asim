#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define elemtype char
#define Maxtree 10
#define NON -1
typedef struct Node {
    elemtype data;
    int lchild, rchild;
} Node, *Tree;

//函数声明
int build_tree(Tree p);
bool ishomo(int head1, Tree t1, int head2, Tree t2);
void PreOrder(int head, Tree t);
void LevelOrder(int head, Tree t);
void visit(Node* p);
void eatline();
typedef struct Qnode {
    elemtype data;
    struct Qnode* next;
} Qnode;
typedef struct Queue {
    Qnode *front, rear;
} Queue;
Queue* Init_queue();
bool Isempty(Queue* q);
void EnQueue(Queue* q, elemtype x);
void DeQueue(Queue* q, elemtype* x);

int main() {
    Node T1[Maxtree], T2[Maxtree];
    int head1, head2;
    head1 = build_tree(T1);
    /*head2 = build_tree(T2);
    if (ishomo(head1, T1, head2, T2))
        printf("Yes\n");
    else
        printf("No\n");*/
    // PreOrder(head1, T1);
    LevelOrder(head1, T1);
    return 0;
}

int build_tree(Tree p) {
    int N;
    scanf("%d", &N);
    char left, right;
    int* check;
    check = (int*)malloc(sizeof(int) * N);
    for (int i = 0; i < N; i++)
        check[i] = 0;  // 0代表链表对应元素未被指向，即root

    for (int i = 0; i < N; i++) {
        scanf(" %c %c %c", &p[i].data, &left, &right);
        //分别对左孩和右孩进行处理，如果有孩子，孩子的check置为1，即不是root
        if (left != '-') {
            (p + i)->lchild = left - '0';
            check[p[i].lchild] = 1;
        } else
            p[i].lchild = NON;
        if (right != '-') {
            p[i].rchild = right - '0';
            check[p[i].rchild] = 1;
        } else
            p[i].rchild = NON;
    }
    int Root;  //根位置
    for (int i = 0; i < N; i++) {
        if (check[i] == 0) {
            Root = i;
            break;
        }
    }
    return Root;
}

void PreOrder(int head, Tree t) {
    Node* p = t + head;
    if (head != NON) {
        visit(p);
        PreOrder(p->lchild, t);
        PreOrder(p->rchild, t);
    }
}
void visit(Node* p) {
    printf("%c->>", p->data);
}
void eatline() {
    while (getchar() != '\n')
        continue;
}

void LevelOrder(int head, Tree t) {
    Queue* q = Init_queue();
    elemtype x;
    while (!Isempty(q)) {
        DeQueue(q, &x);
        printf("%c->", x);
        if (t[head].lchild != NON)
            EnQueue(q, t[head].lchild->data);
        if (t[head].rchild != NON)
            EnQueue(q, t[head].rchild->data);
    }
}
Queue* Init_queue() {
    Queue* p = (Queue*)malloc(sizeof(Queue));
    p->front = p->rear = (Qnode*)malloc(sizeof(Qnode));
    p->front->next = NULL;
    return p;
}
bool Isempty(Queue* q) {
    if (q->front == q->rear)
        return true;
    else
        return false;
}
void EnQueue(Queue* q, elemtype x) {
    Qnode* s = (Qnode*)malloc(sizeof(Qnode));
    s->data = x;
    s->next = NULL;
    q->rear->next = s;
    q->rear = s;
}
void DeQueue(Queue* q, elemtype* x) {
    if (Isempty(q))
        return false;
    Qnode* new = q->front->next;
    *x = new->data;
    q->front->next = new->next;
    if (new == q->rear)  //若原队列只有一个，删除后变空
        q->rear = q->front;
    free(new);
    return true;
}

bool ishomo(int head1, Tree t1, int head2, Tree t2) {
    ;
}
