#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define element int
#define Maximum 10
#define NON -1
typedef struct node {
    element lchild, rchild;
    struct node* next;
} Node;
typedef struct queue {
    struct node *front, *rear;
} Queue;
//**********函数声明**********//
int buildTree(Node*);
void showLeaves(Node* tree, int Root);
Queue* Init_Queue();
bool isempty(Queue* queue);
void EnQueue(Queue* queue, Node* x);
bool DeQueue(Queue* queue, Node* x);
void visit(Node*, Queue*, Node*);

int main() {
    Node tree[Maximum];
    int Root = buildTree(tree);
    showLeaves(tree, Root);
    return 0;
}

int buildTree(Node* p) {
    int N;
    scanf("%d", &N);
    int* check = (int*)malloc(sizeof(int) * N);
    char left, right;
    for (int i = 0; i < N; i++)
        check[i] = 0;
    for (int i = 0; i < N; i++) {
        scanf(" %c %c", &left, &right);
        (p + i)->lchild = (left == '-') ? NON : (left - '0');
        (p + i)->rchild = (right == '-') ? NON : (right - '0');
        if (left != '-')
            check[(p + i)->lchild] = 1;
        if (right != '-')
            check[(p + i)->rchild] = 1;
    }
    int root = NON;
    for (int i = 0; i < N; i++) {
        if (check[i] == 0) {
            root = i;
            break;
        }
    }
    free(check);
    return root;
}
void showLeaves(Node* tree, int Root) {
    Queue* q = Init_Queue();
    EnQueue(q, tree + Root);
    Node* x = (Node*)malloc(sizeof(Node));
    while (!isempty(q)) {
        DeQueue(q, x);
        if (x->lchild != NON)
            EnQueue(q, tree + x->lchild);
        if (x->rchild != NON)
            EnQueue(q, tree + x->rchild);
        // printf("%d->", (x->next - tree));
        visit(tree, q, x);
    }
    free(x);
}
Queue* Init_Queue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = (Node*)malloc(sizeof(Node));
    q->rear = q->front;
    q->front->next = NULL;
    return q;
}
bool isempty(Queue* queue) {
    if (queue->front == queue->rear)
        return true;
    else
        return false;
}
void EnQueue(Queue* queue, Node* x) {
    queue->rear->next = x;
    queue->rear = x;
}
bool DeQueue(Queue* queue, Node* x) {
    if (isempty(queue))
        return false;
    Node* temp = queue->front->next;
    x->lchild = temp->lchild;
    x->rchild = temp->rchild;
    x->next = temp;
    queue->front->next = temp->next;
    if (temp == queue->rear)
        queue->rear = queue->front;
    // free(temp);
    return true;
}
void visit(Node* tree, Queue* q, Node* x) {
    if (x->rchild == NON && x->lchild == NON) {
        printf("%d", x->next - tree);
        if (!isempty(q))
            putchar(' ');
    }
}
