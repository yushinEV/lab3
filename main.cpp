#include <iostream>
#include <stdexcept>
using namespace std;
class Iterator
{
public:
	virtual int next() = 0;
	virtual bool has_next() = 0;
};
class BSTREE
{
	class Node
	{
	public:
		int key;
		Node* left;
		Node* right;
		Node* parent;
		Node(int val, Node* prev = NULL)
		{
			key = val;
			parent = prev;
			left = NULL;
			right = NULL;
		}
	};
	Node* head;
	Iterator* dft;
	Iterator* bft;
	void rec_ins(Node* current, int key)
	{
		if (key >= current->key)
		{
			if (current->right == NULL)
				current->right = new Node(key, current);
			else
				rec_ins(current->right, key);
		}
		else
		{
			if (current->left == NULL)
				current->left = new Node(key, current);
			else
				rec_ins(current->left, key);
		}
	}
	Node* find(Node* current, int key)
	{
		if (current == NULL)
			return NULL;
		else if (current->key == key)
			return current;
		else if (key > current->key)
			return find(current->right, key);
		else
			return find(current->left, key);
	}
	Node* find_min(Node* current)
	{
		if (current->left == NULL)
			return current;
		else
			return find_min(current->left);
	}
public:
	BSTREE()
	{
		head = NULL;
		dft = NULL;
		bft = NULL;
	}
	class DFT :public Iterator
	{
		class Stack
		{
		public:
			Node* inf;
			Stack* next;
			Stack(Node* Inf, Stack* Next)
			{
				inf = Inf;
				next = Next;
			}
		};
		Stack* Head;
		Node* Current;
	public:
		DFT(Node* begin)
		{
			Head = NULL;
			Current = begin;
		}
		int next() override
		{
			if (!has_next())
				throw out_of_range("Tree is over\n");
			int returning_value = Current->key;
			if (Current->right != NULL)
			{
				Stack* New = new Stack(Current->right, Head);
				Head = New;
			}
			if (Current->left != NULL)
			{
				Current = Current->left;
			}
			else
			{
				if (Head != NULL)
				{
					Current = Head->inf;
					Stack* Next;
					Next = Head->next;
					delete Head;
					Head = Next;
				}
				else
					Current = NULL;
			}
			return returning_value;
		}
		bool has_next() override
		{
			return (Current != NULL);
		}
	};
	Iterator* create_dft_iterator()
	{
		if (dft != NULL)
			delete dft;
		dft = new DFT(head);
		return dft;
	}
	class BFT :public Iterator
	{
		class Tree_queue
		{
		public:
			Node* inf;
			Tree_queue* next;
			Tree_queue(Node* Inf, Tree_queue* Next)
			{
				inf = Inf;
				next = Next;
			}
		};
		Tree_queue* First;
		Tree_queue* Last;
		Node* Current;
	public:
		BFT(Node* Start)
		{
			First = NULL;
			Last = NULL;
			Current = Start;
		}
		int next() override
		{
			if (!has_next())
				throw out_of_range("Tree is over\n");
			int returning_value = Current->key;
			if (Current->left != NULL)
			{
				Tree_queue* New = new Tree_queue(Current->left, Last);
				if (First == NULL)
				{
					First = New;
				}
				Last = New;
			}
			if (Current->right != NULL)
			{
				Tree_queue* New = new Tree_queue(Current->right, Last);
				if (First == NULL)
				{
					First = New;
				}
				Last = New;
			}
			Tree_queue* CURRENT = Last;
			if (CURRENT != NULL)
			{
				if (CURRENT == First)
				{
					Current = CURRENT->inf;
					delete CURRENT;
					Last = NULL;
					First = NULL;
				}
				else
				{
					while (CURRENT->next != First)
					{
						CURRENT = CURRENT->next;
					}
					Current = CURRENT->next->inf;
					delete First;
					First = CURRENT;
					CURRENT->next = NULL;
				}
			}
			else
				Current = NULL;
			return returning_value;
		}
		bool has_next() override
		{
			return (Current != NULL);
		}
	};
	Iterator* create_bft_iterator()
	{
		if (bft != NULL)
			delete bft;
		bft = new BFT(head);
		return bft;
	}
	void insert(int key)
	{
		if (bft != NULL)
		{
			delete bft;
			bft = NULL;
		}
		if (dft != NULL)
		{
			delete dft;
			dft = NULL;
		}
		if (head == NULL)
			head = new Node(key);
		else
			rec_ins(head, key);
	}
	bool contains(int key)
	{
		return (find(head, key) != NULL);
	}
	void remove(int key)
	{
		if (bft != NULL)
		{
			delete bft;
			bft = NULL;
		}
		if (dft != NULL)
		{
			delete dft;
			dft = NULL;
		}
		Node* deleter = find(head, key);
		if (deleter == NULL)
			throw invalid_argument("Element is not included in tree\n");
		if ((deleter->left == NULL) && (deleter->right == NULL))
		{
			if (deleter->parent == NULL)
				head = NULL;
			else if (deleter->parent->left == deleter)
				deleter->parent->left = NULL;
			else
				deleter->parent->right = NULL;
			delete deleter;
		}
		else if ((deleter->left == NULL) && (deleter->right != NULL))
		{
			if (deleter->parent == NULL)
			{
				head = deleter->right;
				deleter->right->parent = NULL;
			}
			else if (deleter->parent->left == deleter)
			{
				deleter->parent->left = deleter->right;
				deleter->right->parent = deleter->parent;
			}
			else
			{
				deleter->parent->right = deleter->right;
				deleter->right->parent = deleter->parent;
			}
			delete deleter;
		}
		else if ((deleter->left != NULL) && (deleter->right == NULL))
		{
			if (deleter->parent == NULL)
			{
				head = deleter->left;
				deleter->left->parent = NULL;
			}
			else if (deleter->parent->left == deleter)
			{
				deleter->parent->left = deleter->left;
				deleter->left->parent = deleter->parent;
			}
			else
			{
				deleter->parent->right = deleter->left;
				deleter->left->parent = deleter->parent;
			}
			delete deleter;
		}
		else if ((deleter->left != NULL) && (deleter->right != NULL))
		{
			Node* Min = find_min(deleter->right);
			if (deleter->parent == NULL)
				head = Min;
			if (Min->parent->left == Min)
				Min->parent->left = Min->right;
			else
				Min->parent->right = Min->right;
			if (Min->right != NULL)
				Min->right->parent = Min->parent;
			Min->parent = deleter->parent;
			if (Min->parent != NULL)
			{
				if (Min->parent->right == deleter)
					Min->parent->right = Min;
				else
					Min->parent->left = Min;
			}
			Min->left = deleter->left;
			Min->right = deleter->right;
			Min->left->parent = Min;
			if (Min->right != NULL)
				Min->right->parent = Min;
			delete deleter;
		}
	}
	~BSTREE()
	{
		if (bft != NULL)
		{
			delete bft;
			bft = NULL;
		}
		if (dft != NULL)
		{
			delete dft;
			dft = NULL;
		}
		while (head != NULL)
			remove(head->key);
	}
};
int main()
{
	BSTREE T;
	T.insert(12);
	T.insert(14);
	T.insert(4);
	T.insert(1);
	T.insert(2);
	T.insert(7);
	T.insert(11);
	Iterator* BFT = T.create_bft_iterator();
	Iterator* DFT = T.create_dft_iterator();
	cout << "BFT operator finished his work: " << endl;
	while (BFT->has_next())
	{
		cout << BFT->next();
		if (BFT->has_next())
		{
			cout << "->";
		}
	}
	cout << endl;
	cout << "DFT operator finished his work: " << endl;
	while (DFT->has_next())
	{
		cout << DFT->next();
		if (DFT->has_next())
		{
			cout << "->";
		}
	}
	cout << endl;
}