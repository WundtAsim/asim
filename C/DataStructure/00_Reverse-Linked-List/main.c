#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 100000
typedef int ELEtype;
void print_list(ELEtype*list, int*order, int first){
    int position = first;
    int next_position = order[first];
    while(next_position != -1){
        printf("%05d %d %05d\n", position, list[position],next_position);
        position = next_position;
        next_position = order[next_position];
    }
    printf("%05d %d %d\n", position, list[position],next_position);
    return;
}
int main(){
    int  first, N, K;
    scanf("%d%d%d",&first, &N, &K);
    //the list of data
    ELEtype list[MAXSIZE];
    //the order list
    int order[MAXSIZE];

    for(int i = 0; i < N; i++){
        int index, data, next;
        scanf("%d%d%d",&index, &data, &next);
        list[index] = data;
        order[index] = next;
    }
    print_list(list, order, first);
    return 0;
}
