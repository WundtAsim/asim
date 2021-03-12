#include <stdio.h>
#include "chapter9.h"

double min_2(double x, double y)
{
	return (x > y) ? y : x;
}

void chline(char ch, int i, int j)
{
	for (int b = 0; b < j; b++)
	{
		for (int a = 0; a < i; a++)
		{
			printf("%c", ch);
		}
		printf("\n");
	}
	
}

double haraverage(double a, double b)
{
	return 2 / (1 / a + 1 / b);
}

void larger_of(double *a, double *b)
{
	if (*a > *b)
	{
		*b = *a;
	}
	else
	{
		*a = *b;
	}
}

void large_sort(double *a, double *b, double *c)
{
	
	double temp_max,temp;
	temp = *a >= *b ? *a : *b;
	temp_max = *c >= temp ? *c : temp;//判断最大值

	temp = *a <= *b ? *a : *b;
	temp = *c <= temp ? *c : temp;//判断最小值

	if (*a != temp &&*a != temp_max)
		*b = *a;
	else if (*b != temp &&*b != temp_max)
		;
	else
		*b = *c;
	*a = temp;
	*c = temp_max;
	
}

int alpha_cal(int a)
{
	if (isalpha(a))
	{
		
		return ( tolower(a) - 'a' + 1);
	}
	else
	{
		return -1;
	}

}

double power_i(double a, int b)
{
	if (a == 0 && b == 0)
		return -1;
	else if (a == 0)
		return 0;
	else if (b == 0)
		return 1;
	else if (b < 0)
		return (1 / pow(a, -b));
	else
		return(pow(a, b));
}

void to_base_n(int base, int n)
{
	if (base > 0)
	{
		to_base_n(base / n,n);
	}
	printf("%d", base%n);
	return;
}

void Fibonacci(unsigned int n)
{
	n -= 2;
	int x =1, y = 1;
	int temp;

		printf("%d\t%d\t", y,x);

		for (int i = 0; i < n; i++)
		{
			printf("%d\t", x+y);
			temp = x;
			x = y;
			y += temp;
		
		}
		printf("\nDone!");
}

void p10_1(void)
{
#define MONTHS 12
#define YEARS 5
	const float rain[YEARS][MONTHS] = 
	{
		{ 4.3, 4.3, 4.3, 3.0, 2.0, 1.2, 0.2, 0.2, 0.4, 2.4, 3.5, 6.6 },
		{ 8.5, 8.2, 1.2, 1.6, 2.4, 0.0, 5.2, 0.9, 0.3, 0.9, 1.4, 7.3 },
		{ 9.1, 8.5, 6.7, 4.3, 2.1, 0.8, 0.2, 0.2, 1.1, 2.3, 6.1, 8.4 },
		{ 7.2, 9.9, 8.4, 3.3, 1.2, 0.8, 0.4, 0.0, 0.6, 1.7, 4.3, 6.2 },
		{7.6, 5.6, 3.8, 2.8, 3.8, 0.2, 0.0, 0.0, 0.0, 1.3, 2.6, 5.2 }
	};
	int year, month;
	float subtot, total;
	printf(" YEAR\tRAINFALL(inches)\n");
	for (year = 0, total = 0; year < YEARS; year++)
	{
		//每一年，各月降水量总和
		for (month = 0, subtot = 0; month < MONTHS; month++)
		{
			subtot += *(*(rain + year) + month);
		}
		printf("%5d\t%15.1f\n", 2010 + year, subtot);
		total += subtot;//5年总降水量
	}
	printf("\nThe yearly average is %.1f inches\n\n", total / YEARS);
	printf("MONTHLY AVERAGES:\n\n");
	printf("Jan\tFeb\tMar\tApr\tMay\tJun\tJul\tAug\tSep\tOct\tNov\tDec\n");

	for (month = 0; month < MONTHS; month++)
	{
		//每个月，5年的总降水量
		for (year = 0, subtot = 0; year < YEARS; year++)
			subtot += *(*(rain + year) + month);
		printf("%4.1f\t", subtot / YEARS);
	}
	printf("\n");
	

}

