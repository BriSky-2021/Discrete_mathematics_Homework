#include<iostream>
#include<sstream>
using namespace std;

//���뺯��

#if defined(WIN32)
#include<Windows.h>
//��ʱ��������λms
void wyt_sleep(int ms)
{
	Sleep(ms);
}
#endif

#if defined(linux)||defined(__linux__)
#include<unistd.h>
//��ʱ��������λms
void wyt_sleep(int ms)
{
	usleep(1000 * ms);
}
#endif

/*
�����������ʾ���½磬�Ͻ�
*/
int NumberInput(const char* a, int LowerBound, int UpperBound)
{
	while (1) {

		cout << a << "     " << "\b\b\b\b\b";
		int value;
		cin >> value;
		if (cin.good() && value >= LowerBound && value <= UpperBound)
		{
			return value;
		}
		else
		{
			cout << "�����������������\n";
			cin.clear();
			cin.ignore(1024, '\n');
		}
	}

}


/*
�����������ʾ���½磬�Ͻ�
*/
int AlphaInput(const char* a, int LowerBound, int UpperBound)
{
	while (1) {
		cout << a;
		char value;
		cin >> value;
		if (value >= LowerBound && value <= UpperBound)
		{
			return value;
		}
		else
		{
			cout << "\n�����������������\n";
			cin.clear();
			cin.ignore();
		}
	}
}







//��С��:

const static int DEFAULTSIZE = 100;

template<typename E>
class MinHeap {
private:
	E* Head;
	int CurrentSize;
	int MaxSize;
	//��start��m�»�
	void siftDown(int start, int m);
	//��start��0����
	void siftUp(int start);
public:
	MinHeap(int size = DEFAULTSIZE);
	//MinHeap(E[], int n);
	~MinHeap();
	bool insert(const E& content);
	bool removeMin(E& x);
	bool isEmpty() { return CurrentSize == 0; };
	bool IsFull() { return CurrentSize == MaxSize; };
	//�ֶ�ɾ������Ԫ��
	void makeEmpty();
};


template<typename E>
MinHeap<E>::MinHeap(int size) {
	if (size <= 0) size = DEFAULTSIZE;
	Head = new E[size];
	MaxSize = size;
	CurrentSize = 0;
	if (!Head) {
		cerr << "�Ѵ����ڴ����ʧ��" << endl;
		exit(1);
	}
}


template<typename E>
MinHeap<E>::~MinHeap() {
	if (Head)
		delete[] Head;
}

template<typename E>
void MinHeap<E>::siftDown(int start, int m) {
	int i = start, j = 2 * i + 1;
	E temp = Head[i];
	while (j <= m) {
		//��jָ�������ӵĽ�Сֵ
		if (j<m && Head[j]>Head[j + 1])j++;
		//������׽�С�����˳�
		if (temp <= Head[j])break;
		//���������
		else {
			Head[i] = Head[j];
			i = j;
			j = 2 * j + 1;
		}
	}
	Head[i] = temp;
}

template<typename E>
void MinHeap<E>::siftUp(int start) {
	int j = start, i = (j - 1) / 2;
	E temp = Head[j];
	while (j > 0) {
		//������׽�С�����˳�
		if (temp >= Head[i])break;
		//���������
		else {
			Head[j] = Head[i];
			j = i;
			i = (i - 1) / 2;
		}
	}
	Head[j] = temp;
}


template<typename E>
bool MinHeap<E>::insert(const E& content) {
	if (CurrentSize == MaxSize) {
		cerr << "������" << endl;
		return 0;
	}
	Head[CurrentSize] = content;
	siftUp(CurrentSize);
	CurrentSize++;
	return 1;
}


template<typename E>
bool MinHeap<E>::removeMin(E& x) {
	if (CurrentSize == 0) {
		cerr << "�ѿ���" << endl;
		return 0;
	}
	x = Head[0];
	Head[0] = Head[CurrentSize - 1];
	--CurrentSize;
	siftDown(0, CurrentSize - 1);
	return 1;
}

