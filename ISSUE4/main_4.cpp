


#include<iostream>
using namespace std;


//并查集：
struct JointNode {
	int father;
	int rank;
};

class JointGather {
	int maxlen;
	JointNode* head;
public:
	~JointGather();
	int find(int n);
	JointGather(int len);
	int merge(int m, int n);
};

JointGather::JointGather(int len) {
	maxlen = len;
	head = new JointNode[len];
	for (int i = 0; i < len; i++) {
		head[i].father = i;
		head[i].rank = 1;
	}

}

JointGather::~JointGather()
{
	if (head)delete[] head;
}

int JointGather::find(int n) {
	if (head[n].father == n)
		return n;
	else
		return head[n].father = find(head[n].father);
}


int JointGather::merge(int m, int n) {
	int a = find(m), b = find(n);
	if (a == b)return 1;
	if (head[a].rank > head[b].rank)
		head[b].father = a;
	else
		head[a].father = b;
	if (head[a].rank == head[b].rank)
		head[a].rank = ++(head[b].rank);
	return 0;
}

//最小堆:

const static int DEFAULTSIZE = 10;

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


//边的结构体
template<typename E>
struct Distance {
	int v1;
	int v2;
	E weight;
	bool operator >(Distance& x) { return weight > x.weight; };
	bool operator ==(Distance& x) { return weight == x.weight; };
	bool operator <(Distance& x) { return weight < x.weight; };
	bool operator >=(Distance& x) { return weight >= x.weight; };
	bool operator <=(Distance& x) { return weight <= x.weight; };
	bool operator !=(Distance& x) { return weight != x.weight; };
	friend istream& operator >>(istream& in, Distance<E>& dis) {
		in >> dis.v1 >> dis.v2 >> dis.weight;
		return in;
	}
};



//主函数:
int main() {

	int verticles, edges;
	cout << ("请输入所求图的顶点数目和边的数目(以空格分隔各个数，输入两个0结束):\n");
	cin >> verticles >> edges;
	if ((verticles == edges) && !verticles) {
		cout << "输入了两个0,程序结束" << endl;
		return 0;
	}
	int count = 0;

	Distance<double> *key=new Distance<double>[edges];
	JointGather mygather(verticles);
	MinHeap<Distance<double>> myheap(edges);
	Distance<double> mydistance;
	for (int i = 0; i < edges; i++) {

		cout << "正在输入第" << i + 1 << "条边,请输入两条边的节点序号以及它们的权值(以空格分隔各个数):\n";
		cin >> mydistance;
		myheap.insert(mydistance);
	}

	while (!myheap.isEmpty()) {

		myheap.removeMin(mydistance);
		int v1 = mydistance.v1;
		int v2 = mydistance.v2;
		double weight = mydistance.weight;

		if (mygather.find(v1-1) != mygather.find(v2-1)) {
			mygather.merge(v1-1, v2-1);
			key[count++] = mydistance;
		}

	}

	//接下来输出耗费
	double sum=0;
	for (int i = 0; i < count; i++) {
		cout << "最小耗费为" << key[i].v1 << " " << key[i].v2 << endl;
		sum += key[i].weight;
	}
	cout << "总耗费是" << sum << endl;

	delete[] key;
	system("Pause");
}



