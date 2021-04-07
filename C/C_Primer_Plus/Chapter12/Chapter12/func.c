#include <stdio.h>
#include "func.h"

/*-------------p13_12-------------*/
void eliminate_noise(char* filename,const int x,const int y)
{
    //打开文件
    FILE* fp;
    fopen_s(&fp, filename, "r+");
    if (fp == NULL)
    {
        printf("Can't open file %s.\n", filename);
        exit(EXIT_FAILURE);
    }
    printf("file %s opened.\n", filename);

    if (x <= 0 || y <= 0) {
        printf("行数或列数不合法！\n");
        exit(-1);
    }
    //消除噪声
    int** image = NULL;
    image = (int**)malloc(x * sizeof(int*));
    if (image == NULL)
        exit(EXIT_FAILURE);
    for (int i = 0; i < x; i++)
    {
        image[i] = (int*)malloc(y * sizeof(int));
        if (image[i] == NULL)
            exit(EXIT_FAILURE);
    }

    //写入数组
    
    for (int i = 0; i < x; i++)
    {
        int j = 0;
        int ch;
        while ((ch = getc(fp))!=EOF && ch!='\n')
        { 
            if (isdigit(ch))
            {
                image[i][j] = ch - '0';
                j++;
            }
            else
                continue;
          
        }
        for (int k = 0; k < y; k++)
            printf("%d ", image[i][k]); 
        putchar('\n');
    }
    //处理数组（消噪）
    for (int i = 0; i < x; i++){    
        for (int j = 0; j < y; j++) {
            //首行
            if (i == 0) {
                //左上顶点
                if (j == 0) {
                    if ((image[i][j] - image[i][j + 1]) > 1 && (image[i][j] - image[i + 1][j]) > 1)
                        image[i][j] = (image[i + 1][j] + image[i][j + 1]) / 2;
                }                    
                //右上顶点
                else if (j == y - 1) {
                    if ((image[i][j] - image[i][j - 1]) > 1 && (image[i][j] - image[i + 1][j]) > 1)
                        image[i][j] = (image[i + 1][j] + image[i][j - 1]) / 2;
                }                    
                //首行内点
                else {
                    if ((image[i][j] - image[i][j + 1]) > 1 && (image[i][j] - image[i + 1][j]) > 1 && (image[i][j] - image[i][j-1]) > 1)
                        image[i][j] = (image[i + 1][j] + image[i][j + 1] + image[i][j - 1]) / 3;
                }       
            }
            //尾行
            else if (i == x-1) {
                //左下顶点
                if (j == 0) {
                    if ((image[i][j] - image[i][j + 1]) > 1 && (image[i][j] - image[i - 1][j]) > 1)
                        image[i][j] = (image[i - 1][j] + image[i][j + 1]) / 2;
                }
                //右下顶点
                else if (j == y - 1) {
                    if ((image[i][j] - image[i][j - 1]) > 1 && (image[i][j] - image[i - 1][j]) > 1)
                        image[i][j] = (image[i - 1][j] + image[i][j - 1]) / 2;
                }
                //尾行内点
                else {
                    if ((image[i][j] - image[i][j - 1]) > 1 && (image[i][j] - image[i][j+1]) > 1 && (image[i][j] - image[i - 1][j]) > 1)
                        image[i][j] = (image[i][j-1] + image[i][j + 1] + image[i-1][j]) / 3;
                }
            }
            //首列内点
            if (j == 0) {  
                if (i == 0 || i == x - 1)
                    break;
                if ((image[i][j] - image[i+1][j]) > 1 && (image[i][j] - image[i][j + 1]) > 1 && (image[i][j] - image[i - 1][j]) > 1)
                   image[i][j] = (image[i+1][j] + image[i][j + 1] + image[i - 1][j]) / 3;                
            }
            //尾列内点
            else if (j == y-1) {
                if (i == 0 || i == x - 1)
                    break;
                if ((image[i][j] - image[i + 1][j]) > 1 && (image[i][j] - image[i][j - 1]) > 1 && (image[i][j] - image[i - 1][j]) > 1)
                    image[i][j] = (image[i + 1][j] + image[i][j - 1] + image[i - 1][j]) / 3;
            }

            //数组内部值：
            if ((image[i][j] - image[i + 1][j]) > 1 && (image[i][j] - image[i][j - 1]) > 1 && (image[i][j] - image[i - 1][j]) > 1 && (image[i][j] - image[i][j+1]) > 1) {
                image[i][j] = (image[i - 1][j] + image[i + 1][j] + image[i][j - 1] + image[i][j + 1]) / 4;
                printf("haha\n");
            }


        }

    }

    //写入文件
    rewind(fp);
    for (int j = 0; j < x; j++)
    {
        for (int i = 0; i < y; i++)
        {
            fprintf(fp, "%d", image[j][i]);
            if (i < y - 1)
                putc('-', fp);
            else
                putc('\n', fp);
        }
    }    

    //清理内存
    for (int i = 0; i < x; i++)
        free(image[i]);
    free(image);  

    fclose(fp);
    fp = NULL;
    return;
}

