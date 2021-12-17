
#include<iostream>
#include<cstring>
using namespace std;

//�߼�������
class matrix {
private:
	int ROW_MAX;
	int COL_MAX;
	int* head;

public:
	matrix() { ROW_MAX = 0; COL_MAX = 0; head = NULL; }
	matrix(const matrix&);
	~matrix() { if (head)delete[] head; };
	int getMaxCol()const { return COL_MAX; }
	int getMaxRow()const { return ROW_MAX; }

	int get_cell(int row, int col)const { return head[row * COL_MAX + col]; }

	void set_row_and_col(int row, int col) {
		ROW_MAX = row; COL_MAX = col;
		head = new int[row * col];
		memset(head, 0, row * col * sizeof(int));//incase there is a problem with
	}

	bool input_cell (int row, int col, int Value) {
		if (row<0 || row>ROW_MAX - 1 || col<0 || col>COL_MAX - 1) {
			return 1;
		}
		head[row * COL_MAX + col] = Value;
		return 0;
	}

	void display() {

		if (!head)return;
		for (int i = 0; i < this->ROW_MAX; i++) {

			for (int k = 0; k < this->COL_MAX; k++) {

				cout << get_cell(i, k) << ' ';
			}
			cout << endl;
		}

	}

	friend bool operator==(const matrix& x1, const matrix& x2);
	matrix& operator=(const matrix& b);
	friend matrix operator+ (const matrix& x1, const matrix& x2);
	friend matrix operator* (const matrix& x1, const matrix& x2);

};


matrix::matrix(const matrix& b) {

	this->set_row_and_col(b.getMaxRow(), b.getMaxCol());
	for (int i = 0; i < ROW_MAX; i++) {

		for (int k = 0; k < COL_MAX; k++) {
			this->input_cell(i, k, b.get_cell(i, k));
		}

	}

}


bool operator==(const matrix& x1, const matrix& x2) {
	if (x1.getMaxCol() != x2.getMaxCol() || x1.getMaxRow() != x2.getMaxRow()) {
		cerr << "���в��ȵıȽ�" << endl;
		return 0;
	}
	return memcmp(x1.head, x2.head, x1.COL_MAX * x1.ROW_MAX * sizeof(int))==0?1:0;

}

matrix& matrix::operator=(const matrix& b) {

	this->set_row_and_col(b.getMaxRow(), b.getMaxCol());
	for (int i = 0; i < ROW_MAX; i++) {

		for (int k = 0; k < COL_MAX; k++) {
			this->input_cell(i,k,b.get_cell(i,k));
		}

	}
	return *this;
}


matrix operator+ (const matrix& x1, const matrix& x2) {
	
	if (x1.getMaxCol() != x2.getMaxCol() || x1.getMaxRow() != x2.getMaxRow()) {
		exit(1);
		cerr << "������ӵľ������в���ͬ" << endl;
	}
	matrix sum;
	int ROW_MAX = x1.getMaxRow();
	int COL_MAX= x1.getMaxCol();
	sum.set_row_and_col(ROW_MAX, COL_MAX);
	for (int i = 0; i < ROW_MAX; i++) {

		for (int k = 0; k < COL_MAX; k++) {
			int sumvalue = (x1.get_cell(i,k) + x2.get_cell(i,k)>=1?1:0);
			sum.input_cell(i, k, sumvalue);
		}

	}
	return  sum;
}

matrix operator* (const matrix& x1, const matrix& x2) {

	if (x1.getMaxCol() != x2.getMaxRow()) {
		exit(1);
		cerr << "������˵ľ������в�ƥ��:	��ߵ���Ϊ"<< x1.getMaxCol()\
			<<"�ұߵ���Ϊ" << x2.getMaxRow()<<endl;
	}
	matrix sum;
	int ROW_MAX = x1.getMaxRow();
	int COL_MAX = x2.getMaxCol();
	sum.set_row_and_col(ROW_MAX, COL_MAX);
	for (int i = 0; i < ROW_MAX; i++) {

		for (int k = 0; k < COL_MAX; k++) {
			int sumvalue = 0;
			for (int r = 0; r < x1.getMaxCol(); r++) {

				sumvalue += x1.get_cell(i, r) && x2.get_cell(r, k);
			}
			sumvalue = sumvalue > 0 ? 1 : 0;
			sum.input_cell(i, k, sumvalue);
		}

	}
	return sum;
}


