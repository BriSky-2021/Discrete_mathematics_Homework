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

const static int DEFAULTSIZE = 10;

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

//��ͨ������
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
	/*��member�ӵ�first���¼�
		pos:posΪ1�����
			posΪ2���ұ�
	*/
	bool add(const tree_node<T>* first, const T member, int pos = 1);
	/*
		��child�ڵ��Լ���֮�µ����нڵ�ӵ�first���¼�
		pos��ʾλ��:�����(1)���Ҷ���(2)
		�ɹ�����0
	*/
	//bool add(const tree_node<T>* first, tree_node<T>* child, int pos = 1);

	//��first��Ϊmember
	void change(const tree_node<T>* first, const T member);
	/*�Ƴ��ڵ㼰�����ڵ�
	*/
	void remove(tree_node<T>*& member);

	void previsit(const tree_node<T>* now, void bianli(const T* i));
	void midvisit(const tree_node<T>* now, void bianli(const T* i));
	void aftvisit(const tree_node<T>* now, void bianli(const T* i));
};


/*
	��nowָ����ָ�Ľ�㿪ʼ���µݹ�ɾ��
*/
template<typename T>
void Tree_normal<T>::del(const tree_node<T>* now)
{
	if (!now)return;//nowָ��Ϊ��
	//if ((!now->rlink) && (!now->llink)) {//�����ӽڵ��Ϊ��
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
	��nowָ����ָ�Ľ�㿪ʼ���±������ҵ�ֵΪmember�Ľڵ��ָ�룬������ָ��
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
	tree_node<T>* fa = (tree_node<T>*)Father;//�ҵ�ֵΪFather��ָ��
	fa->content = member;
	return;
}



template<typename T>
void Tree_normal<T>::remove(tree_node<T>*& Father) {
	//tree_node<T>* fa =(tree_node<T>*) Father;//�ҵ�ֵΪFather��ָ��
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

//�ݴ�ṹ��
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



//���ı�������
void bianli(const heapnode* opt) {

	if (opt->isYezi == 1) {
		cout << opt->rank << " " << opt->TreeValue << endl;
	}


}



//������:

int main(int argc, char* argv[]) {

	//���Ȼ�ȡ�ڵ�
	int nodes,*Array;
	nodes = NumberInput("������ڵ����(������������),С��100:", 1, 100);
	Array = new int[nodes];
	cout << ("������ڵ�(�Կո�ָ�):");
	string tips ;
	stringstream tipsbuffer;
	//��������ʼ������
	MinHeap<heapnode> myheap(nodes);
	heapnode last;
	//��ȡ�ڵ�ֵ
	for (int i = 0; i < nodes; i++) {
		tipsbuffer.str("");
		tipsbuffer << "�������"<<i<<"���ڵ�Ľڵ�ֵ";
		tipsbuffer >> tips;
		Array[i] = NumberInput(tips.c_str(), 1, INT_MAX);
		heapnode tmp(i, Array[i]);
		myheap.insert(tmp);
	}

	//��ʼ����
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

	//���������

	delete[] Array;
}


