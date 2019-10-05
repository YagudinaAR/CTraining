#include <iostream>
using namespace std;


template<class T>
class DoubleList;

class iterator;

template<class T>
class DoubleList
{
	struct Node
	{
		Node* prev;
		Node* next;
		T Value;

	public:
		Node() {};
		Node(T _val) : Value(_val) {};
		~Node() {};
	};

public:
	class iterator
	{
		Node* node;
	public:

		iterator() : node(nullptr) {};
		iterator(Node* p) : node(p) {};
		iterator(const iterator& it) : node(it.node) {};
		iterator& operator=(const iterator& it)
		{
			node = it.node;
			return *this;
		}

		iterator& operator++()
		{
			if (node == nullptr)
				throw "error when trying to increment empty iterator!";
			if (node->next == nullptr)
				throw "error when trying to increment last iterator!";
			node = node->next;
			return *this;
		}

		iterator& operator--()
		{
			if (node == nullptr)
				throw "error when trying to decrement empty iterator!";
			if (node->prev == nullptr)
				throw "error when trying to decrement past the beginning!";
			node = node->prev;
			return *this;
		}

		T& operator*() const
		{
			if (node == nullptr)
				throw "error when trying to dereference an empty iterator";
			return node->Value;
		}

		//may be that two pointers point on the same node
		bool operator==(const iterator& it)
		{
			return(node == it.node);
		}

		bool operator!=(const iterator& it)
		{
			return(node != it.node);
		}


		friend class DoubleList<T>;
	};

	Node* head;
	Node* last;
	iterator head_it;
	iterator last_it;
public:
	DoubleList()
	{
		head = last = new Node;
		last->next = nullptr;
		last->prev = nullptr;
		head_it = iterator(head);
		last_it = iterator(last);

	}
	DoubleList(T _val)
	{
		head = last = new Node;
		last->next = nullptr;
		last->prev = nullptr;
		head_it = iterator(head);
		last_it = iterator(last);
		push_front(_val);
	}
  
	~DoubleList()
	{
		Node* rem = head;
		Node* p = head;
		while (p != last)
		{
			p = p->next;
			delete rem;
			rem = p;
		}
		delete rem;
	}

	void push_front(T _val)
	{
		Node* addNode = new Node(_val);
		addNode->next = head;
		addNode->prev = nullptr;
		head->prev = addNode;
		head = addNode;
		head_it = iterator(head);

	}

	void push_back(T _val)
	{
		Node* addNode = new Node(_val);
		addNode->next = last;
		addNode->prev = last->prev;
		last->prev->next = addNode;
		last->prev = addNode;
		last_it = iterator(last);
	}

	bool isEmpty()
	{
		return (head == last);
	}

	T remove_front()
	{
		if (isEmpty())
			throw "remove isnt possible, list is empty";
		Node* p = head;
		head = head->next;
		head->prev = nullptr;
		T _val = p->Value;
		head_it = iterator(head);
		delete p;
		return _val;
	}

	T remove_back()
	{
		if (isEmpty())
			throw "remove isnt possible, list is empty";
		Node* p = last->prev;
		if (last->prev == nullptr)
			remove_front();
		T _val = p->Value;
		p ->prev ->next = last;
		last->prev = p->prev;
		last_it = iterator(last);
		delete p;
		return _val;

	}

	// operations for iterators
	int getSize()
	{
		int size = 0;
		iterator p = head_it;
		while (p != last_it)
		{
			++p;
			++size;
		}
		return size;
	}

	void erase(iterator pos)
	{
		Node* p = pos.node;
		Node* tmpPrev = p->prev;
		Node* tmpNext = p->next;
		tmpPrev->next = tmpNext;
		tmpNext->prev = tmpPrev;
		delete p;
	}

	bool findKey(T val)
	{
		iterator p = head_it;
		while (p != last_it)
		{
			if (*p == val)
			{
				return true;
			}
			++p;
		}
		return false;
	}

	friend class iterator;
};



int main()
{
	DoubleList<int> List;
	DoubleList<int>::iterator it;
	int i = 0;
	while (i != 6)
	{
		List.push_front(i);
		++i;
	}
	List.push_back(-4);
	for (it = List.head_it; it != List.last_it; ++it)
	{
		cout << *it <<" ";
	}
	cout << endl;
	cout << List.remove_front() << endl; 
	cout << List.remove_back() << endl;
	cout << List.findKey(3)<< " " << List.getSize() << endl;
	it = List.head_it;
	++it;
	List.erase(it);
	return 0;
}