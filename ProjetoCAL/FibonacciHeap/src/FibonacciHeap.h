/*
 * FibonacciHeap.h
 *
 *  Created on: 19/03/2016
 *      Author: João Barbosa
 */

#ifndef FIBONACCIHEAP_H_
#define FIBONACCIHEAP_H_

#include "CDLinkedList.h"
#include "Node.h"

class FibHeap {

private:
	int rankLimit;
	Node* min;
	LinkedList roots;


public:

	FibHeap();
	~FibHeap();

	int top();
	void push(int value);
	void decreaseKey(Node* node, int newValue);
	void pop();
	bool isEmpty();


	void printRoots();
};



#endif /* FIBONACCIHEAP_H_ */
