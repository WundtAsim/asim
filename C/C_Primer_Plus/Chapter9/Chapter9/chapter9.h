#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>

double min_2(double x, double y);

void chline(char ch, int i, int j);

double haraverage(double a, double b);

void larger_of(double *a, double *b);

void large_sort(double *a, double *b,double *c);

int alpha_cal(int a);

double power_i(double a, int b);

void to_base_n(int base, int n);

void Fibonacci(unsigned n);

void p10_1(void);

void copy_arr(double *target, double*source, int n);//p10_2的子函数，用于拷贝数组
void copy_ptr(double *target, double*source, int n);//p10_2的子函数，用于拷贝数组
void copy_ptrs(double *target, double*source, double *source_n);//p10_2的子函数，用于拷贝数组
void p10_2(void);

int max_array(int *array, int n);
void p10_3(void);

int *array_reverse(int *array, int n);
void p10_6(void);

void p10_7(void);

void p10_8(void);

double *copy_2d(double source[][5], double target[][5], int rows);//p10_9子函数，用于拷贝二维数组
void display(double source[][5], double target[][5], int rows);//p10_9子函数，用于显示两个二维数组
void p10_9(void);

void merge_array(int *source1, int *source2, int *target, int n);//p10_10子函数，合并两个一维数组
void p10_10(void);

void print_a(int *a, int n);//p10_11子函数，用于打印二维数组
void double_array(int *a[][5], int n);//p10_11子函数，用于将数组每个数double
void p10_11(void);

double average_a(double *a, int n);//p10_13子函数，用于计算一维数组均值
double average_2d(double a[][5], int n);//p10_13子函数，用于计算二维数组总均值
double max_2d(double a[][5], int n);//p10+13子函数，用于找二维数组最大值
void p10_13(void);

//s_gets()调用函数：读取整行输入字符串，并用空字符代替换行符，或者读取一部分输入，丢弃其余部分，
char* s_gets(char* st, int n);

void get_ch(char* ch, int n);//p11_1子函数，读取字符串
void p11_1(void);

void get_word(char* ch);//p11_3子函数，读取字符串中第一个单词
void p11_3(void);