//���ܲ��Ժ���
void test();
void reflexive(matrix*);
void symmetry(matrix*);
void transfer(matrix*);




int main() {
	if(0)
		test();
	
	int max_row, max_col;
	matrix MyMatrix;
	cout<<("����������������:");
	cin >> max_row;
	max_col = max_row;
	MyMatrix.set_row_and_col(max_row, max_col);
	cout<<("�������ϵ����:\n");

	for (int i = 0; i < max_row; i++)
	{
		cout<<"\n";
		cout<<"���������ĵ�"<<i<<"��Ԫ��(Ԫ���Կո�ָ�):";
		for (int j = 0; j < max_col; j++) {
			bool get;
			cin >> get;
			MyMatrix.input_cell(i, j, get);
		}
			
	}

	cout << "��ǰ����Ϊ" << endl;
	MyMatrix.display();
	matrix mycpy=MyMatrix;
	while (true) {
		MyMatrix = mycpy;
		cout << ("�����Ӧ���ѡ���㷨\nl:�Է��հ�\n2:���ݱհ�\n3:�ԳƱհ�\n4:�˳�\n");
		int whattodo;
		cin >> whattodo;
		switch (whattodo)
		{
		case 1:
			reflexive(&MyMatrix);
			break;
		case 2:
			transfer(&MyMatrix);
			break;
		case 3:
			symmetry(&MyMatrix);

			break;
		default:
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return 1;
			break;
		}

		cout << "����Ϊ" << endl;
		MyMatrix.display();
	}
	

	return 0;
}

//�Է�
void reflexive(matrix* a) {
	int n = a->getMaxRow();

	for (int i = 0; i < n; i++) {
		a->input_cell(i, i, 1);
	}
}

//�Գ�
void symmetry(matrix* a) {
	int n = a->getMaxRow();

	for (int i = 0; i < n; i++) {
		
		for (int k = i+1; k < n; k++) {

			int judge = a->get_cell(i, k) || a->get_cell(k, i);
			a->input_cell(i, k, judge);
			a->input_cell(k, i, judge);

		}

	}

}


//����
void transfer(matrix* a) {

	int n = a->getMaxRow();
	matrix b;
	b.set_row_and_col(n, n);

	for (int i = 0; i < n; i++) {

		//�ҵ�������ֵ�ĵ�
		for (int m = 0; m < n; m++) {
			for (int d = 0; d < n; d++) {
				if (a->get_cell(m, d) == 1) {
					//�����ڵ��ж�Ӧ����Ѱ�ҿ��Դ��ݵĵ�
					for (int r = 0; r < n; r++)
						if (a->get_cell(d, r) == 1)
							b.input_cell(m, r, 1);
				}

			}


		}
		//��һ��ֵ
		*a = b;


	}


}




void test() {
	if (1) {
		//���ܲ���
		matrix trail1, trail2;
		trail1.set_row_and_col(4, 4);
		trail2.set_row_and_col(4, 4);
		int data1[] = {
			1,0,0,1,
			0,1,0,1,
			0,0,1,1,
			1,1,1,1
		};
		int data2[] = {
			0,1,0,1,
			0,1,1,1,
			0,0,0,1,
			1,0,0,1

		};
		for (int i = 0; i < 4; i++) {

			for (int k = 0; k < 4; k++) {

				trail1.input_cell(i, k, data1[i * 4 + k]);
				trail2.input_cell(i, k, data2[i * 4 + k]);
			}

		}
		cout << "��һ��������" << endl;
		trail1.display();
		cout << "�ڶ���������" << endl;
		trail2.display();

		matrix trail3;
		trail3 = trail1 + trail2;
		cout << "�;�����" << endl;
		trail3.display();

		matrix trail4;
		trail4 = trail1 * trail2;
		cout << "�˷�������" << endl;
		trail4.display();

		matrix trail5 = trail4;
		cout << "�Ƚ��Ƿ���ͬ�Ľ����" << endl;
		cout << (trail5 == trail4) << endl;
		cout << "�Ƚ��Ƿ���ͬ�Ľ����" << endl;
		cout << (trail5 == trail3) << endl;


	}


}