void copy_arr(double *target, double*source, int n)
{
	//p10_2的子函数，用于拷贝数组
	//printf("target array is:\n");
	for (int a = 0; a < n; a++)
	{
		target[a] = source[a];
		//printf("%.1lf ", target[a]);
	}
	//printf("\n");
	
}
void copy_ptr(double *target, double*source, int n)
{
	//p10_2的子函数，用于拷贝数组
	//printf("target array is:\n");
	for (int a = 0; a < n; a++)
	{
		*(target+a) = *(source+a);
		//printf("%.1lf ", *(target+a));

	}
	//printf("\n");
}
void copy_ptrs(double *target, double *source, double *source_n)
{
	//p10_2的子函数，用于拷贝数组
	//printf("target array is:\n");
	int  index = 0;
	while (source<source_n)
	{
		*(target + index) = *source;
		
		//printf("%.1lf ", *(target + index));
		index++;
		source = source + 1;

	}
	//printf("\n");
}
void p10_2(void)
{
	double source[5] = { 1.1, 2.2, 3.3, 4.4, 5.5 };
	double target1[5];
	double target2[5];
	double target3[5];

	copy_arr(target1, source, 5);
	copy_ptr(target2, source, 5);
	copy_ptrs(target3, source, source + 5);

}

int max_array(int *array, int n)
{
	//p10_3子函数，返回Int数组最大值
	int max_dig = 0;
	for (int a = 0; a < n; a++)
	{
		if (array[a] > max_dig)
			max_dig = array[a];
	}
	return max_dig;
}
void p10_3(void)
{
	printf("enter an array with type of int which contain 5 digits:\n");
	int a = 0;
	int array[5];
	for (int i = 0; i < 5; i++)
	{
		scanf_s("%d", &a);
		array[i] = a;
	}
	printf("the max digits of the array is %d", max_array(array, 5));
}

int *array_reverse(int *array, int n)
{
	int (*p)[5];
	int array_new[5];
	p = &array_new;
	for (int i = 0; i < n; i++)
	{
		array_new[i] = array[n - i - 1];
	}
	
	return p;
}
void p10_6(void)
{
#define NUM 5
	int array[NUM] = { 1, 2, 3, 4, 5 };
	for (int i = 0; i < NUM; i++)
	{
		printf("第 %d 个数字为：%d\n", i + 1, *(array_reverse(array,5)+i) );
	}
}

void p10_7(void)
{
	//使用p10_2中的拷贝函数拷贝二维数组
	const double source[3][5] = 
	{
		{ 1.1, 2.2, 3.3, 4.4, 5.5 },
		{ 2.1, 3.2, 4.3, 5.4, 6.5 },
		{ 3.1, 4.2, 5.3, 6.4, 7.5 }
	};
	double target1[3][5];
	double target2[3][5];
	double target3[3][5];

	copy_arr(target1, source, 3);
	copy_ptr(target2, source, 3);
	copy_ptrs(target3, source, source + 3);

	printf("target array 1 is:\n");
	for (int a = 0; a < 3; a++)
	{
		copy_arr(target1[a], source[a], 5);
		for (int b = 0; b < 5; b++)
		{
			printf("%.1lf ", target1[a][b] );
		}
		printf("\n");	

	}
	printf("\n");
	
}

void p10_8(void)
{
	const double source[7] = { 1.1, 2.2, 3.3, 4.4, 5.5, 6.6, 7.7 };
	double target[3];

	copy_arr(target, (source + 2), 3);
	printf("target array is \n");
	for (int a = 0; a < 3; a++)
	{
		printf("%.1lf ", target[a]);
	}

}

double *copy_2d(double source[][5], double target[][5], int rows)
{

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < 5; j++)
			target[i][j] = source[i][j];
	}
	return target;
}
void display(double source[][5], int rows)
{
	printf("the array is \n");
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < 5; j++)
			printf("%.1lf ", source[i][j]);
		printf("\n");
	}
}
void p10_9(void)
{
	const double source[3][5] =
	{
		{ 1.1, 2.2, 3.3, 4.4, 5.5 },
		{ 2.1, 3.2, 4.3, 5.4, 6.5 },
		{ 3.1, 4.2, 5.3, 6.4, 7.5 }
	};
	double target[3][5] =
	{
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 0, 0, 0, 0 }
	};
	display( copy_2d(source,target,3), 3 );

}

