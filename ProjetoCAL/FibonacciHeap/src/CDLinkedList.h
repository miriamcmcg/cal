/*
 * CDLinkedList.h
 *
 *  Created on: 19/03/2016
 *      Author: João Barbosa
 */

#ifndef CDLINKEDLIST_H_
#define CDLINKEDLIST_H_

#include "Node.h"

class Node;


class LinkedList {

private:
	unsigned listSize;
	Node* current;
	Node* iter;


public:
	LinkedList();
	~LinkedList();

	bool isEmpty() const;
	void insertBack(int value);
	void insertFront(int value);
	void deleteBack();
	void deleteFront();
	void move();
	void moveBack();
	Node* getCurrent() const;
	Node* getFront() const;
	Node* getBack() const;
	unsigned size();

	void iterateStart();
	bool iterateEnd();
	void iterate();
	Node* retrieve() const;


	class EmptyList {};
	class InvalidRetrieve {};


	friend class FibHeap;
};


#endif /* CDLINKEDLIST_H_ */
