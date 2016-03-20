/*
 * FibonacciHeap.cpp
 *
 *  Created on: 19/03/2016
 *      Author: João Barbosa
 */


#include "FibonacciHeap.h"
#include <vector>
#include <iostream>


FibHeap::FibHeap() {

	roots = LinkedList();
	min = 0;
	rankLimit = 1;
}


FibHeap::~FibHeap() {

	roots.~LinkedList();
}

int FibHeap::top() {

	return min->value;
}



void FibHeap::push(int value) {

	roots.insertBack(value);

	if (min == 0 || value < min->value)
		min = roots.getBack();
}



void FibHeap::decreaseKey(Node* node, int newValue) {

	Node* parent = node->parent;

	if (parent == 0 || parent->value > node->value) {
		node->value = newValue;
		return;
	}


	roots.insertBack(node->value);

	if (parent->child == node)
		parent->child = node->next;

	if (parent->marked)
		decreaseKey(parent, parent->value);
	else
		parent->marked = true;

	delete node;
}




void FibHeap::pop() {

	if (roots.current == min)
		roots.move();

	if (min->child != 0) {

		min->child->previous->insertNodeLeft(min->next);
		min->child->insertNodeRight(min->previous);

		min->unlink();
	}


	delete min;
	roots.listSize--;
	min = new Node();


	std::vector<NodePtr> ranks(rankLimit, NodePtr());
	int numProcesses = roots.size();

	while (numProcesses != 0) {

		Node* process = roots.current;							// node to process
		int rank = process->rank;

		if (process->value < min->value)
			min = process;

		NodePtr saved = ranks[process->rank];

		if (saved.unassigned()) {
			ranks[rank] = NodePtr(process);
			roots.move();
		}
		else {

			if (process->value < saved.node->value) {
				process->addChild(new Node(saved.node->value));
				delete saved.node;
				rank = process->rank;
			}
			else {
				saved.node->addChild(new Node(process->value));
				delete process;
				roots.current = saved.node;
				rank = saved.node->rank;
			}


			roots.listSize--;
			if (rank >= rankLimit) {
				ranks.push_back(NodePtr(roots.current));
				rankLimit++;
				roots.move();
			}
			else numProcesses++;

			ranks[rank-1] = NodePtr();

		}

		numProcesses--;
	}
}





void FibHeap::printRoots() {

	Node* start = roots.getCurrent();

	do {
		std::cout << "Element: " << roots.getCurrent()->value << std::endl;
		roots.move();
	} while (start != roots.getCurrent());
}