void merge_array(int *source1, int *source2, int *target, int n)
{
	printf("the target array is :");
	for (int i = 0; i < n; i++)
	{
		target[i] = source1[i] + source2[i];
		printf("%d ", target[i]);
	}
	putchar('\n');
}
void p10_10()
{
#define NUM  4
	int source1[NUM] = { 2,4,5,8 };
	int source2[NUM] = { 1, 0, 4, 6 };
	int target[NUM] = { 0, 0, 0, 0 };
	merge_array(source1, source2, target, NUM);
}

void print_a(int a[][5], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 5;j++)
			printf("%d ", a[i][j]);
		putchar('\n');		
	}
}
void double_array(int a[][5], int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 5; j++)
			a[i][j] *= 2;		
	}
}
void p10_11(void)
{
	int source[3][5] = {
		{1,2,3,4,5},
		{6,7,8,9,10},
		{11,12,13,14,15}
	};
	printf("the resource array is:\n");
	print_a(source, 3);
	double_array(source, 3);
	printf("the targert array is:\n");
	print_a(source, 3);

}

double average_a(double *a, int n)
{
	double sum = 0;
	for (int i = 0; i < n; i++)
		sum += a[i];
	return sum;
}
double average_2d(double a[][5], int n)
{
	double sum = 0;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 5;j++)
			sum += a[i][j];
	}
	sum /= (n * 5);		
	return sum;
}
double max_2d(double a[][5], int n)
{
	double max = a[0][0];
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < 5; j++)
			max = (max < a[i][j]) ? a[i][j] : max;
	}
	return max;
}
void p10_13(void)
{
	printf("enter 3 groups of digits in the types of double:\n");
	double source[3][5];
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 5; j++)
			scanf_s("%lf", &source[i][j]);
	}

	printf("the average of every row is:\n");
	for (int i = 0; i < 3; i++)
		printf("%.1lf\n", average_a(source[i], 5));

	printf("the average of array is:\n");
	printf("%.1lf\n", average_2d(source, 3));
	
	printf("the max of array is:\n");
	printf("%.1lf\n", max_2d(source, 3));

}

//s_gets()调用函数：读取整行输入字符串，并用空字符代替换行符，或者读取一部分输入，丢弃其余部分，
char* s_gets(char* st, int n)
{
	/*
	char* ret_val;
	int i = 0;

	ret_val = fgets(st, n, stdin);
	if (ret_val)//即：!=NULL
	{
		while (st[i] != '\n' && st[i] != '\0')
			i++;
		if (st[i] == '\n')
			st[i] = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
		return ret_val;
	*/

	/*使用指针代替数组的方式
	char* ret_val;
	ret_val = fgets(st, n, stdin);
	if (ret_val)//即：!=NULL
	{
		while (*st != '\n' && *st != '\0')
			st++;
		if (*st == '\n')
			*st = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
		return ret_val;
		*/
	/*使用strchr函数找\n的方式*/
	char* ret_val;
	char* find;
	ret_val = fgets(st, n, stdin);
	if (ret_val)//即：!=NULL
	{
		find = strchr(st, '\n');//查找换行符地址
		if (find!= NULL)//存在换行符则替换
			*find = '\0';
		else
			while (getchar() != '\n')
				continue;
	}
	return ret_val;

}
void get_ch(char* ch, int n)
{
	for (int i = 0; i < n - 1; i++)
	{		
		ch[i] = getchar();
		if (isspace(ch[i]))
		{
			ch[i + 1] = '\0';
			break;
		}
			
	}
	ch[n-1] = '\0';
	
}
void p11_1(void)
{
#define Len 10
	printf("enter your words with %d characters:\n",Len-1);
	char input[10];
	get_ch(input, Len);
	printf("Result is:\n");
	puts(input);
	
}

void get_word(char* ch)
{
	char temp = getchar();
	while (isspace(temp))
	{
		temp = getchar();
	}
	int i = 0;
	ch[i] = temp;
	while (!(isspace(ch[i])))
	{
		i++;
		ch[i] = getchar();
	} 
	ch[++i] = '\0'; 
}
void p11_3(void)
{
	printf("enter your words :\n");
	char input[80];
	get_word(input);
	printf("Result is:\n");
	puts(input);
}


