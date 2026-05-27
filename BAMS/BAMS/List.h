#pragma once

template<class T>
class Node {
public:
	T data;
	Node<T>* next;
	//节点的构造函数，方便只传入值；
	Node(const T& value) :data(value), next(nullptr) {};
};

template<class T>
class List {
public:
	List() :head(nullptr), tail(nullptr), cnt(0) {
	};
	bool empty() const{
		return cnt == 0;
	} 
	int size() const{
		return cnt;
	}
	Node<T>* getHead() const{
		return head;
	}
	//尾插；
	void push_back(const T& value);

	template<class Fkey>
	Node<T>* find(Fkey key) const;

	void clear();//清空

	~List() {//析构
		clear();
	}

	//防止浅拷贝出错：
	List<T>& operator=(const List<T>& other) = delete;
	List(const List<T>& other) = delete;

	template<class com>
	void sort(com cmp);//通用链表排序；


private:
	Node<T>* head;
	Node<T>* tail;
	int cnt;
};

template<class T>
void List<T>::clear() {
	Node<T>* p = head;
	while (p != nullptr) {
		Node<T>* ne = p->next;
		delete p;
		p = ne;
	}
	head = nullptr;
	tail = nullptr;
	cnt = 0;
}

template<class T>
void List<T>::push_back(const T& value)
{
	Node<T>* p_new = new Node<T>(value);
	if (head == nullptr) {
		head = p_new;
		tail = p_new;
	}
	else {
		tail->next = p_new;
		tail = p_new;
	}
	cnt++;
}

template<class T>
template<class Fkey>
Node<T>* List<T>::find(Fkey key) const {
	Node<T>* p = head;
	while (p != nullptr)
	{
		if (key(p->data)) {
			return p;
		}
		p = p->next;
	}
	return nullptr;
}

template<class T>
template<class com>
void List<T>::sort(com cmp) {
	// 通过交换节点中的 data 完成排序，不改变链表指针结构。
	for (Node<T>* i = head; i != nullptr; i = i->next) {
		for (Node<T>* j = i->next; j != nullptr; j = j->next) {
			if (cmp(j->data, i->data)) {
				T tmp = i->data;
				i->data = j->data;
				j->data = tmp;
			}
		}
	}
}