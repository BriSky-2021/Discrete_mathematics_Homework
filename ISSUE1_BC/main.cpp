#include<iostream>

using namespace std;
const int VARIABLE_SIZE = 52;

//���һ�����ʽ�Ƿ������ţ�����У��������������ŵ�ǰ��λ��
bool isBracket(const string&formula,int &possrc,int &posend ) {
	bool isRight = false;
	for (int i=0; i < (int)formula.length();i++) {
		if (formula[i] == '(') {
			isRight = true;
			possrc = i;
		}
		else if (formula[i] == ')') {
			if (isRight == true) {
				posend = i;
				return true;
			}
			else return false;
		}
	}
	return false;
}



//�����㺯������������������
string operateString(const string &target) {
	int possrc=0, posend=0;
	string target_cpy = target;
	while (true) {
		//��������ţ����ҵ���С�����ţ������ڲ����в�����Ȼ���޸����ַ���
		if (isBracket(target_cpy, possrc, posend) == true) {
			cout << "���������ţ�λ��Ϊ" << possrc << " " << posend << endl;
			string tmp = operateString(target_cpy.substr(possrc+1, posend - possrc-1));//�������Ŵ���ȥ
			cout << "�滻ǰΪ" << target_cpy << endl;
			target_cpy.replace(possrc, posend-possrc+1, tmp);
			cout << "���滻Ϊ" << target_cpy<<endl;
		}
		//û������ʱ�������ȼ����������������
		else {
			//������!
			int characterPos = (int)target_cpy.find('!');
			//�ҵ���!����������
			if (characterPos != string::npos) {
				cout << "�ҵ���!" << endl;
				cout << "��ǰΪ" << target_cpy << endl;
				char characterGet = target_cpy[characterPos + 1];
				string replaceString;
				switch (characterGet) {
				case'!':
					characterGet = '\0';
					break;
				case'0':
					characterGet = '1';
					break;
				case'1':
					characterGet = '0';
					break;
				default:
					characterGet = '\0';
					break;
				}
				//characterGet = ('1' == characterGet) ? '0' : '1';
				target_cpy.replace(characterPos, 2, string("")+characterGet);
				cout << "�滻��Ϊ" << target_cpy << endl;
				continue;
			}
			else {
				//������ʱд������Ϊֹ,��һ����������̺�����
				return target_cpy;

			}


		}
	}

}



int main() {

	string formula;
	cout << "������һ����ʽ" << endl;
	cin >> formula;
	char* variable=new char[VARIABLE_SIZE];
	memset(variable, 0, VARIABLE_SIZE);
	int variable_max=0;
	for (auto i : formula) {
		if (isalpha(i)) {
			variable[i - 'A']++;
			if (variable[i - 'A'] == 1)
				variable_max++;
		}
	}
	cout << "��������Ϊ" << variable_max << endl;
	if (!variable_max) {
		cout << "���ʽ�������" << endl;
	}

	//���б��ʽ�ĸ�ֵ

	formula.assign("!!(!!(1))");

	cout<<operateString(formula);


	delete[] variable;
	return 0;
}