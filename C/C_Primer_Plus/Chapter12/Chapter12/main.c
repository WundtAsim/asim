#include <stdio.h>
#include "func.h"

int main(int argc, char* argv[])
{

	/*p12_6
	编写一个程序，生成1000个1~10范围内的随机数，不用保存或打印这些数字，近打印每个数出现的次数，
	用10个不同非种子值运行，生成的数字是否相同？这是一个测试特定随机数生成器随机性的方法
	*/
	p12_6();

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