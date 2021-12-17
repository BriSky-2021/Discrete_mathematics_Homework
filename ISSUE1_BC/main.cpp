#include<iostream>

using namespace std;
const int VARIABLE_SIZE = 52;
const bool IS_TEST = false;

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
			if(IS_TEST)
				cout << "���������ţ�λ��Ϊ" << possrc << " " << posend << endl;
			string tmp = operateString(target_cpy.substr(possrc+1, posend - possrc-1));//�������Ŵ���ȥ
			if (IS_TEST)
				cout << "�滻ǰΪ" << target_cpy << endl;
			target_cpy.replace(possrc, posend-possrc+1, tmp);
			if (IS_TEST)
				cout << "���滻Ϊ" << target_cpy<<endl;
		}
		//û������ʱ�������ȼ����������������
		else {
			//������!
			int characterPos = (int)target_cpy.find('!');
			//�ҵ���!����������
			if (characterPos != string::npos) {
				if (IS_TEST) {
					cout << "�ҵ���!" << endl;
					cout << "��ǰΪ" << target_cpy << endl;
				}
				
				char characterGet = target_cpy[characterPos + 1];
				string replaceString;
				switch (characterGet) {
				case'!':
					characterGet = NULL;
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
				if(characterGet)
					target_cpy.replace(characterPos, 2, string("")+characterGet);
				else
					target_cpy.replace(characterPos, 2, string(""));
				if (IS_TEST)
					cout << "�滻��Ϊ" << target_cpy << endl;
				continue;
			}
			else {
				int characterPos_and = (int)target_cpy.find('&');
				//�ҵ���������
				if (characterPos_and != string::npos) {
					if (IS_TEST) {
						cout << "�ҵ���&" << endl;
						cout << "��ǰΪ" << target_cpy << endl;
					}
					char cha1=target_cpy[characterPos_and - 1];
					char cha2=target_cpy[characterPos_and + 1];
					if(cha1==cha2 && cha1=='1')
						target_cpy.replace(characterPos_and-1, 3,"1");
					else
						target_cpy.replace(characterPos_and-1, 3,"0");
					if (IS_TEST)
						cout << "�滻��Ϊ" << target_cpy << endl;
					continue;
				}else{

					int characterPos_or = (int)target_cpy.find('|');
					//�ҵ��˻�����
					if (characterPos_or != string::npos) {
						if (IS_TEST) {
							cout << "�ҵ���|" << endl;
							cout << "��ǰΪ" << target_cpy << endl;
						}
						char cha1=target_cpy[characterPos_or - 1];
						char cha2=target_cpy[characterPos_or + 1];
						if(cha1=='1'||cha2=='1')
							target_cpy.replace(characterPos_or-1, 3,"1");
						else
							target_cpy.replace(characterPos_or-1, 3,"0");
						if (IS_TEST)
							cout << "�滻��Ϊ" << target_cpy << endl;
						continue;
					}else{
						int characterPos_logic = (int)target_cpy.find('^');
						//�ҵ����̺�����
						if (characterPos_logic != string::npos) {
							if (IS_TEST) {
								cout << "�ҵ���^" << endl;
								cout << "��ǰΪ" << target_cpy << endl;
							}
							char cha1=target_cpy[characterPos_logic - 1];
							char cha2=target_cpy[characterPos_logic + 1];
							if(cha1=='0'||cha2=='1')
								target_cpy.replace(characterPos_logic-1, 3,"1");
							else
								target_cpy.replace(characterPos_logic-1, 3,"0");
							if (IS_TEST)
								cout << "�滻��Ϊ" << target_cpy << endl;
							continue;
						}
						else{
							int characterPos_equal = (int)target_cpy.find('~');
							//�ҵ��˵�ֵ����
							if (characterPos_equal != string::npos){
								if (IS_TEST) {
									cout << "�ҵ���~" << endl;
									cout << "��ǰΪ" << target_cpy << endl;
								}
								char cha1=target_cpy[characterPos_equal - 1];
								char cha2=target_cpy[characterPos_equal + 1];
								if(cha1==cha2)
									target_cpy.replace(characterPos_equal-1, 3,"1");
								else
									target_cpy.replace(characterPos_equal-1, 3,"0");
								if (IS_TEST)
									cout << "�滻��Ϊ" << target_cpy << endl;
								continue;


							}else return target_cpy;

						}

					}
					
				}

					
				

			}


		}
	}

}

