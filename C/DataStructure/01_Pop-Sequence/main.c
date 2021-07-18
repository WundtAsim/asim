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

    for (int i = 0;i<K;i++){
        while(getchar()!='\n')//如果跳出，清理剩余输入
            continue;
        Stack list = init_stack();
        int* temp;
        int current;
        bool Noway = false;//用于表示栈满，直接失败的情况
        temp = (int*)malloc(N * sizeof(int));
        for(int j = 0;j<N;j++){
            scanf("%d",temp+j);
            //第一个数，则先将栈内push到第一个数
            if(j==0){
                for(current = 1; current<=*(temp+j); current++){
                    //如果栈满，直接退出循环
                    if(! push_stack(list, current, M)){
                        Noway = true;goto here;
                    }
                }
                int out;
                pop_stack(list,&out);
            }
            else{
                    //更新top
                int top = gettop(list);
                //如top=第一个出栈的数，则出栈
                if(top == *(temp+j)){
                    int out;
                    pop_stack(list,&out);
                }
                //如检测的数>top，且其>current，则入栈到current
                else if(*(temp+j) > top && *(temp+j)>=current){
                    while(current <= *(temp+j)){
                        //如果栈满，直接退出循环
                        if(! push_stack(list, current, M)){
                            Noway = true;break;
                        }
                        current++;
                    }//while
                    int out;
                    pop_stack(list,&out);
                }//elseif
                else{
                        Noway = true;break;
                    }
            }//else
        }//for 一行数判断完
        here:if(!isempty(list) || Noway)
            printf("NO");
        else
            printf("YES");
        if(i!=K-1)
            putchar('\n');

    free(temp);
    destory_stack(list);
    }

    return 0;
}
/*************************************************************
*****************----------functions---------*****************
*************************************************************/
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
