#pragma once
#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<time.h>
#include<stdarg.h>

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




