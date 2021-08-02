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
bool isomorphic(int head1, Tree t1, int head2, Tree t2);
void PreOrder(int head, Tree t);
void LevelOrder(int head, Tree t);
void visit(Node* p);
void eatline();
typedef struct Qnode {
    Node* current;
    struct Qnode* next;
} Qnode;
typedef struct Queue {
    Qnode *front, *rear;
} Queue;
Queue* Init_queue();
bool Isempty(Queue* q);
void EnQueue(Queue* q, Node* x);
bool DeQueue(Queue* q, Qnode* x);

int main() {
    Node T1[Maxtree], T2[Maxtree];
    int head1, head2;
    head1 = build_tree(T1);
    head2 = build_tree(T2);
    if (isomorphic(head1, T1, head2, T2))
        printf("Yes\n");
    else
        printf("No\n");
    // PreOrder(head1, T1);
    // LevelOrder(head1, T1);
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
    int Root = -1;  //根位置
    for (int i = 0; i < N; i++) {
        if (check[i] == 0) {
            Root = i;
            break;
        }
    }
    return Root;
}

void PreOrder(int head, Tree t) {
    printf("PreOrder:\n");
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
    printf("LevelOrder:\n");
    Queue* q = Init_queue();
    EnQueue(q, t + head);                      //根入队
    Qnode* x = (Qnode*)malloc(sizeof(Qnode));  //接收出队元素
    while (!Isempty(q)) {
        DeQueue(q, x);
        printf("%c->", x->current->data);
        if (x->current->lchild != NON)
            EnQueue(q, t + x->current->lchild);
        if (x->current->rchild != NON)
            EnQueue(q, t + x->current->rchild);
    }
    //↓此处之前写成在while里free（x），后果是x指向的内存被交还，下次出队时x处即脏数据
    free(x);
}
Queue* Init_queue() {
    Queue* p = (Queue*)malloc(sizeof(Queue));
    p->front = (Qnode*)malloc(sizeof(Qnode));
    p->rear = p->front;
    p->front->next = NULL;
    return p;
}
bool Isempty(Queue* q) {
    if (q->front == q->rear)
        return true;
    else
        return false;
}
void EnQueue(Queue* q, Node* x) {
    Qnode* s = (Qnode*)malloc(sizeof(Qnode));
    s->current = x;
    s->next = NULL;
    q->rear->next = s;
    q->rear = s;
}
bool DeQueue(Queue* q, Qnode* x) {
    if (Isempty(q))
        return false;
    Qnode* temp = q->front->next;
    x->current = temp->current;
    x->next = temp->next;
    q->front->next = temp->next;
    if (temp == q->rear)  //若原队列只有一个，删除后变空
        q->rear = q->front;
    free(temp);
    return true;
}
/*1、malloc与free配套使用。(有申请有释放，有创建有销毁)
2、指向malloc申请的堆内存的指针，在运用过程中千万不要另外赋值，否则同样导致内存泄露
3、malloc后，实际使用时指针长度超过了你申请的范围。再去free时肯定出问题。
4、改变指针的初始指向地址*/

bool isomorphic(int head1, Tree t1, int head2, Tree t2) {
    if (head1 == NON && head2 == NON)  //两树皆空，同
        return 1;
    if (head1 == NON && head2 != NON ||
        head1 != NON && head2 == NON)  //一树空一树非空，不同
        return 0;
    Node *h1 = t1 + head1, *h2 = t2 + head2;
    if (h1->data != h2->data)  //根不同，不同
        return 0;
    if (h1->lchild == NON && h2->lchild == NON)  //两树的根左孩都非空，判断右孩
        return isomorphic(h1->rchild, t1, h2->rchild, t2);
    //左孩存在且相等，往下；
    if ((h1->lchild != NON && h2->lchild != NON) &&
        ((t1 + h1->lchild)->data == (t2 + h2->lchild)->data))
        return isomorphic(h1->lchild, t1, h2->lchild, t2) &&
               isomorphic(h1->rchild, t1, h2->rchild, t2);
    else  //左孩可能与右孩对调
        return isomorphic(h1->lchild, t1, h2->rchild, t2) &&
               isomorphic(h1->rchild, t1, h2->lchild, t2);
}