template<typename E>
void MinHeap<E>::makeEmpty() {
	E x;
	while (!isEmpty()) {
		removeMin(x);
	}
}


//�ݴ���
class heapnode {
public:
	int weight = 0;
	int isyezi = 0;
	heapnode* left = NULL;
	heapnode* right = NULL;
	void del(heapnode* now) {
		if (!now)return;
		if (now->left)del(now->left);
		if (now->right)del(now->right);
	}
	~heapnode() {
		del(this);
	}
	heapnode() {
		weight = 0;
		isyezi = 0;
		left = NULL;
		right = NULL;
	}

	void nodecpy(const heapnode* source) {
		if (!source)return;
		weight = source->weight;
		isyezi = source->isyezi;
		if (source->left) {
			left = new heapnode;
			left->nodecpy(source->left);
		}
		if (source->right) {
			right = new heapnode;
			right->nodecpy(source->right);
		}
		return;

	}
	heapnode(heapnode& x) {
		this->nodecpy(&x);
	}

	heapnode& operator=(const heapnode& x) {
		this->nodecpy(&x);
		return *this;
	}


	void static_display(const heapnode* source,string info) {
		if (source->isyezi == 1) {
			cout << source->weight << " " << info << endl;
			return;
		}
		if (source->left) {
			static_display(source->left, info + '0');
		}
		if (source->right) {
			static_display(source->right, info + '1');
		}
		return;
	}

	void display() {
		
		static_display(this, string(""));
	}

	friend bool operator >=(const heapnode a, const heapnode b) {
		return a.weight >= b.weight;
	}
	friend bool operator <=(const heapnode a, const heapnode b) {
		return a.weight <= b.weight;
	}
	friend bool operator >(const heapnode a, const heapnode b) {
		return a.weight > b.weight;
	}
	friend bool operator <(const heapnode a, const heapnode b) {
		return a.weight < b.weight;
	}
	friend bool operator ==(const heapnode a, const heapnode b) {
		return a.weight >= b.weight;
	}
	friend bool operator !=(const heapnode a, const heapnode b) {
		return a.weight >= b.weight;
	}
};




//������:

int main(int argc, char* argv[]) {
	int nodes;
	string tips;
	stringstream tipsbuffer;
	cout << ("������ڵ����(������������):");
	nodes = NumberInput("������ڵ����(������������),С��100:", 1, 100);
	int* head = new int[nodes];
	heapnode tmp;
	MinHeap<heapnode> MyHeap;
	cout << "����ڵ�" << endl;
	for (int i = 0; i < nodes; i++) {
		tipsbuffer.str("");
		tipsbuffer.clear();
		tips.assign("");
		tipsbuffer << "�������";
		tipsbuffer << i;
		tipsbuffer << "���ڵ�Ľڵ�ֵ";
		tipsbuffer >> tips;
		head[i] = NumberInput(tips.c_str(), 1, INT_MAX);
		tmp.weight = head[i];
		tmp.isyezi = 1;
		MyHeap.insert(tmp);
	}


	do {
		heapnode tmp_a, tmp_b;
		MyHeap.removeMin(tmp_a);
		if (MyHeap.isEmpty() == true) {
			tmp = tmp_a;
			break;
		}
		MyHeap.removeMin(tmp_b);

		tmp.weight = tmp_a.weight + tmp_b.weight;
		tmp.isyezi = 0;
		tmp.left = new heapnode;
		tmp.right = new heapnode;
		*tmp.left = tmp_a;
		*tmp.right = tmp_b;
		MyHeap.insert(tmp);

		delete tmp.left;
		delete tmp.right;

	} while (!MyHeap.isEmpty());



	cout << endl;
	tmp.display();

	delete[] head;

	system("pause");
	return 0;
}