void p13_13(void)
{
    printf("Enter the number of x and y pixels:");
    int x_pixel, y_pixel;
    scanf_s("%5d%5d", &x_pixel, &y_pixel);
    //创建0-9代表的灰度图
    const char* imagedig = "imagedig.txt";
    FILE* fp_imagedig;
    fp_imagedig = openfile(imagedig);

    //将灰度数值写入文件
    srand((unsigned int)500);
    for (int j = 0; j < x_pixel; j++)
    {
        for (int i = 0; i < y_pixel; i++)
        {
            int roll;
            roll = rand() % 10;

            fprintf(fp_imagedig, "%d", roll);
            if (i < y_pixel-1)
                putc(' ', fp_imagedig);
            else
                putc('\n', fp_imagedig);
        }
    }
    fclose(fp_imagedig);
    fp_imagedig = NULL;

    //处理噪声
    eliminate_noise(imagedig, x_pixel, y_pixel);

    //读取灰度值文件
    fopen_s(&fp_imagedig, imagedig, "r+");
    if (fp_imagedig == NULL)
        exit(EXIT_FAILURE);
    int ch;
    int** dig = NULL;
    dig = (int**)malloc(x_pixel * sizeof(int*));
    if (dig == NULL)
        exit(EXIT_FAILURE);
    for (int i = 0; i < x_pixel; i++)
    {
        dig[i] = (int*)malloc(y_pixel * sizeof(int));
        if (dig[i] == NULL)
            exit(EXIT_FAILURE);
    }        
    
    int count = 0;//用于计数dig数组到末尾
    while ((ch = getc(fp_imagedig)) != EOF)
    {
        if ((isdigit(ch)))
        {
            dig[count / x_pixel][count % x_pixel] = ch - '0';
            /*多次调用malloc分配的地址不一定连续，因实际物理内存可能分页，所以间隔分配。
            * 因此不用下行代码↓
            //*(*dig + count) = ch - '0';
            printf("dig[%d] = %d, address:%p\n", 
                count, dig[count/x_pixel][count%x_pixel],&dig[count / x_pixel][count % x_pixel]);
            */
            count++;
            if (count > x_pixel * y_pixel - 1)
                break;//防止溢出数组！                       
        }
        else
            continue;
    }
    count = 0;
    printf("so the content is:\n");
    for (int i = 0; i < x_pixel; i++)
    {
        for (int j = 0; j < y_pixel; j++)
        {
            printf("%d ", dig[i][j]);
        }putchar('\n');
    }puts("\n\n");
    if(fclose(fp_imagedig))
        exit(EXIT_FAILURE);
    fp_imagedig = NULL;

    /// 画出对应图象
    printf("so the image is:\n");
    for (int i = 0; i < x_pixel; i++)
    {
        for (int j = 0; j < y_pixel; j++)
        {
            int temp = 0;
            switch (dig[i][j])
            {
            case 0:
            {
                temp = '\'';
                break;
            }
            case 1:
            {
                temp = '.';
                break;
            }
            case 2:
            {
                temp = ',';
                break;
            }
            case 3:
            {
                temp = '\"';
                break;
            }
            case 4:
            {
                temp = ':';
                break;
            }
            case 5:
            {
                temp = '-';
                break;
            }
            case 6:
            {
                temp = '+';
                break;
            }
            case 7:
            {
                temp = '*';
                break;
            }
            case 8:
            {
                temp = '%';
                break;
            }
            case 9:
            {
                temp = '#';
                break;
            }
            }
            printf("%c ",temp);
        }putchar('\n');
    }
    printf("Done!\n");

    
    for (int i = 0; i < x_pixel; i++)
        free(dig[i]);
    free(dig);
    return;

}