void displayTips() {
	cout<<"***************************************\n";  //����
	cout << "**                                   **\n";
	cout << "**         ��ӭ�����߼��������      **\n";
	cout << "**   (��������ֵ��,����ʽ,֧������)  **\n";
	cout << "**                                   **\n";
	cout << "**              ��!��ʾ��            **\n";
	cout << "**              ��&��ʾ��            **\n";
	cout << "**              ��|��ʾ��            **\n";
	cout << "**             ��^��ʾ�̺�           **\n";
	cout << "**             ��~��ʾ��ֵ           **\n";
	cout << "**                                   **\n";
	cout << "***************************************\n\n";
	cout << "������һ���Ϸ������⹫ʽ:\n";  //����ʽ��
}

int main() {

	string formula;//��ʽ
	displayTips();
	//cout << "������һ����ʽ" << endl;
	cin >> formula;
	char* variable=new char[VARIABLE_SIZE];
	memset(variable, 0, VARIABLE_SIZE);
	int variable_max=0;//��������
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

	int* myPointor = new int[variable_max];//��ʶ�ڼ���������52����ĸ�е�λ��
	int flag = 0;//�ڼ��������ı�ʶ
	for (int i = 0; i < VARIABLE_SIZE; i++) {
		if (variable[i]) {
			myPointor[flag++] = i;
		}
	}


	for (int i = 0; i < variable_max; i++) {
		cout << char(myPointor[i] + 'A') << " ";
	}
	cout << formula<<endl;

	string formula_cpy;
	//������ʽ��ֵ
	int* fanshi = new int[((int)1) << variable_max];

	//����2��variable_max��ѭ����ֵ
	for (int i = 0; i < ((int)1) << variable_max; i++) {//i�ǵڼ���ѭ������0��ʼ
		formula_cpy = formula;
		for (int k = 0; k < variable_max; k++) {//k�������滻�ڼ�����ĸ
			bool replaceValue = i & (1 << (variable_max - k - 1));
			int chaPos = 0;
			while ((chaPos = (int)formula_cpy.find('A'+myPointor[k])) != string::npos) {//�ҵ��˵�k����ĸ
				formula_cpy.replace(chaPos, 1, string("")+(char)(replaceValue + '0'));
			}
			cout << (char)(replaceValue + '0')<<" ";
		}
		//cout << "��" << i << "���滻Ϊ" << formula_cpy << endl;
		string theget = operateString(formula_cpy);
		if (theget == "1") {
			fanshi[i] = 1;
		}
		else
		{
			fanshi[i] = 0;
		}
		cout <<"	"<< theget << endl;

	}

	//�������ȡ��ʽ
	cout << "����ȡ��ʽ��";
	bool isfirst = true;
	for (int i = 0; i < ((int)1) << variable_max; i++) {
		if (fanshi[i]) {
			if (!isfirst) { 
				cout << "/\\"; 
			}
			isfirst = false;
			cout << "m(" << i << ")";

		}
	}
	cout << endl;
	//�������ȡ��ʽ1
	cout << "����ȡ��ʽ��";
	isfirst = true;
	for (int i = 0; i < ((int)1) << variable_max; i++) {
		if (!fanshi[i]) {
			if (!isfirst) {
				cout << "\\/";
			}
			isfirst = false;
			cout << "M(" << i << ")";

		}
	}
	cout << endl;
	
	delete[] fanshi;
	delete[] myPointor;
	delete[] variable;

	cout << "��ӭ�´�ʹ��" << endl;

	system("pause");
	return 0;
}