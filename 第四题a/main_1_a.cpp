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
		cout<<"***************************************\n";  //����
		cout<<"**                                   **\n";
		cout<<"**        ��ӭ�����߼��������       **\n";
		cout<<"**                                   **\n";
		cout<<"***************************************\n\n";
		cout<<"\n  ������P��ֵ��0��1��,�Իس�����:";
		cin >> i;  //��ȡP��ֵ
		if (i != 0 && i != 1||!cin.good())
		{
			cout<<"\n  P��ֵ��������,����������!";
			Sleep(2000);
			system("cls");  //����
			cin.clear();
			cin.ignore(1024, '\n');
			continue;
		}
		cout<<"\n  ������Q��ֵ��0��1��,�Իس�����:";
		cin >> j;  //��ȡQ��ֵ
		if (j != 0 && j != 1 || !cin.good())
		{
			printf("\n  Q��ֵ��������,����������!");
			Sleep(2000);
			system("cls");  //����
			cin.clear();
			cin.ignore(1024, '\n');

			continue;
		}
		a[0] = i && j;  //������
		a[1] = i || j;  //������
		a[2] = (!i) || j;  //�̺����㣬����ת��Ϊ������ʽ
		a[3] = ((!i) || j) && ((!j) || i);  //��ֵ���㣬����ת��Ϊ������ʽ
		cout<<"\n\n  ��ȡ:\n       P/\\Q = "<<a[0]<<endl;  //������
		cout<<"  ��ȡ:\n       P\\/Q = "<<a[1]<<endl;
		cout<<"  ����:\n       P->Q = " << a[2] << endl;
		cout << "  ˫����:\n       P<->Q = " << a[3] << endl;
		while (1) {
			cout<<"\n�Ƿ��������?��y/n��";  //ѯ���Ƿ��������
			cin >> s;
			if (s == 'y' || s == 'n')
			{
				if (s == 'y')
				{
					system("cls");  //����
					//backtotop = 1;
					break;
				}
				else
				{
					printf("��ӭ�´��ٴ�ʹ��!\n");  //�˳�
					exit(0);
				}
			}
			else
			{
				printf("�������,����������!\n"); //����У��
				cin.clear();
				cin.ignore(1024, '\n');
				continue;
			}
		}

	}
	
	
	return 0;
}
