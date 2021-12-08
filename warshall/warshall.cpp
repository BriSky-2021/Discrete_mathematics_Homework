#include<iostream>
#include<cstring>
using namespace std;

//逻辑矩阵类
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

	bool input_cell(int row, int col, int Value) {
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
		cerr << "行列不等的比较" << endl;
		return 0;
	}
	return memcmp(x1.head, x2.head, x1.COL_MAX * x1.ROW_MAX * sizeof(int)) == 0 ? 1 : 0;

}

matrix& matrix::operator=(const matrix& b) {

	this->set_row_and_col(b.getMaxRow(), b.getMaxCol());
	for (int i = 0; i < ROW_MAX; i++) {

		for (int k = 0; k < COL_MAX; k++) {
			this->input_cell(i, k, b.get_cell(i, k));
		}

	}
	return *this;
}


matrix operator+ (const matrix& x1, const matrix& x2) {

	if (x1.getMaxCol() != x2.getMaxCol() || x1.getMaxRow() != x2.getMaxRow()) {
		exit(1);
		cerr << "进行相加的矩阵行列不相同" << endl;
	}
	matrix sum;
	int ROW_MAX = x1.getMaxRow();
	int COL_MAX = x1.getMaxCol();
	sum.set_row_and_col(ROW_MAX, COL_MAX);
	for (int i = 0; i < ROW_MAX; i++) {

		for (int k = 0; k < COL_MAX; k++) {
			int sumvalue = (x1.get_cell(i, k) + x2.get_cell(i, k) >= 1 ? 1 : 0);
			sum.input_cell(i, k, sumvalue);
		}

	}
	return  sum;
}

matrix operator* (const matrix& x1, const matrix& x2) {

	if (x1.getMaxCol() != x2.getMaxRow()) {
		exit(1);
		cerr << "进行相乘的矩阵行列不匹配:	左边的列为" << x1.getMaxCol()\
			<< "右边的行为" << x2.getMaxRow() << endl;
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



void transfer(matrix*);




int main() {


	int max_row, max_col;
	matrix MyMatrix;
	cout << ("请输入矩阵的行列数:");
	cin >> max_row;
	max_col = max_row;
	MyMatrix.set_row_and_col(max_row, max_col);
	cout << ("请输入关系矩阵:\n");

	for (int i = 0; i < max_row; i++)
	{
		cout << "\n";
		cout << "请输入矩阵的第" << i << "行元素(元素以空格分隔):";
		for (int j = 0; j < max_col; j++) {
			bool get;
			cin >> get;
			MyMatrix.input_cell(i, j, get);
		}

	}

	cout << "当前矩阵为" << endl;
	MyMatrix.display();

	transfer(&MyMatrix);


	cout << "传递后为" << endl;
	MyMatrix.display();

	system("pause");
	return 0;
}





//传递
void transfer(matrix* a) {

	int n = a->getMaxRow();

	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				a->input_cell(i, j, a->get_cell(i, j) || a->get_cell(i, k) && a->get_cell(k, j) ? 1 : 0);
				//A[i][j] = A[i][j] == 1 || A[i][k] == 1 && A[k][j] == 1 ? 1 : 0;
			}
		}
	}

}

