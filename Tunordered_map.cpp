#include<iostream>

using namespace std;
template<class K, class V>
class Tunordered_map
{
	struct Node
	{
		K key;
		V value;
		int hash;
		Node* next;
		Node() {};
		Node(K _key, V _val) : key(_key), value(_val), hash(0), next(nullptr) {};
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
		K first()
		{
			return node->key;
		}
		V second()
		{
			return node->value;
		}

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
		V& operator*() const
		{
			if (node == nullptr)
				throw "error when trying to dereference an empty iterator";
			return node->value;
		}
		bool operator==(const iterator& it)
		{
			return(node == it.node);
		}
		bool operator!=(const iterator& it)
		{
			return(node != it.node);
		}
		friend class Tunordered_map<K, V>;
	};

	Node** map;
	iterator first;

	Tunordered_map()
	{
		map = new Node *[20];
		for (int i = 0; i < 20; ++i)
		{
			map[i] = nullptr;
		}
	}
	~Tunordered_map()
	{
		for (int i = 0; i < 20; ++i)
			delete map[i];
		delete[] map;
	}

	K Get_hash(K _key)
	{
		return (_key % 20);
	}

	bool isEmpty()
	{
		for (int i = 0; i < 20; i++)
		{
			if (map[i] != nullptr)
				return true;
		}
		return false;
	}

	void insert(K _key, V _val)
	{
		bool empty = false;
		if (isEmpty())
			empty = true;
		Node* node = new Node;
		K tmp = Get_hash(_key);
		node->hash = tmp;
		node->key = _key;
		node->value = _val;
		int i = (int)(tmp);
		if (i >= 20 && i < 0)
			throw "out of range";
		else
		{
			if (map[i] == nullptr)
			{
				map[i] = node;
				node->next = nullptr;
			}
			else
			{
				Node* p = map[i];
				while (p->next != nullptr)
					p = p->next;
				p->next = node;
				node->next = nullptr;
			}
		}
		if (empty)
			first = iterator(node);

	}

	iterator find(K _key)
	{
		if (isEmpty())
			throw "map is empty";
		Node* node = map[0];
		if (node->key == _key)
			return iterator(node);
		else
		{
			int i = 0;
			Node* p = map[i];
			while (p->key != _key)
			{
				if (i >= 20)
					return nullptr;
				++i;
			}
			node = map[i];
		}
		return iterator(node);
	}

	void erase(K _key)
	{
		iterator it = find(_key);
		if (it == nullptr) throw "no buckets with key";
		else
		{
			
			while (it.node->next != nullptr)
			{
				Node* n = it.node;
				delete n;
			}
		}
	}

	void print()
	{
		for (int i = 0; i < 20; ++i)
		{
			if (map[i] != nullptr)
			{
				Node* p = map[i];
				cout << p->key << " " << p->value << endl;
				if (p->next != nullptr)
				{
					Node* n = map[i];
					while (n->next != nullptr)
					{
						cout << n->key << " " << n->value << endl;
						n = n->next;
					}
				}
			}
		}

	}


};

int main()
{
	Tunordered_map<int, int> mp;
	mp.insert(1, 4);
	mp.insert(13, 7);
	mp.insert(5, 210);
	mp.insert(19, 231);
	mp.insert(1, 90);
	mp.insert(7, 34);
	mp.print();
	auto it = mp.find(1);
	cout << it.first() << it.second() << endl;
	mp.erase(5);
	return 0;