#include<iostream>
#include "stdlib.h"
using namespace std;
void output(int s[][100]);
void zifan(int s2[][100]);
void duichen(int s2[][100]);
void chuandi(int s2[][100]);
void select();
void exit();
int s[100][100], z;
int d, n, i, j;

int main()
{
	select();
	return 0;
}

void select()
{
	cout<<("请输入矩阵的行数:");
	cin >> n;
	cout<<("请输入矩阵的列数:");
	cin >> d;
	cout<<("请输入关系矩阵:\n");
	for (i = 0; i < n; i++)
	{
		cout << endl;
		cout << "请输入矩阵的第" << i << "行元素(元素以空格分隔" << endl;;
		for (j = 0; j < d; j++)
			cin>>s[i][j];
	}
	cout<<("输入对应序号选择算法\nl:自反闭包\n2:传递闭包\n3:对称闭包\n4:退出\n");
	cin >> z;
	switch (z)
	{
	case 1:zifan(s); break;
	case 2:chuandi(s); break;
	case 3:duichen(s); break;
	case 4:exit(); break;
	}
}

void output(int s[][100])
{
	cout<<("所求关系矩阵为:\n");
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < d; j++)
			cout<<s[i][j];
		cout << endl;
	}
}

void zifan(int s2[][100])
{
	for (i = 0; i < n; i++)
		s2[i][i] = 1;
	output(s2);
	select();
}

void duichen(int s2[][100])
{
	int s1[100][100];
	for (i = 0; i < n; i++)
		for (j = 0; j < d; j++)
			s1[j][i] = s2[i][j];
	for (i = 0; i < n; i++)
		for (j = 0; j < d; j++)
		{
			s2[i][j] = s2[i][j] + s1[i][j];
			if (s2[i][j] > 1)
				s2[i][j] = 1;
		}
	output(s2);
	select();
}

void chuandi(int s2[][100])
{
	int m[100][100], a[100][100], k, h;
	int t[100][100];
	for (i = 0; i < n; i++)
		for (j = 0; j < d; j++)
		{
			a[i][j] = 0;
			t[i][j] = s2[i][j];
			m[i][j] = s2[i][j];
		}
	for (h = 0; h < n; h++)
	{
		for (i = 0; i < n; i++)
			for (j = 0; j < d; j++)
				if (m[i][j] == 1)
				{
					for (k = 0; k < n; k++)
						if (s2[j][k] == 1)
							a[i][k] = 1;
				}
		for (i = 0; i < n; i++)
			for (j = 0; j < d; j++)
			{
				m[i][j] = a[i][j];
				t[i][j] += a[i][j];
				a[i][j] = 0;
				if (t[i][j] > 1)
					t[i][j] = 1;
			}
	}

	output(t);
	select();
}

void exit()
{
	exit(1);
}
