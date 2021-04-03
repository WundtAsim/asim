#include <stdio.h>
#include "func.h"


/*-------------p13_1-------------*/
void p13_1(void)
{
    printf("Enter the file name you want to check: ");
    char file_name[30];
    while (fscanf_s(stdin,"%s", file_name,30) != 1)
    {
        fprintf(stderr,"Usage : filename\n");
        exit(EXIT_FAILURE);
    }
    strcat_s(file_name,sizeof file_name,"\0");
    printf("So, the file name is %s, hah!\n", file_name);
    FILE* fp;
    fopen_s(&fp, file_name, "r+");
    if (fp == NULL)
    {
        fprintf(stderr, "Can't open file %s\n",file_name);
        exit(EXIT_FAILURE);
    }
    printf("the file %s has already opened. \n", file_name);

    int ch;
    while ((ch = getc(fp)) != EOF)
        putc(ch, stdout);
    putchar('\n');
    for(int i = 0; i < (int)strlen(file_name); i++)
    {
        printf("the %dst character is %c\n",i,file_name[i]);
        putc(file_name[i], fp);
    }



    if (fclose(fp))
        printf("Error in closing file %s", file_name);
    else
        printf("Thank God! The file has been closed.\n");

    fp = NULL;

    return;
}

/*-------------p12_9-------------*/

void p12_9(void)
{
    printf("How many wordsdo you wisn to enter? \n");
    int n;
    scanf_s("%d", &n);
    printf("Enter your %d words now:\n", n);

    char** words;
    int len;
    char temp[100] = {0};
    if (words = (char**)malloc(n * sizeof(char*)))
    {
        for (int i = 0; i < n; i++)
        {
          scanf_s("%s", temp,99);
          len = strlen(temp) + 1;
          words[i] = (char*)malloc(len * sizeof(char));
          if (NULL == words[i])
          {
              printf("Memory allocation failed!\n");
              exit(-1);
          }
          strcpy_s(words[i],len, temp);
          //数组不要过界：中间为缓冲区大小。
          puts(words[i]);
          //↑从临时数组中把单词拷贝到动态分配的存储空间中;
        }

        printf("Here are your %d words:\n", n);
        for (int i = 0; i < n; i++)
        {
            puts(words[i]);
            free(words[i]);
          //  words[i] = NULL;
        }
        free(words);
     //   words = NULL;
        //↑指针仍然指向malloc分配的存储空间;
        //↑因此令指针指向NULL后防止内存滥用;

    }
    else
    {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

        
}

/*-------------p12_8-------------*/
int* make_array(int elem, int val)
{ 
    int* p = NULL;
    p = (int*)malloc(elem * sizeof(int));
    if (p == NULL)
    {
        puts("Memory allocation failed,Goodbye.");
        exit(EXIT_FAILURE);
    }
   
    for (int i = 0; i < elem; i++)
    {
        p[i] = val;
    }       
    return p;
}
void p12_8(void)
{
    int* pa;
    int size;
    int value;
    printf("Enter the number of elements: ");
    while (scanf_s("%d", &size)== 1 && size>0)
    {
        printf("Enter the initialization value: ");
        scanf_s("%d", &value);
        pa = make_array(size, value);
        if (pa)
        {
            show_array(pa, size);
            free(pa);

        }
        printf("Enter the number of elements (< 1 to quit): ");
    }
    printf("Done!\n");
}

/*-------------p12_6-------------*/
void occur_times(int *arr,int n, int j)
{
    int count = 0;
    int* p;
    p = arr;
    for (int i = 0; i < n; i++)
    {
        if (j == *p++)
            count++;
    }
    printf("Number %d occurs %d times\n", j, count);
    return;
}
void p12_6(void)
{
#define LEN 1000
    unsigned int seed = 11;
    for (int time = 0; time < 10; time++)
    {
        seed += time;
        srand((unsigned int)seed);
        int arr[LEN];
        for (int i = 0; i < LEN; i++)
        {
            arr[i] = rand() % 10 + 1;
        }
        for (int j = 1, count = 0; j < 11; j++)
        {
            occur_times(arr, LEN, j);
        }
        putchar('\n');
    }
    printf("Test completed!\n");
  
}

/*-------------p12_5-------------*/

void show_array(const int *arr, int n)
{
   
        for (int i = 0; i < n; i++)
        {

            printf("%-4d", arr[i]);
            if (!((i+1)% 8) )
                putchar('\n');
        }
        putchar('\n');
    
   
}
void sort(int *arr, int n)
{
    int temp;
    for (int i = 0; i < n-1; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] > arr[i])
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}
void p12_5(void)
{
#define LEN 100
    int arr[LEN];
    srand((unsigned int)time(0));
    for (int i = 0; i < LEN; i++)
    {
        arr[i] = rand() % 10 + 1;
    }
    printf("Array is:\n");
    show_array(arr, LEN);
    sort(arr, LEN);
    printf("After sorting is:\n");
    show_array(arr, LEN);

}

/*-------------p12_4-------------*/
int counter(void)
{
    static int count;
    return ++count;
}
void p12_4(void)
{
    for (int i = 0; i < 8; i++)
    {
        counter();
    }
    printf("the function counter has been called %d times.\n", counter()-1);
    return;
}

/*----------------------------------p12_2-------------------------*/
static int mode;
static double distance;
static double fuel;
void set_mode(int n)
{
    if (n > 1)
    {
        printf("Invalid mode specified. Mode %s used.\n",
            (0 == mode) ? "0(metric)" : "1(US)");
    }
    else
    {
        mode = n;
    }
    return;

}
void get_info()
{
	printf("Enter distance traveled in %s:\n",
        (0 == mode) ? "kilmoters" : "miles" );
    scanf_s("%lf", &distance);

    printf("Enter fuel comsumed in %s:\n",
        (0 == mode) ? "liters" : "gallons");
    scanf_s("%lf", &fuel);

}
void show_info()
{
    printf("Fuel consumption is %g %s:\n",
        (0 == mode) ? fuel/100/distance : distance/fuel,
        (0 == mode) ? "liters/100km" : "miles/gallons");
}