char* get_words(char* ch, int a)
{
	
	/*自己写的，下面使用参考的写法
	char temp = getchar();
	while (isspace(temp))
	{
		temp = getchar();
		continue;
	}
	ch[0] = temp;

	temp = getchar();
	int i = 1;//字符个数
	while ( (!(isspace(temp))) && (i<a-1) )
	{
		ch[i] = temp;
		i++;
		temp = getchar();		
	}
	ch[i] = '\0';
	return;*/

	int temp;
	int n = 0;
	char* pt = ch;

	while ((temp = getchar()) != EOF && isspace(temp) )
		continue;
	//↑跳过第一个非空白字符前的所有字符
	if (temp == EOF)
	{
		return NULL;
		//若第一次直接输入Ctrl＋Z，返回空指针
	}
	else
	{
		*ch++ = temp;
		n++;
		//↑吧第一个非空白字符赋值给ch所指向的内存空间，并指向下一个存储空间
	}

	while ((temp = getchar()) != EOF && !isspace(temp) && n < a-1)
	{
		*ch++ = temp;
		//↑从第二个字符开始赋值知道遇见但此后第一个空白
		n++;
	}
	*ch = '\0';

	if (temp == EOF)
	{
		return NULL;
	}
	else
	{
		while (getchar() != '\n')
			continue;
		//↑从单词后面丢弃输入行中其他字符
		return pt;
	}

}
void p11_4(void)
{
	printf("enter your words :\n");
	char input[50];
	while (get_words(input, 22) != NULL)
	{
		//get_words(input,12);
		printf("Result is:\n");
		puts(input);
		printf("enter your words :\n");
	}
	
}


char* str_word(const char* ch, char one)
{
	//p11_5子函数，用于查找指定字符串中指定字符。
	int len = strlen(ch);
	for (int i = 0; i < len; i++)
	{
		if (ch[i] == one)
		{
			return ch + i;
		}
		if (ch[i] == '\0')
			return NULL;
	}
}

void p11_5(void)
{
	char ch[3][30] = {
		"im groot.",
		"im not groot.",
		"damn."
	};

	for (int i = 0; i < 3; i++)
	{
		printf("the sentence %d:\n\"n\" first came out at %p\n", i, str_word(ch[i], 'n'));
		printf("the function result is %p\n\n", strchr(ch[i], 'n'));
	}
}


int is_within(int ch, const char* str)
{
	//p11_6子函数用于检测字符是否在字符串中
	if (strchr(str, ch) != NULL)
		return 1;
	else
		return 0;
	
}
void p11_6()
{
	printf("plz enter a string: (EOF to quit)\n");
	char str[20];
	int ch;
	while (s_gets(str, 20))
	{

		printf("plz enter a character: (EOF to quit)\n");
		ch = getchar();
		while (getchar() != '\n')
			continue;

		if (ch == EOF)
			break;

		if (is_within(ch , str))
		{
			printf("\"%c\"is within the string \"%s\"\n", ch, str);
		}
		else
			printf("\"%c\"is not within the string \"%s\"\n", ch, str);
		printf("\n\n"
			"You can enter another string to check:\n");
	}
	printf("Done!\n");

}

char* mystrncpy(char* s1, char* s2, int n)
{
	//p11_7子函数，用于模仿strncpy函数复制s2的第n个字符到s1中
	char* temp;
	temp = s1;
	for (int i = 0; i < n && s2[i]!='\0' ; i++)
	{
		*s1++ = s2[i];
	}
	*s1 = '\0';

	return temp;
}
void p11_7()
{
	printf("Plz enter string s1:(EOF to quit)\n");
	char s1[20];
	char s2[20];
	int n;
	while (s_gets(s1, 20))
	{
		printf("Then enter string s2:\n");
		if (s_gets(s2, 20) != NULL)
		{
			printf("Next, enter the number of characters you want to copy to s1 in the stirng s2:\n");
			while (scanf_s("%d", &n) != 1 || n <= 0)
				while (getchar() != '\n')
					continue;

			mystrncpy(s1, s2, n);
			while (getchar() != '\n')
				continue;
			printf("So the string s1 has been changed to \"%s\"\n\n", s1);
			printf("You can enter s1 again:\n");
		
		}
		
	}
	printf("Done!\n\n");
}


