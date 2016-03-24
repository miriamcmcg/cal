#ifndef NODE_H
#define NODE_H

#include <list>
#include <limits>
#include "CDLinkedList.h"

#define INT_MAXIMUM			std::numeric_limits<int>::max()
#define INT_MININUM			std::numeric_limits<int>::min()

class Node {

private:
	bool marked;
	int rank;
	int value;

	Node* previous;
	Node* next;
	Node* parent;
	Node* child;

public:
	Node ();
	Node (int val);
	Node (int val, Node* previous, Node* next);
	Node (const Node& n);
	~Node ();
	void addChild (Node* node);
	void insertNode (Node* previous, Node* next);
	void insertNodeRight (Node* previous);
	void insertNodeLeft (Node* next);
	int getValue();
	void unlink();



	friend class LinkedList;
	friend class FibHeap;
};




class NodePtr {

private:
	Node* node;

public:
	NodePtr();
	NodePtr(Node* node);

	NodePtr& operator=(NodePtr np);
	bool operator==(NodePtr np) const;
	bool unassigned() const;

	friend class FibHeap;
};

#endif
