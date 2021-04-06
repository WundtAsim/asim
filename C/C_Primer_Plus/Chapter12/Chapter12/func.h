//#pragma once
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<time.h>

/*-------------p13_13-------------*/
void eliminate_noise(char* filename,int x,int y);
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




