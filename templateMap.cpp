nclude <iostream>
#include <cstring>

using namespace std;

enum NodeColor {red, black};

#define compLT(a,b) (a < b)
#define compEQ(a,b) (a == b)

template<class K, class V>
class Tmap
{
public:
	struct Node
	{
		Node* left;
		Node* right;
		Node* parent;
		K key;
		V value;
		NodeColor color;
	public:
		Node() {};
		Node(K _key, V _val) : key(_key), value(_val) {};
		~Node() {};
	};

	class iterator
	{
		Node* node;

	public:

		iterator() : node(nullptr) {};
		iterator(Node* p) : node(p) {};
		iterator(const iterator& it) : node(it.node) {};

		K first() const
		{
			return node->key;
		}

		V second()
		{
			return node->value;
		}

		void advance(iterator it, int count)
		{
			int i = 0;
			while (i != count) ++it;
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

		iterator& operator--()
		{
			if (node == nullptr)
				throw "error when trying to decrement empty iterator!";
			if (node->prev == nullptr)
				throw "error when trying to decrement past the beginning!";
			node = node->prev;
			return *this;
		}

		bool operator==(const iterator& it)
		{
			return(node == it.node);
		}

		bool operator!=(const iterator& it)
		{
			return(node != it.node);
		}


		friend class Tmap<K,V>;
	};


	Node* root;
	Node* sentinel;
	iterator first;
	iterator last;

	Tmap()
	{
		sentinel = new Node;
		sentinel->parent = 0;
		sentinel->left = nullptr;
		sentinel->right = nullptr;
		sentinel->color = black;
		root = sentinel;
	}
	~Tmap()
	{
		cleanup(root);
	}

	void cleanup(Node* p) 
	{
		if (!p) return;
		if (p->left==sentinel)
		{
			Node* t = p;
			cleanup(t->left);
			delete p;
		}
		if (p->right==sentinel)
		{
			cleanup(p->right);
			delete p;
		}
		delete p;
	}

	/******************************************base function for iterator*******************************************/
	Node* getMin()
	{
		//Node* min=nullptr;
		Node* tmp = root;
		if (root == sentinel)
			return nullptr;
		while (tmp->left != sentinel)
			tmp = tmp->left;
		return tmp;
	}

	Node* getMax()
	{
		Node* tmp = root;
		if (root == sentinel)
			return;
		while (tmp->right != sentinel)
		{
			tmp = tmp->right;
		}
		return tmp;
	}

	iterator begin()
	{
		return iterator(getMin());
	}

	iterator end()
	{
		return iterator(getMax());
	}

/************************************rotate function after insert and remove element*********************************/
	void rotateLeft(Node* x)
	{
		Node* y = x->right;
		x->right = y->left;
		if (y->left != sentinel) y->left->parent = x;
		if (y != sentinel) y->parent = x->parent;
		if (x->parent)
		{
			if (x == x->parent->left)
				x->parent->left = y;
			else
				x->parent->right = y;
		}
		else
		{
			root = y;
		}
		y->left = x;
		if (x != sentinel) x->parent = y;
	}

	void rotateRight(Node* x)
	{
		Node* y = x->left;
		x->left = y->right;
		if (y->right != sentinel) y->right->parent = x;
		if (y != sentinel) y->parent = x->parent;
		if (x->parent)
		{
			if (x == x->parent->right)
				x->parent->right = y;
			else
				x->parent->left = y;
		}
		else {
			root = y;
		}
		y->right = x;
		if (x != sentinel) x->parent = y;
	}

	void insertFixup(Node* x)
	{
		/* check Red-Black properties */
		while (x != root && x->parent->color == red)
		{
			/* we have a violation */
			if (x->parent == x->parent->parent->left)
			{
				Node* y = x->parent->parent->right;
				if (y->color == red)
				{
					/* uncle is RED */
					x->parent->color = black;
					y->color = black;
					x->parent->parent->color = red;
					x = x->parent->parent;
				}
				else
				{
					/* uncle is BLACK */
					if (x == x->parent->right)
					{
						/* make x a left child */
						x = x->parent;
						rotateLeft(x);
					}
					/* recolor and rotate */
					x->parent->color = black;
					x->parent->parent->color = red;
					rotateRight(x->parent->parent);
				}
			}
			else
			{
				/* mirror image of above code */
				Node* y = x->parent->parent->left;//nullptr
				if (y->color == red)
				{
					/* uncle is RED */
					x->parent->color = black;
					y->color = black;
					x->parent->parent->color = red;
					x = x->parent->parent;
				}
				else
				{
					/* uncle is BLACK */
					if (x == x->parent->left)
					{
						x = x->parent;
						rotateRight(x);
					}
					x->parent->color = black;
					x->parent->parent->color = red;
					rotateLeft(x->parent->parent);
				}
			}
		}
		root->color = black;
	}


