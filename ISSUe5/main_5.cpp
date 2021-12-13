#include<iostream>
#include<sstream>
using namespace std;

//输入函数

#if defined(WIN32)
#include<Windows.h>
//延时函数，单位ms
void wyt_sleep(int ms)
{
	Sleep(ms);
}
#endif

#if defined(linux)||defined(__linux__)
#include<unistd.h>
//延时函数，单位ms
void wyt_sleep(int ms)
{
	usleep(1000 * ms);
}
#endif

/*
输入参数：提示，下界，上界
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
			cout << "输入错误，请重新输入\n";
			cin.clear();
			cin.ignore(1024, '\n');
		}
	}

}


/*
输入参数：提示，下界，上界
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
			cout << "\n输入错误，请重新输入\n";
			cin.clear();
			cin.ignore();
		}
	}
}







//最小堆:

const static int DEFAULTSIZE = 100;

template<typename E>
class MinHeap {
private:
	E* Head;
	int CurrentSize;
	int MaxSize;
	//从start向m下滑
	void siftDown(int start, int m);
	//从start向0上升
	void siftUp(int start);
public:
	MinHeap(int size = DEFAULTSIZE);
	//MinHeap(E[], int n);
	~MinHeap();
	bool insert(const E& content);
	bool removeMin(E& x);
	bool isEmpty() { return CurrentSize == 0; };
	bool IsFull() { return CurrentSize == MaxSize; };
	//手动删除所有元素
	void makeEmpty();
};


template<typename E>
MinHeap<E>::MinHeap(int size) {
	if (size <= 0) size = DEFAULTSIZE;
	Head = new E[size];
	MaxSize = size;
	CurrentSize = 0;
	if (!Head) {
		cerr << "堆创建内存分配失败" << endl;
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
		//让j指向两孩子的较小值
		if (j<m && Head[j]>Head[j + 1])j++;
		//如果父亲较小，则退出
		if (temp <= Head[j])break;
		//否则就下移
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
		//如果父亲较小，则退出
		if (temp >= Head[i])break;
		//否则就上升
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
		cerr << "堆满了" << endl;
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
		cerr << "堆空了" << endl;
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


//暂存类
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




//主函数:

int main(int argc, char* argv[]) {
	int nodes;
	string tips;
	stringstream tipsbuffer;
	cout << ("请输入节点个数(必须是正整数):");
	nodes = NumberInput("请输入节点个数(必须是正整数),小于100:", 1, 100);
	int* head = new int[nodes];
	heapnode tmp;
	MinHeap<heapnode> MyHeap;
	cout << "输入节点" << endl;
	for (int i = 0; i < nodes; i++) {
		tipsbuffer.str("");
		tipsbuffer.clear();
		tips.assign("");
		tipsbuffer << "请输入第";
		tipsbuffer << i;
		tipsbuffer << "个节点的节点值";
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





