/*
 * CDLinkedList.cpp
 *
 *  Created on: 19/03/2016
 *      Author: João Barbosa
 */

#include "CDLinkedList.h"


LinkedList::LinkedList() /*: sentinel(new Node())*/ {

	//	current = sentinel;
	//	iter = sentinel;

	current = 0;
	iter = 0;
	listSize = 0;
};


LinkedList::~LinkedList() {

	while(!isEmpty())
	{
		delete current->next;
		listSize--;
	}
	//delete current;
}


bool LinkedList::isEmpty() const {

	return (listSize == 0);
}


void LinkedList::insertBack(int value) {

	if (isEmpty())	new Node(value);
	else 			new Node(value, current->previous, current);

	listSize++;
}


void LinkedList::insertFront(int value) {

	//	new Node(value, current, current->next);
	//
	//	if (isEmpty())
	//		move();
	//
	//	listSize++;

	if (isEmpty()) 	current = new Node(value);
	else 			new Node(value, current, current->next);

	listSize++;
}




void LinkedList::deleteBack() {

	if (isEmpty())
		return;

//	if (current->previous == sentinel)
//		delete sentinel->previous;
//	else
		delete current->previous;


	listSize--;
//	if (isEmpty())
//		current = sentinel;
}



void LinkedList::deleteFront() {

	if (isEmpty())
		return;

//	if (current->next == sentinel)
//		delete sentinel->next;
//	else
		delete current->next;


	listSize--;
//	if (isEmpty())
//		current = sentinel;
}


void LinkedList::move() {

	current = current->next;

//	if (current == sentinel)
//		current = sentinel->next;
}



void LinkedList::moveBack() {

	current = current->previous;

//	if (current == sentinel)
//		current = sentinel->previous;
}



Node* LinkedList::getCurrent() const {

	if (isEmpty())
		throw EmptyList();

	return current;
}


Node* LinkedList::getFront() const {

	if (isEmpty())
		throw EmptyList();

//	if (current->next == sentinel)
//		return sentinel->next;

	return current->next;
}


Node* LinkedList::getBack() const {

	if (listSize == 0)
		throw EmptyList();

	return current->previous;
}


unsigned LinkedList::size() {

	return listSize;
}



void LinkedList::iterateStart() {

	iter = current->next;
}



bool LinkedList::iterateEnd() {

	return (iter == current);
}



void LinkedList::iterate() {

	iter = iter->next;
}



Node* LinkedList::retrieve() const {

//	if (iter == sentinel)
//		throw InvalidRetrieve();

	return iter;
}
