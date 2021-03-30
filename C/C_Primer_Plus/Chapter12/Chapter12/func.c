#include <stdio.h>
#include "func.h"


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
    for (int row = 0; row < 10; row++)
    {
        for (int i = 0; i < n / 10; i++)
        {
            printf("%-4d", arr[10 * row + i]);
        }
        putchar('\n');
    }
   
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