void eatline(void)
{
	//清空输出行
	while (getchar() != '\n')
		continue;
}
int get_choice(void)
{
	//获取列表选项
	int ch;
	do
	{
		ch = tolower(getchar());
	} while (isspace(ch));
	eatline();
	printf("i entered %c\n", ch);
	return ch;
	
}
void print_str(char* str[], int n)
{
	//直接打印字符串
	printf("Source string:\n");
	for (int i = 0; i < n; i++)
	{
		puts(str[i]);
	}
	putchar('\n');
	return;
}
void ascii_print_str(char* str[], int n)
{
	//按ascii码顺序打印字符串
	char* temp;
	for (int top = 0; top < n-1; top++)
	{
		for (int seek = top + 1; seek < n; seek++)
		{
			if (strcmp(str[top], str[seek]) > 0)
			{
				temp = str[top];
				str[top] = str[seek];
				str[seek] = temp;
			}
		}
	}

	print_str(str, n);
	return;
}
void len_print_str(char* str[], int n)
{
	//按字符串长度递增打印字符串
	char* temp;
	for (int top = 0; top < n-1; top++)
	{
		for (int seek = top + 1; seek < n; seek++)
		{
			if (strlen(str[top]) > strlen(str[seek]))
			{
				temp = str[top];
					str[top] = str[seek];
					str[seek] = temp;
			}
		}
		
	}

	print_str(str, n);
	return;
}
int word(char* str)
{
	int length = 0;

	/*统计字符串第一个非空白字符的单词
	长度并作为返回值传递给调用函数;*/
	while (isspace(*str))
	{
		str++;
	}
	while (*str != '\0')
	{
		length++;
		str++;
	}
	return length;
}
void first_print_str(char* str[], int n)
{
	//按第一个单词长度顺序打印字符串
	char* temp;
	for (int top = 0; top < n - 1; top++)
	{
		for (int seek = top+1; seek < n; seek++)
		{
			if (word(str[top]) > word(str[seek]) )
			{
				temp = str[top];
				str[top] = str[seek];
				str[seek] = temp;
			}
		}
	}
	print_str(str, n);
	return;
}
void p11_11()
{
#define ROWS 3
#define COLUMNS 20
	char str[ROWS][COLUMNS];//字符串二维数组
	char* ptstr[ROWS];//内含指针变量的数组。
	int n = 0;
	int ch;
	printf("Please Enter %d strings (EOF to quit):\n",ROWS);
	while (s_gets(str[n], COLUMNS))
	{
		ptstr[n] = str[n];//设置指针指向字符串
		n++;
		if (n >= ROWS)
			break;
	}
	

	if (n != 0)
	{
		printf("You can choose one of the following opinions:\n "
			"\tA.Print string directively.\n"
			"\tB.Print string in order of ASCII order.\n"
			"\tC.Print string in order of length of strings.\n"
			"\tD.Print string in order of length of first word.\n"
			"\tE.Quit.\n"
		);
		while ((ch = get_choice()) != 'e')
		{
			printf("You have chosen %c\n", ch);
			switch (ch)
			{
			case 'a':
			{
				print_str(ptstr, n);
				break;
			}
			case 'b':
			{
				ascii_print_str(ptstr, n);
				break;
			}
			case 'c':
			{
				len_print_str(ptstr, n);
				break;
			}
			case 'd':
			{
				first_print_str(ptstr, n);
				break;
			}
			default:
			{
				printf("Entered wrong.\n");
				break;
			}

			}
		
			printf("You can choose one of the following opinions:\n "
				"\tA.Print string directively.\n"
				"\tB.Print string in order of ASCII order.\n"
				"\tC.Print string in order of length of strings.\n"
				"\tD.Print string in order of length of first word.\n"				
				"\tE.Quit.\n"
				);
		}
	

	}
	else
	{
		printf("You entered nothing.\n");
	}
	printf("DONE!\n\n");
	return;

}


void p11_13(void)
{
	char b[3][8] = {"in","my","heart"};
	char* a[3] = {NULL,NULL,NULL};
		
	for (int i = 0; i < 3; i++)
	{
		*(a+i) = b[i];
		printf("%s\nadress: %p\na(adress) is %p, a(char)is %c, \n", a[i],a[i],*(a[i]+1),*(a[i]+1));
		
	}
	
}