/*
 * Node.cpp
 *
 *  Created on: 19/03/2016
 *      Author: João Barbosa
 */


#include "Node.h"


Node::Node() : previous(this), next(this), parent(0), child(0) {

	marked = false;
	value = INT_MAXIMUM;
	rank = 0;
}


Node::Node(int val) : previous(this), next(this), parent(0), child(0) {

	marked = false;
	value = val;
	rank = 0;
}


Node::Node(int val, Node* previous, Node* next) {

	marked = false;
	value = val;
	rank = 0;

	this->previous = previous;
	this->next = next;
	previous->next = this;
	next->previous = this;

	this->parent = 0;
	this->child = 0;
}


Node::Node(const Node& n) {

	marked = n.marked;
	value = n.value;
	rank = n.rank;

	this->previous = n.previous;
	this->next = n.next;
	previous->next = this;
	next->previous = this;

	this->parent = n.parent;
	this->child = n.child;
}


Node::~Node() {

	previous->next = next;
	next->previous = previous;
}



void Node::addChild (Node* node) {

	if (child == 0) {
		child = node;
		child->unlink();
	}
	else
		node->insertNode(child, child->next);

	node->parent = this;
	rank++;
}



void Node::insertNode (Node* previous, Node* next) {

	this->previous = previous;
	this->next = next;
	previous->next = this;
	next->previous = this;
}



void Node::insertNodeRight (Node* previous) {

	this->previous = previous;
	previous->next = this;
}



void Node::insertNodeLeft (Node* next) {

	this->next = next;
	next->previous = this;
}



int Node::getValue() {

	return value;
}



void Node::unlink() {

	this->previous = this;
	this->next = this;
}





// NodePtr Class


NodePtr::NodePtr() : node(0) {}


NodePtr::NodePtr(Node* node) {

	this->node = node;
}


NodePtr& NodePtr::operator=(NodePtr np) {

	this->node = np.node;
	return *this;
}


bool NodePtr::operator==(NodePtr np) const {

	return (this->node == np.node);
}


bool NodePtr::unassigned() const {

	return (node == 0);
}
