#include<iostream>

using namespace std;
const int VARIABLE_SIZE = 52;

//检查一个表达式是否有括号，如果有，返回最里层的括号的前后位置
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



//主运算函数，不包括函数运算
string operateString(const string &target) {
	int possrc=0, posend=0;
	string target_cpy = target;
	while (true) {
		//如果有括号，先找到最小的括号，对其内部进行操作，然后修改主字符串
		if (isBracket(target_cpy, possrc, posend) == true) {
			cout << "发现了括号，位置为" << possrc << " " << posend << endl;
			string tmp = operateString(target_cpy.substr(possrc+1, posend - possrc-1));//不把括号传过去
			cout << "替换前为" << target_cpy << endl;
			target_cpy.replace(possrc, posend-possrc+1, tmp);
			cout << "已替换为" << target_cpy<<endl;
		}
		//没有括号时按照优先级找运算符进行运算
		else {
			//首先是!
			int characterPos = (int)target_cpy.find('!');
			//找到了!，进行运算
			if (characterPos != string::npos) {
				cout << "找到了!" << endl;
				cout << "当前为" << target_cpy << endl;
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
				cout << "替换后为" << target_cpy << endl;
				continue;
			}
			else {
				//本次暂时写到这里为止,下一次添加与或非蕴含运算
				return target_cpy;

			}


		}
	}

}



int main() {

	string formula;
	cout << "请输入一个公式" << endl;
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
	cout << "变量个数为" << variable_max << endl;
	if (!variable_max) {
		cout << "表达式输入错误" << endl;
	}

	//进行表达式的赋值

	formula.assign("!!(!!(1))");

	cout<<operateString(formula);


	delete[] variable;
	return 0;
}