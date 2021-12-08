#include<iostream>
#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
	int a[4];
	int i = -1, j = -1;
	char s;
	//int backtotop = 0;
	while (1) {
		printf("***************************************\n");  //标语
		printf("**                                   **\n");
		printf("**        欢迎进入逻辑运算程序       **\n");
		printf("**                                   **\n");
		printf("***************************************\n\n");
		printf("\n  请输入P的值（0或1）,以回车结束:");
		cin >> i;  //读取P的值
		if (i != 0 && i != 1||!cin.good())
		{
			printf("\n  P的值输入有误,请重新输入!");
			Sleep(2000);
			system("cls");  //清屏
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		printf("\n  请输入Q的值（0或1）,以回车结束:");
		cin >> j;  //读取Q的值
		if (j != 0 && j != 1 || !cin.good())
		{
			printf("\n  Q的值输入有误,请重新输入!");
			Sleep(2000);
			system("cls");  //清屏
			cin.clear();
			cin.ignore(1024, '\n');

			continue;
		}
		a[0] = i && j;  //与运算
		a[1] = i || j;  //或运算
		a[2] = (!i) || j;  //蕴含运算，将其转化为与或非形式
		a[3] = ((!i) || j) && ((!j) || i);  //等值运算，将其转化为与或非形式
		printf("\n\n  合取:\n       P/\\Q = %d\n", a[0]);  //输出结果
		printf("  析取:\n       P\\/Q = %d\n", a[1]);
		printf("  条件:\n       P->Q = %d\n", a[2]);
		printf("  双条件:\n       P<->Q = %d\n", a[3]);
		while (1) {
			printf("\n是否继续运算?（y/n）");  //询问是否继续操作
			cin >> s;
			if (s == 'y' || s == 'n')
			{
				if (s == 'y')
				{
					system("cls");  //清屏
					//backtotop = 1;
					break;
				}
				else
				{
					printf("欢迎下次再次使用!\n");  //退出
					exit(0);
				}
			}
			else
			{
				printf("输入错误,请重新输入!\n"); //错误校验
				cin.clear();
				cin.ignore(1024, '\n');
				continue;
			}
		}

	}
	
	
	return 0;
}
