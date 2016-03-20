/*
 * CDLinkedList.cpp
 *
 *  Created on: 19/03/2016
 *      Author: João Barbosa
 */

#include "CDLinkedList.h"


LinkedList::LinkedList() {

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
}


bool LinkedList::isEmpty() const {

	return (listSize == 0);
}


void LinkedList::insertBack(int value) {

	if (isEmpty())	current = new Node(value);
	else 			new Node(value, current->previous, current);

	listSize++;
}


void LinkedList::insertFront(int value) {

	if (isEmpty())	current = new Node(value);
	else 			new Node(value, current, current->next);

	listSize++;
}




void LinkedList::deleteBack() {

	if (isEmpty())
		return;

	delete current->previous;
	listSize--;
}



void LinkedList::deleteFront() {

	if (isEmpty())
		return;

	delete current->next;
	listSize--;
}


void LinkedList::move() {

	current = current->next;
}



void LinkedList::moveBack() {

	current = current->previous;
}



Node* LinkedList::getCurrent() const {

	if (isEmpty())
		throw EmptyList();

	return current;
}


Node* LinkedList::getFront() const {

	if (isEmpty())
		throw EmptyList();

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

	return iter;
}
