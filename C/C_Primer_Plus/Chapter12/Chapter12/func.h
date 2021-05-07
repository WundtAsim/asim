#pragma once
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<time.h>
#include<stdarg.h>
#include<stdbool.h>

/*-------------p17_7-------------*/
#define SLEN 81
#define MAXITEAMS 100
typedef struct item_word{
	char word[SLEN];
	int count;
}Item_word;

typedef struct node {
	Item_word item_word;
	struct node* left;
	struct node* right;
}Node;
typedef struct tree {
	Node* root;
	int size;
}Tree;
void init_tree(Tree* ptree);//初始化树
bool tree_empty(const Tree* ptree);//树空
bool tree_full(const Tree* ptree);//树满
int tree_count(const Tree* ptree);//树中item个数
bool add_item2tree(const Item_word* pi, Tree* ptree);//在树中加入item
bool in_tree(const Item_word* pi , Tree* ptree);//item是否在树中
bool del_item(const Item_word* pim , Tree* ptree);//从树中删除item
bool traverse(const Tree* ptree, void(*pfun)(Item_word item));//将func应用到树中每一个item
void del_all(Tree* ptree);//从树中删除所有
const Item_word* whereintree(const Item_word* pi, const Tree* ptree);//返回树中某个item地址

void p17_7(void);

/*-------------p17_6-------------*/
bool in_array(int* sarray, int n, int obj);
void p17_6(void);

/*-------------p17_5-------------*/
#define MAXSIZE 100//栈大小

typedef char item;//item栈的数据类型

typedef struct {
	item data[MAXSIZE];
	int top;//第一个空位的索引值
}stack;

char* s_get(char* st, int n);//从std获取字符串输入
void init_stack(stack* ps);//初始化栈-ps指向一个栈
bool full_stack(const stack* ps);//判断栈是否已满
bool empty_stack(const stack* ps);//判断栈是否为空
bool push(item val, stack* ps);//压入栈
bool pop(item* val, stack* ps);//弹出栈
void p17_5(void);

/*-------------p16_7-------------*/
void show_d_array(const double ar[], int n);
double* new_d_array(int n, ...);
void p16_7(void);

/*-------------p16_5-------------*/
void rand_draw(int* source, int num, int n);
void p16_5(void);

/*-------------p16_4-------------*/
void delay(double n);
void p16_4(void);

/*-------------p16_3-------------*/
#define DEG2RAD(x)((x)*atan(1)/45)
typedef struct polar {
	float r;
	float t;
}POLAR;
typedef struct cartisian {
	float  x;
	float y;
}CARTISIAN;
CARTISIAN p2c_convert(struct polar* polar);
void p16_3(void);

/*-------------p16_2-------------*/
#define HARMEAN(x,y)( 1/( 1/(x) + 1/(y) )*2 )
void p16_2(void);

/*-------------p15_6-------------*/
void show_message(struct message* ps);
void show_choices(void);
void p15_6(void);

/*-------------p15_5-------------*/
unsigned int rotate(unsigned int dig, int n);
void p15_5(void);

/*-------------p15_2-------------*/
void bitoperate(char* ch,char* new,char choice);
void show_bitoperate(void);
void p15_2(void);

/*-------------p15_1-------------*/
char* i2b(int n);
int b2i(char* ch);
void p15_1(void);

/*-------------p14_11-------------*/
void show_menu(void);
void transform(double* source, double* target, int n, double(*fp)(double));
void p14_11(void);

/*-------------p14_5-------------*/
void set_students(struct student list[], int n);
void get_averages(struct student list[], int n);
void show_messages(const struct student list[], int n);
void show_averages(const struct student list[], int n);
void p14_5(void);

/*-------------p14_4-------------*/
void show_id(const struct id identi[], int );
void p14_4(void);

/*-------------p14_2-------------*/
int day_count(int day, char* month);
void p14_2(void);

/*-------------p14_1-------------*/
int days(char* month);
void p14_1(void);

/*-------------p13_13-------------*/
void eliminate_noise(char* filename,const int x,const int y);
void p13_13(void);

/*-------------p13_12-------------*/
FILE* openfile(char* filename);
void p13_12(void);

/*-------------p13_10-------------*/
void p13_10(void);

/*-------------p13_7-------------*/
void p13_7(void);

/*-------------p13_3-------------*/
int readfile(FILE* );
void p13_3(void);

/*-------------p13_2-------------*/
int file_copy(FILE* source, FILE* destination);
void p13_2(int argcount,char **argument);

/*-------------p13_1-------------*/
void p13_1(void);

/*-------------p12_9-------------*/
void p12_9(void);

/*-------------p12_8-------------*/
int *make_array(int elem,int val);
void p12_8(void);

/*-------------p12_6-------------*/
void occur_times(int* arr, int n, int j);
void p12_6(void);


/*-------------p12_5-------------*/
void show_array(const int *arr, int n);
void sort(int *arr, int n);
void p12_5(void);

/*-------------p12_4-------------*/
int counter(void);
void p12_4(void);

//--------------p12_2-------------//
void set_mode(int n);
void get_info();
void show_info();