/*-------------p13_12-------------*/
FILE* openfile(char* filename)
{
    FILE* fp;
    fopen_s(&fp, filename, "w+");
    if (fp == NULL)
    {
        printf("Can't open file %s.\n", filename);
        exit(EXIT_FAILURE);
    }
    printf("file %s opened.\n", filename);
    return fp;
}
void p13_12(void)
{
    //创建0-9代表的灰度图
    char* imagedig = "imagedig.txt";
    FILE* fp_imagedig;
    fp_imagedig = openfile(imagedig);
    
    //将灰度数值写入文件
    srand((unsigned int)time(0));
    for (int j = 0; j < 20; j++)
    {
        for (int i = 0; i < 30; i++)
        {
            int roll;
            roll = rand() % 10 ;
            
            fprintf(fp_imagedig, "%d", roll);
            if (i < 29)
                putc(' ', fp_imagedig);
            else
                putc('\n', fp_imagedig);
        }
    }
    fclose(fp_imagedig);
    fp_imagedig = NULL;

    //读取灰度值文件
    fopen_s(&fp_imagedig, imagedig, "r+");
    if (fp_imagedig == NULL)
        exit(EXIT_FAILURE);    
    int ch;
    int dig[20][30];
    int(* temp)[30];
    temp = dig;//用于接收每个数字
    int count = 0;//用于计数dig数组到末尾
    while ((ch = getc(fp_imagedig)) != EOF)
    {        
        if ((isdigit(ch)))
        {
            *(*temp + count)= ch - '0';
            count++;
            if (count > 20 * 30-1)
                break;//防止溢出数组！                       
        }
        else
            continue;  
        
              
    }
    printf("so the content is:\n");
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            
            printf("%d ", dig[i][j]);
        }putchar('\n');
    }puts("\n\n");
    fclose(fp_imagedig);
    fp_imagedig = NULL;   

    /// 画出对应图象
    printf("so the image is:\n");
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            int temp;
            switch (dig[i][j])
            {
            case 0:
            {
                temp = '\'';
                break;
            }
            case 1:
            {
                temp = '.';
                break;
            }
            case 2:
            {
                temp = ',';
                break;
            }
            case 3:
            {
                temp = '\"';
                break;
            }
            case 4:
            {
                temp = ':';
                break;
            }
            case 5:
            {
                temp = '-';
                break;
            }
            case 6:
            {
                temp = '+';
                break;
            }
            case 7:
            {
                temp = '*';
                break;
            }
            case 8:
            {
                temp = '%';
                break;
            }
            case 9:
            {
                temp = '#';
                break;
            }
            }
            printf("%c ", temp);
            
        }putchar('\n');
    }
    printf("Done!\n");


    return;
    
}

/*-------------p13_10-------------*/
void p13_10(void)
{
    printf("Enter the finame of waht you want to demonstrate:");
    char file[30];
    scanf_s("%s", file, 30);
    FILE* fp;
    fopen_s(&fp, file, "r");
    if (fp==NULL)
    {
        printf("Can't open file %s", file);
        exit(EXIT_FAILURE);
    }
    printf("the file %s has been opened.\n", file);

    printf("Enter the location which you want to type:(nagative or q to quit)");
    long n;
    while ((1 == scanf_s("%ld", &n)) && n >= 0)
    {
        
        fseek(fp, 0L, SEEK_SET);
        if (0 == fseek(fp, n, SEEK_SET))
        {
            int ch;
            while (((ch = getc(fp)) != EOF) && ch != '\n')
            {
                putc(ch, stdout);
            }
            putchar('\n');
        }
        else
            exit(EXIT_FAILURE);
        
        printf("Enter the location which you want to type:(nagative or q to quit)");
    }
    fclose(fp); fp = NULL;
    printf("file has been closed.\n");
    return;
    
}

