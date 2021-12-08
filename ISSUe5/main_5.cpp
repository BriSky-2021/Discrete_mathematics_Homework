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

//普通二叉树
template<typename T>
struct tree_node {
	T content;
	tree_node<T>* pre = NULL;
	tree_node<T>* rlink = NULL;
	tree_node<T>* llink = NULL;
	tree_node(T cpy) {
		content = cpy;
		tree_node<T>* pre = NULL;
		tree_node<T>* rlink = NULL;
		tree_node<T>* llink = NULL;
	}
	tree_node() {
		tree_node<T>* pre = NULL;
		tree_node<T>* rlink = NULL;
		tree_node<T>* llink = NULL;
	}
};




template<typename T>
class Tree_normal {
protected:
	void del(const tree_node<T>* now);
public:
	tree_node<T>* head;
	Tree_normal() { head = new tree_node<T>; }
	Tree_normal(T ancestor) { head = new tree_node<T>; head->content = ancestor; }
	~Tree_normal();
	tree_node<T>* find(tree_node<T>* now, const T member);
	/*把member加到first的下级
		pos:pos为1：左边
			pos为2：右边
	*/
	bool add(const tree_node<T>* first, const T member, int pos = 1);
	/*
		把child节点以及其之下的所有节点加到first的下级
		pos表示位置:左儿子(1)与右儿子(2)
		成功返回0
	*/
	//bool add(const tree_node<T>* first, tree_node<T>* child, int pos = 1);

	//把first改为member
	void change(const tree_node<T>* first, const T member);
	/*移除节点及后续节点
	*/
	void remove(tree_node<T>*& member);

	void previsit(const tree_node<T>* now, void bianli(const T* i));
	void midvisit(const tree_node<T>* now, void bianli(const T* i));
	void aftvisit(const tree_node<T>* now, void bianli(const T* i));
};


/*
	从now指针所指的结点开始往下递归删除
*/
template<typename T>
void Tree_normal<T>::del(const tree_node<T>* now)
{
	if (!now)return;//now指针为空
	//if ((!now->rlink) && (!now->llink)) {//两个子节点均为空
	//	delete now;
	//	return;
	//}
	if (now->llink) {
		del(now->llink);
	}
	if (now->rlink) {
		del(now->rlink);
	}
	delete now;
}


/*
	从now指针所指的结点开始往下遍历，找到值为member的节点的指针，并返回指针
*/
template<typename T>
tree_node<T>* Tree_normal<T>::find(tree_node<T>* now, const T member)
{
	if (now->content == member)
		return now;
	if ((!now->llink) && (!now->rlink)) {
		return NULL;
	}
	tree_node<T>* ret;
	if (now->llink)
		if (ret = find(now->llink, member))
			return ret;
	if (now->rlink)
		if (ret = find(now->rlink, member))
			return ret;
	return NULL;
}



template<typename T>
bool Tree_normal<T>::add(const tree_node<T>* first, const T member, int pos) {
	tree_node<T>* fa = (tree_node<T>*)first;
	switch (pos) {
	case 1:
		if (fa->llink)return 1;
		fa->llink = new tree_node<T>;
		fa->llink->content = member;
		fa->llink->pre = fa;
		break;
	default:
		if (fa->rlink)return 1;
		fa->rlink = new tree_node<T>;
		fa->rlink->content = member;
		fa->rlink->pre = fa;
		break;
	}


	return 0;
}




template<typename T>
void Tree_normal<T>::change(const tree_node<T>* Father, const T member) {
	tree_node<T>* fa = (tree_node<T>*)Father;//找到值为Father的指针
	fa->content = member;
	return;
}



template<typename T>
void Tree_normal<T>::remove(tree_node<T>*& Father) {
	//tree_node<T>* fa =(tree_node<T>*) Father;//找到值为Father的指针
	del(Father);
	Father = NULL;
}

template<typename T>
Tree_normal<T>::~Tree_normal() {
	del(head);
	head = NULL;
}

template<typename T>
void Tree_normal<T>::previsit(const tree_node<T>* now, void bianli(const T* i)) {
	bianli(&(now->content));
	if (now->llink)previsit(now->llink, bianli);
	if (now->rlink)previsit(now->rlink, bianli);
}

template<typename T>
void Tree_normal<T>::midvisit(const tree_node<T>* now, void bianli(const T* i)) {
	if (now->llink)midvisit(now->llink, bianli);
	bianli(&(now->content));
	if (now->rlink)midvisit(now->rlink, bianli);
}

template<typename T>
void Tree_normal<T>::aftvisit(const tree_node<T>* now, void bianli(const T* i)) {
	if (now->llink)aftvisit(now->llink, bianli);
	if (now->rlink)aftvisit(now->rlink, bianli);
	bianli(&(now->content));
}

//暂存结构体
struct heapnode {
	int sum;
	bool isYezi;
	string TreeValue ;
	int rank;
	heapnode() { sum = 0; rank = 0; isYezi = 0; TreeValue =""; }
	heapnode(int Rank,int Sum) { sum =Sum; isYezi = 1; TreeValue = ""; rank = Rank; }
	bool operator >(heapnode& x) { return sum > x.sum; };
	bool operator ==(heapnode& x) { return sum == x.sum; };
	bool operator <(heapnode& x) { return sum < x.sum; };
	bool operator >=(heapnode& x) { return sum >= x.sum; };
	bool operator <=(heapnode& x) { return sum <= x.sum; };
	bool operator !=(heapnode& x) { return sum != x.sum; };

};



//树的遍历函数
void bianli(const heapnode* opt) {

	if (opt->isYezi == 1) {
		cout << opt->rank << " " << opt->TreeValue << endl;
	}


}



//主函数:

int main(int argc, char* argv[]) {

	//首先获取节点
	int nodes,*Array;
	nodes = NumberInput("请输入节点个数(必须是正整数),小于100:", 1, 100);
	Array = new int[nodes];
	cout << ("请输入节点(以空格分隔):");
	string tips ;
	stringstream tipsbuffer;
	//接下来开始构建树
	MinHeap<heapnode> myheap(nodes);
	heapnode last;
	//获取节点值
	for (int i = 0; i < nodes; i++) {
		tipsbuffer.str("");
		tipsbuffer << "请输入第"<<i<<"个节点的节点值";
		tipsbuffer >> tips;
		Array[i] = NumberInput(tips.c_str(), 1, INT_MAX);
		heapnode tmp(i, Array[i]);
		myheap.insert(tmp);
	}

	//开始构建
	Tree_normal<heapnode> hoffmanTree;
	while (true) {

		heapnode h1,h2;
		myheap.removeMin(h1);
		myheap.removeMin(h2);
		heapnode h3;
		h3.sum = h1.sum + h2.sum;
		h1.TreeValue = h1.TreeValue + "0";
		h2.TreeValue = h2.TreeValue + "1";
		if (myheap.isEmpty()) {
			last = h3;
			break;
		}
		myheap.insert(h3);
	}

	//现在输出树

	delete[] Array;
}


