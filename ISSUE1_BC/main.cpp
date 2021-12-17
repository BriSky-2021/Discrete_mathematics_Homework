#include<iostream>

using namespace std;
const int VARIABLE_SIZE = 52;
const bool IS_TEST = false;

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
			if(IS_TEST)
				cout << "发现了括号，位置为" << possrc << " " << posend << endl;
			string tmp = operateString(target_cpy.substr(possrc+1, posend - possrc-1));//不把括号传过去
			if (IS_TEST)
				cout << "替换前为" << target_cpy << endl;
			target_cpy.replace(possrc, posend-possrc+1, tmp);
			if (IS_TEST)
				cout << "已替换为" << target_cpy<<endl;
		}
		//没有括号时按照优先级找运算符进行运算
		else {
			//首先是!
			int characterPos = (int)target_cpy.find('!');
			//找到了!，进行运算
			if (characterPos != string::npos) {
				if (IS_TEST) {
					cout << "找到了!" << endl;
					cout << "当前为" << target_cpy << endl;
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
					cout << "替换后为" << target_cpy << endl;
				continue;
			}
			else {
				int characterPos_and = (int)target_cpy.find('&');
				//找到了与运算
				if (characterPos_and != string::npos) {
					if (IS_TEST) {
						cout << "找到了&" << endl;
						cout << "当前为" << target_cpy << endl;
					}
					char cha1=target_cpy[characterPos_and - 1];
					char cha2=target_cpy[characterPos_and + 1];
					if(cha1==cha2 && cha1=='1')
						target_cpy.replace(characterPos_and-1, 3,"1");
					else
						target_cpy.replace(characterPos_and-1, 3,"0");
					if (IS_TEST)
						cout << "替换后为" << target_cpy << endl;
					continue;
				}else{

					int characterPos_or = (int)target_cpy.find('|');
					//找到了或运算
					if (characterPos_or != string::npos) {
						if (IS_TEST) {
							cout << "找到了|" << endl;
							cout << "当前为" << target_cpy << endl;
						}
						char cha1=target_cpy[characterPos_or - 1];
						char cha2=target_cpy[characterPos_or + 1];
						if(cha1=='1'||cha2=='1')
							target_cpy.replace(characterPos_or-1, 3,"1");
						else
							target_cpy.replace(characterPos_or-1, 3,"0");
						if (IS_TEST)
							cout << "替换后为" << target_cpy << endl;
						continue;
					}else{
						int characterPos_logic = (int)target_cpy.find('^');
						//找到了蕴含运算
						if (characterPos_logic != string::npos) {
							if (IS_TEST) {
								cout << "找到了^" << endl;
								cout << "当前为" << target_cpy << endl;
							}
							char cha1=target_cpy[characterPos_logic - 1];
							char cha2=target_cpy[characterPos_logic + 1];
							if(cha1=='0'||cha2=='1')
								target_cpy.replace(characterPos_logic-1, 3,"1");
							else
								target_cpy.replace(characterPos_logic-1, 3,"0");
							if (IS_TEST)
								cout << "替换后为" << target_cpy << endl;
							continue;
						}
						else{
							int characterPos_equal = (int)target_cpy.find('~');
							//找到了等值运算
							if (characterPos_equal != string::npos){
								if (IS_TEST) {
									cout << "找到了~" << endl;
									cout << "当前为" << target_cpy << endl;
								}
								char cha1=target_cpy[characterPos_equal - 1];
								char cha2=target_cpy[characterPos_equal + 1];
								if(cha1==cha2)
									target_cpy.replace(characterPos_equal-1, 3,"1");
								else
									target_cpy.replace(characterPos_equal-1, 3,"0");
								if (IS_TEST)
									cout << "替换后为" << target_cpy << endl;
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
	cout<<"***************************************\n";  //标语
	cout << "**                                   **\n";
	cout << "**         欢迎进入逻辑运算软件      **\n";
	cout << "**   (可运算真值表,主范式,支持括号)  **\n";
	cout << "**                                   **\n";
	cout << "**              用!表示非            **\n";
	cout << "**              用&表示与            **\n";
	cout << "**              用|表示或            **\n";
	cout << "**             用^表示蕴含           **\n";
	cout << "**             用~表示等值           **\n";
	cout << "**                                   **\n";
	cout << "***************************************\n\n";
	cout << "请输入一个合法的命题公式:\n";  //输入式子
}

int main() {

	string formula;//公式
	displayTips();
	//cout << "请输入一个公式" << endl;
	cin >> formula;
	char* variable=new char[VARIABLE_SIZE];
	memset(variable, 0, VARIABLE_SIZE);
	int variable_max=0;//变量个数
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

	int* myPointor = new int[variable_max];//标识第几个变量在52个字母中的位置
	int flag = 0;//第几个变量的标识
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
	//保留范式的值
	int* fanshi = new int[((int)1) << variable_max];

	//进行2的variable_max次循环赋值
	for (int i = 0; i < ((int)1) << variable_max; i++) {//i是第几轮循环，从0开始
		formula_cpy = formula;
		for (int k = 0; k < variable_max; k++) {//k是正在替换第几个字母
			bool replaceValue = i & (1 << (variable_max - k - 1));
			int chaPos = 0;
			while ((chaPos = (int)formula_cpy.find('A'+myPointor[k])) != string::npos) {//找到了第k个字母
				formula_cpy.replace(chaPos, 1, string("")+(char)(replaceValue + '0'));
			}
			cout << (char)(replaceValue + '0')<<" ";
		}
		//cout << "第" << i << "轮替换为" << formula_cpy << endl;
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

	//输出主析取范式
	cout << "主析取范式是";
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
	//输出主合取范式1
	cout << "主合取范式是";
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

	cout << "欢迎下次使用" << endl;

	system("pause");
	return 0;
}