/*-------------p13_7-------------*/
void p13_7(void)
{
    //打开文件1
    printf("Enter the filename of the first one:");
    char file_1[30];
    scanf_s("%s", file_1,30);
    FILE* fp1;
    fopen_s(&fp1, file_1, "r");
    if (fp1 == NULL)
    {
        printf("Can't open file \"%s\"", file_1);
        exit(EXIT_FAILURE);
    }
    printf("file \"%s\" opened.\n", file_1);
    //打开文件2
    printf("Enter the filename of the second one:");
    char file_2[30];
    scanf_s("%s", file_2,30);
    FILE* fp2;
    fopen_s(&fp2, file_2, "r");
    if (fp2 == NULL)
    {
        printf("Can't open file \"%s\"", file_2);
        exit(EXIT_FAILURE);
    }
    printf("file \"%s\" opened.\n", file_2);

    int ch1 = 0, ch2 = 0;
    ch1 = getc(fp1);
    ch2 = getc(fp2);
    while (1)
    {
        while (ch1 != EOF)
        {            
            putc(ch1, stdout);  
            ch1 = getc(fp1);
            if (ch1 == '\n')
            {
                ch1 = getc(fp1);//若检测到换行，则跳过换行，并跳出循环
                break;
            }          
         
        }
        printf("\t");
        while (ch2 != EOF)
        {
            putc(ch2, stdout);
            ch2 = getc(fp2);
            if (ch2 == '\n')
            {
                ch2 = getc(fp2);//若检测到换行，则跳过换行，并跳出循环
                break;
            }

        }
        putchar('\n');

        if (feof(fp1) && feof(fp2))
        {
            break;
        }
       
    }
    fclose(fp1);
    fp1 = NULL;
    fclose(fp2);
    fp2 = NULL;
    return;
}

/*-------------p13_3-------------*/
int readfile(char* filename)
{
    FILE* fp;
    fopen_s(&fp, filename, "r+");
    if (fp == NULL)
    {
        fprintf(stderr, "Can't open file--%s !\n",filename);
        exit(EXIT_FAILURE);
    }
    fprintf(stdout, "file--%s opened!\n", filename);
    int ch,cnt = 0; 
    printf("file content:\n");
    while ((ch = getc(fp)) != EOF)
    {
        putc(ch, stdout);
        cnt++;
    }
    puts("\nDone!");
    printf("there are %d characters.\n", cnt);
    if (fclose(fp))
    {
        fprintf("Can't close file--%s", filename);
        exit(EXIT_FAILURE);
    }
    else
        fp = NULL;
        return 1;
}
void p13_3(void)
{
    printf("Enter the name of file you want to dispose:");
    char filename[30];
    fscanf_s(stdin, "%s", filename,30);
    readfile(filename);
    puts("\n\n");

    FILE* fp;
    fopen_s(&fp, filename, "r+");
    if (fp == NULL)
    {
        fprintf(stderr, "Can't open file--%s !\n", filename);
        exit(EXIT_FAILURE);
    }
    int ch;
    while (1)
    {
        ch = getc(fp);
        if (ch == EOF)
           break;
        else if(isalpha(ch))
        {
            fseek(fp, -1L, SEEK_CUR);
            putc(toupper(ch), fp);
            fseek(fp, 0L, SEEK_CUR);
        }
        else
        {
            fseek(fp, -1L, SEEK_CUR);
            putc(ch, fp);
            fseek(fp, 0L, SEEK_CUR);            
        }    
        
    }
    rewind(fp);
    fclose(fp);

    readfile(filename);
    return;
}

/*-------------p13_2-------------*/
int file_copy(FILE* source, FILE* destination)
{
    setvbuf(destination, NULL, _IOFBF, 256);
    char temp[256];
    size_t bytes;
    while ((bytes = fread(temp, sizeof(char), 256, source)) > 0)
    {
       
        fwrite(temp, sizeof(char), bytes, destination);
        printf("copying!\n");
    }
    printf("the bytes is %d\n", (int)bytes);
    if (fclose(source) || fclose(destination))
        return 0;
    else
    {
        source = NULL;
        destination = NULL;
        return 1;
    }
        
}
void p13_2(int argcount,char** argument)
{
    if (argcount < 3)
    {
        printf("Usage: %s source_file destination_file\n", argument[0]);
        exit(EXIT_FAILURE);
    }
    FILE* source_fp;
    fopen_s(&source_fp, argument[1], "rb");
    if (source_fp == NULL)
    {
        fprintf(stderr, "Can't open source file!\n");
        exit(EXIT_FAILURE);
    }
    printf("...source file has been opened.\n");

    FILE* destination_fp;
    fopen_s(&destination_fp, argument[2], "wb");
    if (!destination_fp)
    {
        fprintf(stderr, "Can't open destination file!\n");
        exit(EXIT_FAILURE);
    }
    printf("...destination file has been opened.\n");

    if (file_copy(source_fp, destination_fp) == 1)
        printf("file has been copyed!\n");
    else
        printf("Error while coping!\n");
    return;

}

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