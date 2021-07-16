#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100000
typedef int ELEtype;
void print_list(ELEtype*list, int*order){
    int i = 0;
    while(order[i+1]!=-1){
        printf("%05d %d %05d\n", order[i], list[order[i]], order[i+1]);
        i++;
    }
    printf("%05d %d %d\n", order[i], list[order[i]], order[i+1]);
    return;
}
int getlength(int*order){
    int N = 0;
    while(*(order++)!= -1)
        N++;
    return N;
}
void reverse_K(int*order, int K){
    int temp[K];
    for (int i = 0; i<K; i++)
        temp[i] = *(order+i);
    for(int i = 0; i < K; i++){
        *(order+i) = temp[K-1-i];
    }
    return;
}
int reverse_all(int*order,int K){
    int N = getlength(order);
    int*ptr = order;
    while(N/K>0){
        reverse_K(ptr,K);
        N-=K;
        ptr+=K;
    }
    return;
}
int main(){
    int  first, N, K;
    scanf("%d%d%d",&first, &N, &K);
    //the list of data
    ELEtype list[MAXSIZE];
    int next_pos[MAXSIZE];
    //the order list的顺序即为数组下标的顺序
    int order[N+1];

    for(int i = 0; i < N; i++){
        int index, data, next;
        scanf("%d%d%d",&index, &data, &next);
        list[index] = data;
        next_pos[index] = next;
    }
    //sort the list of order
    for(int i = first,j = 0; i != -1; i = next_pos[i]){
        order[j] = i;
        j++;
        order[j] = -1;
    }
    reverse_all(order,K);
    print_list(list, order);


    return 0;
}