	void deleteFixup(Node* x)
	{
		while (x != root && x->color == black)
		{
			if (x == x->parent->left)
			{
				Node* w = x->parent->right;
				if (w->color == red)
				{
					w->color = black;
					x->parent->color = red;
					rotateLeft(x->parent);
					w = x->parent->right;
				}
				if (w->left->color == black && w->right->color == black)
				{
					w->color = red;
					x = x->parent;
				}
				else
				{
					if (w->right->color == black)
					{
						w->left->color = black;
						w->color = red;
						rotateRight(w);
						w = x->parent->right;
					}
					w->color = x->parent->color;
					x->parent->color = black;
					w->right->color = black;
					rotateLeft(x->parent);
					x = root;
				}
			}
			else
			{
				Node* w = x->parent->left;
				if (w->color == red)
				{
					w->color = black;
					x->parent->color = red;
					rotateRight(x->parent);
					w = x->parent->left;
				}
				if (w->right->color == black && w->left->color == black)
				{
					w->color = red;
					x = x->parent;
				}
				else
				{
					if (w->left->color == black)
					{
						w->right->color = black;
						w->color = red;
						rotateLeft(w);
						w = x->parent->left;
					}
					w->color = x->parent->color;
					x->parent->color = black;
					w->left->color = black;
					rotateRight(x->parent);
					x = root;
				}
			}
		}
		x->color = black;
	}
/*****************************function for map***************************************************/
	void insertNode(K _key, V _val)
	{
		Node* current = root;
		Node* parent = 0;
		Node* x;
		while (current != sentinel)
		{
			if (compEQ(_key, current->key))
			    return;
			parent = current;
			current = compLT(_key, current->key) ?
				current->left : current->right;
		}

			x = new Node(_key, _val);
				x->parent = parent;
				x->left = sentinel;
				x->right = sentinel;
				x->color = red;
		if(parent)
		{
			if (compLT(_key, parent->key)) parent->left = x;
			else parent->right = x;
		}
		else root = x;
		insertFixup(x);
	}


	void deleteNode(Node* z)
	{
		Node* x;
		Node* y;
		if (!z || z == sentinel) return;
		if (z->left == sentinel || z->right == sentinel) y = z;
		else
		{
			y = z->right;
			while (y->left != sentinel) y = y->left;
		}
		if (y->left != sentinel) x = y->left;
		else x = y->right;
		x->parent = y->parent;
		if (y->parent)
			if (y == y->parent->left) y->parent->left = x;
			else y->parent->right = x;
		else root = x;
		if (y != z)
		{
			z->key = y->key;
			z->value = y->value;
		}
		if (y->color == black)
			deleteFixup(x);
		delete y;
	}

	iterator findNode(K _key, V value)
	{
		Node* current = root;
		while (current != sentinel)
			if (compEQ(_key, current->key))

				return iterator(current);

			else
				current = compLT(_key, current->key) ?
				current->left : current->right;
		return 0;
	}

	void printNode()
	{
		print(root);
	}
	void print(Node *p)
	{
		if (p == sentinel)
			return;
		cout << "key = " << p->key << " " << "value = " << p->value << endl;
		print(p->left);
		print(p->right);
	}

};
	int  main() 
	{
			Tmap<int, string> mp;
			mp.insertNode(1, "Hello");
			mp.insertNode(4, "from");
			mp.insertNode(110, "russia");
			mp.insertNode(11, "with");
			mp.insertNode(3, "love");
			mp.insertNode(13, "goodbye");
			auto p = mp.findNode(3, "love");
			cout << p.first() << p.second() << endl;
			mp.printNode();
		return 0;
	}