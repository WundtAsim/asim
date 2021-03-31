#include <stdio.h>
#include "func.h"

int main(int argc, char* argv[])
{


	/*p12_9
	询问用户需要输入多少个单词，然后接受用户输入的单词，显示出来，使用malloc并 回答第一个问题（即需要输入多少个单词）
	创建一个动态数组，数组内含相应的指向char的指针。
	在读取字符串时，改程序应该吧单词读入一个临时的char数组，使用malloc分配足够的内存空间来存储单词。并把地址存入该指针数组。
	然后从临时数组中把单词拷贝到动态分配的内存空间中
	因此，有一个字符指针数组，每个指针指向一个对象，该对象正好能容纳被存储的特定单词，
	*/
	p12_9();


	/*p12_8
	提供make_array和show_array 的定义，完成该函数：
	makearray接收两个参数：int类型数组的元素个数，要赋给每个元素的值。
	该函数调用malloc创建一个大小合适的数组，将其每个元素设置为指定的值并返回一个指向该数组的指针。
	shouarray显示数组的内容，一行显示10个。
	p12_8();*/
	

	/*p12_6
	编写一个程序，生成1000个1~10范围内的随机数，不用保存或打印这些数字，近打印每个数出现的次数，
	用10个不同非种子值运行，生成的数字是否相同？这是一个测试特定随机数生成器随机性的方法
	p12_6();*/
	

	/*p12_5
	编写一个程序，生成100个1~10范围内的随机数，并以降序排列
	p12_5();*/

	/*p12-4
	*计算一个函数被返回的次数
	p12_4();
	*/	

	/*p12_2
	* 计算公制油耗或美式油耗
	//--------------p12_2-------------//
	int mode;

	printf("Enter 0 for metric mode, 1 for US mode:");
	scanf_s("%d", &mode);
	while (mode >= 0)
	{
		set_mode(mode);
		get_info();
		show_info();
		printf("Enter 0 for metric mode, 1for US mode");
		printf("(-1to quit):");
		scanf_s("%d", &mode);
	}
	printf("Done.\n");
	*/

	system("pause");
	return 0;
}