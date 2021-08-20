#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define Maximum 1000
typedef struct hnode {
    /*堆数组*/
    int* data;
    /*当前个数*/
    int size;
    /*最大容量*/
    int capacity;
} Hnode, *Heap;

/*函数声明*/
Heap initHeap(int max);
bool isFull(Heap H);
bool isEmpty(Heap H);
bool insert(Heap H, int x);
int delete (Heap H);
void PercDown(Heap H, int p);
void buildMinHeap(Heap H);
void printPath(Heap H, int M);

/*主函数*/
int main() {
    int N, M;
    scanf("%d%d", &N, &M);
    int tempData;
    Heap H = initHeap(Maximum);
    for (int i = 1; i <= N; i++) {
        /*scanf("%d", &H->data[i]);
        H->size++;*/

        scanf("%d", &tempData);
        insert(H, tempData);
    }
    /*此种方式会导致叶节点顺序与输入顺序不同步*/
    // buildMinHeap(H);
    printPath(H, M);

    return 0;
}

/*函数定义*/
Heap initHeap(int max) {
    Heap H = (Heap)malloc(sizeof(Hnode));
    H->data = (int*)malloc((Maximum + 1) * sizeof(int));
    /*最小堆的哨兵*/
    H->data[0] = -10001;
    H->size = 0;
    H->capacity = Maximum;
    return H;
}
bool isFull(Heap H) {
    return (H->size == H->capacity);
}
bool isEmpty(Heap H) {
    return (H->size == 0);
}
bool insert(Heap H, int x) {
    if (isFull(H))
        return false;
    Heap temp;
    int seat = ++H->size;
    /*如果待插入位置的父亲大于待插入元素，将父亲下放*/
    while (x < H->data[seat / 2]) {
        H->data[seat] = H->data[seat / 2];
        seat = seat / 2;
    }
    H->data[seat] = x;
    return true;
}
int delete (Heap H) {
    if (isEmpty(H))
        return false;
    int seat, parent, child;
    int MaxItem = H->data[1];
    /* 用最大堆中最后一个元素从根结点开始向下过滤下层结点 */
    int x = H->data[H->size--]; /* 注意当前堆的规模要减小 */
    for (parent = 1; parent * 2 <= H->size; parent = child) {
        child = parent * 2;
        if (child != H->size) /* Child指向左右子结点的较小者 */
            child = (H->data[child] < H->data[child + 1]) ? child : child + 1;
        if (x <= H->data[child])
            break; /* 找到了合适位置 */
        else /* 向下滤X，把上层的根用child填充，即把小的child往上放 */
            H->data[parent] = H->data[child];
    }
    H->data[parent] = x;
    return MaxItem;
}
void PercDown(Heap H, int p) {
    /* 下滤：将H中以H->Data[p]为根的子堆调整为最xiao堆 */
    int Parent, Child;
    int X;

    X = H->data[p]; /* 取出根结点存放的值 */
    for (Parent = p; Parent * 2 <= H->size; Parent = Child) {
        Child = Parent * 2;
        if ((Child != H->size) && (H->data[Child] > H->data[Child + 1]))
            Child++; /* Child指向左右子结点的较xiao者 */
        if (X <= H->data[Child])
            break; /* 找到了合适位置 */
        else       /* 下滤X */
            H->data[Parent] = H->data[Child];
    }
    H->data[Parent] = X;
}
void buildMinHeap(Heap H) {
    /* 调整H->Data[]中的元素，使满足最大堆的有序性  */
    /* 这里假设所有H->Size个元素已经存在H->Data[]中 */

    int i;

    /* 从最后一个结点的父节点开始，到根结点1 */
    for (i = H->size / 2; i > 0; i--)
        PercDown(H, i);
}
void printPath(Heap H, int M) {
    int* index = (int*)malloc(M * sizeof(int));
    int temp;
    for (int i = 0; i < M; i++)
        scanf("%d", index + i);
    /*输出序列*/
    for (int i = 0; i < M; i++) {
        temp = index[i];
        while (temp > 1) {
            printf("%d ", H->data[temp]);
            temp /= 2;
        }
        if (i != M - 1)
            printf("%d\n", H->data[1]);
        else
            printf("%d", H->data[1]);
    }
}