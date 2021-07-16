#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#define MAXIMUM 1000
typedef struct Node{
    int data;
    struct Node* next;
} Node,*Stack;

Stack init_stack();
bool isempty(Stack list);
bool isfull(Stack list, int N);
int getlen(Stack list);
bool push_stack(Stack list, int, int max);
bool pop_stack(Stack list, int* );
int gettop(Stack list);
void destory_stack(Stack list);

int main(){
    //M：栈深， N：序列长度， K：序列个数
    int M, N, K;
    scanf("%d%d%d",&M,&N,&K);

    Stack list = init_stack();
    for (int i = 0;i<K;i++){
        int* temp;
        temp = (int*)malloc(N * sizeof(int));
        for(int j = 0;j<N;j++){
            scanf("%d",temp+j);
            int top = gettop(list);
            //如空栈，则先push到
            if(top == -1){
                for(int add = 1; add<=*(temp+j); add++){
                    push_stack(list, add, M);
                }
            }
            //更新top
            top = gettop(list);
            //如top=第一个出栈的数
            else if(top == *(temp+j)){
                pop_stack(list);
                break;
            }
            //如top<第一个出栈的数
            else if(){

            }
        }




        push_stack(list,temp,10);
    }

    destory_stack(list);
    return 0;
}

//初始化栈
Stack init_stack()
{
    Stack list = NULL;
    list = (Stack)malloc(sizeof(Node));
    list->next = NULL;
    return list;
}
//判空栈
bool isempty(Stack list)
{
    return (list->next == NULL);
}
//判满栈
bool isfull(Stack list, int max)
{
    if(getlen(list) == max)
        return true;
    else
        return false;
}
int getlen(Stack list){
    int n = 0;
    Node*ptr = list->next;
    while(ptr){
        n++;
        ptr = ptr->next;
    }
    return n;
}
//压入栈
bool push_stack(Stack list, int a, int max)
{
    if(isfull(list,max))
        return false;
    Node* ptr = NULL;
    ptr = (Node*)malloc(sizeof(Node));
    ptr->data = a;
    ptr->next = list->next;
    list->next = ptr;
    return true;
}
//弹出栈
bool pop_stack(Stack list, int* item)
{
    if(isempty(list))
        return false;
    Node* ptr = list->next;
    *item = ptr->data;
    list->next = ptr->next;
    free(ptr);
    return true;
}
//获取栈顶元素
int gettop(Stack list){
    if(!isempty(list))
        return list->next->data;
    else return -1;
}
//销毁栈
void destory_stack(Stack list){
    Node*ptr;
    while(! isempty(list)){
        ptr = list->next;
        list->next = ptr->next;
        free(ptr);
    }
    free(list);
    return;
}
