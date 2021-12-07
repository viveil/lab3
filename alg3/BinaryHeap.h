#pragma once
#include <iostream>
#include <stdexcept>
using namespace std;

class Iterator
{
public:
	virtual int next() = 0;
	virtual bool has_next() = 0;
};

class Node
{
public:
	Node* parent;
	Node* left;
	Node* right;
	int data;

	Node(int data = 0, Node* parent = nullptr):data(data), parent(parent), left(nullptr), right(nullptr) {}

	~Node()
	{
		if (left != nullptr) delete left;
		if (right != nullptr) delete right;
	}
};

class LinkedStructure
{
public:
	Node* node;
	LinkedStructure* next;

	LinkedStructure(Node* current = nullptr, LinkedStructure* prev = nullptr)
		: node(current), next(nullptr) {}

	~LinkedStructure() {}
};

class Stack
{
public:
	LinkedStructure* head;

	Stack() : head(nullptr) {}
	~Stack()
	{
		while (head != nullptr) Pop();
	}

	void Push(Node* node)
	{
		LinkedStructure* temp = new LinkedStructure(node);
		temp->next = head;
		head = temp;
		return;
	}

	void Pop()
	{
		if (head == nullptr) throw out_of_range("Stack is empty");
		LinkedStructure* next = head->next;
		delete head;
		head = next;
		return;
	}
};

class Queue
{
public:
	LinkedStructure* first;
	LinkedStructure* last;

	Queue() : first(nullptr), last(nullptr) {}
	~Queue()
	{
		while (first != nullptr) Pop();
		last = nullptr;
	}

	void Push(Node* node)
	{
		if (last != nullptr)
		{
			last->next = new LinkedStructure(node, last);
			last = last->next;
		}
		else
		{
			first = new LinkedStructure(node);
			last = first;
		}
		return;
	}

	void Pop()
	{
		if (first == nullptr) throw out_of_range("Queue is empty");
		LinkedStructure* next = first->next;
		delete first;
		first = next;
		return;
	}
};

class BinaryHeap
{
	Node* root;
	size_t size;
	size_t height;

	size_t GetSize(size_t hHeight)
	{
		size_t Size = 1;
		for (size_t i = 0; i < hHeight; i++) Size += Size + 1;
		return Size;
	}

	
	void siftUp(Node* curr)
	{
		Node* current = curr;
		while (current != root)
		{
			if (current->data > current->parent->data)
			{
				int tmp = current->data;
				current->data = current->parent->data;
				current->parent->data = tmp;
				current = current->parent;
			}
			else break;
		}
		return;
	}

	
	void siftDown(Node* curr)
	{
		Node* current = curr;
		while (current != nullptr)
		{
			if (current->left == nullptr) break;

			Node* swapp;
			if (current->right == nullptr) swapp = current->left;
			else
			{
				if (current->left->data > current->right->data) swapp = current->left;
				else swapp = current->right;
			}

			int tmp = current->data;
			current->data = swapp->data;
			swapp->data = tmp;
			current = swapp;
		}
		return;
	}

	
	void Heapify(Node* cur)
	{ 
		if (cur->parent == nullptr) {
			siftDown(cur);
		}
		else
			if ((cur->data) > (cur->parent->data)) {
				siftUp(cur);
			}
			else {
				siftDown(cur);
			}
	}

public:
	
	BinaryHeap()
	{
		root = nullptr;
		height = 0;
		size = 0;
	}

	~BinaryHeap()
	{
		if (root) delete root;
	}


	bool contains(int data)
	{
		bft_iterator iterator(root);
		while (iterator.has_next())
		{
			if (iterator.next() == data) return true;
		}
		return false;
	}

	void insert(int data)
	{
		if (size == 0) root = new Node(data);
		else
		{
			Node* current = root;
			const size_t Index = size + 1;
			size_t iterations = (GetSize(height) > size ? height - 1 : height);
			for (size_t i = 0; i < iterations; i++)
			{
				if ((Index >> (iterations - i)) % 2 == 0) current = current->left;
				else current = current->right;
			}
			if (Index % 2 == 0)
			{
				current->left = new Node(data, current);
				current = current->left;
			}
			else
			{
				current->right = new Node(data, current);
				current = current->right;
			}
			if (GetSize(height) == size) height++;
			Heapify(current);
		}
		size++;
		return;
	}

	void remove(int data)
	{
		bft_iterator iterator(root);
		while (iterator.has_next())
		{
			if (iterator.next() == data)
			{
				if (size == 1)
				{
					delete root;
					root = nullptr;
				}
				else
				{
					Node* current = root;
					bool condition, last = false;
					size_t iterations = (GetSize(height) > size ? height - 1 : height);
					for (size_t i = 0; i < iterations; i++)
					{
						if ((size >> (iterations - i)) % 2 == 0) current = current->left;
						else current = current->right;
					}
					if (size % 2 == 0)
					{
						condition = (iterator.previous->data <= current->left->data);
						iterator.previous->data = current->left->data;
						if (current->left == iterator.previous) last = true;
						delete current->left;
						current->left = nullptr;
					}
					else
					{
						condition = (iterator.previous->data <= current->right->data);
						iterator.previous->data = current->right->data;
						if (current->right == iterator.previous) last = true;
						delete current->right;
						current->right = nullptr;
					}
					if (GetSize(height - 1) == size - 1) height--;
					if (!last) Heapify(iterator.previous);
				}
				size--;
				return;
			}
		}
		throw invalid_argument("No such element");
	}


	class dft_iterator : public Iterator
	{
		Node* current;
		Stack* stackOfNodes;

	public:
		Node* previous;

		dft_iterator(Node* root) : current(root), stackOfNodes(new Stack), previous(nullptr) {}
		~dft_iterator() { delete stackOfNodes; }

		
		int next() override {
			if (!has_next())
			{
				throw out_of_range("No elements left");
			}
			previous = current;
			int temp = current->data;
			if (current->right != nullptr) stackOfNodes->Push(current->right);
			if (current->left != nullptr) current = current->left;
			else
			{
				if (stackOfNodes->head != nullptr)
				{
					current = stackOfNodes->head->node;
					stackOfNodes->Pop();
				}
				else current = nullptr;
			}
			return temp;
		};

		
		bool has_next() override { return current != nullptr; }
	};

	
	class bft_iterator : public Iterator
	{
		Node* current;
		Queue* queueOfNodes;

	public:
		Node* previous;

		bft_iterator(Node* root) : current(root), queueOfNodes(new Queue), previous(nullptr) {}
		~bft_iterator() { delete queueOfNodes; }

		
		int next() override {
			if (!has_next())
			{
				throw out_of_range("No elements left");
			}
			previous = current;
			int temp = current->data;
			if (current->left != nullptr) queueOfNodes->Push(current->left);
			if (current->right != nullptr) queueOfNodes->Push(current->right);
			if (queueOfNodes->first != nullptr)
			{
				current = queueOfNodes->first->node;
				queueOfNodes->Pop();
			}
			else current = nullptr;
			return temp;
		};

		
		bool has_next() override { return current != nullptr; }
	};

	
	Iterator* create_dft_iterator()
	{
		return new dft_iterator(root);
	}

	
	Iterator* create_bft_iterator()
	{
		return new bft_iterator(root);
	}

	

	friend ostream& operator<<(ostream& output, BinaryHeap& heap)
	{
		bft_iterator iterator(heap.root);
		while (iterator.has_next())
		{
			output << iterator.next() << " ";
		}
		return output;
	}
};

