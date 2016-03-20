//============================================================================
// Name        : FibHeap.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "CDLinkedList.h"
#include "FibonacciHeap.h"

using namespace std;

int main() {

//	LinkedList roots = LinkedList();
//
//	if (roots.isEmpty())
//		cout << "Está vazia!\n";
//
//	cout << "Tamanho " << roots.size() << endl;
//
//
//	cout << "\n\n";
//
//
//	cout << "Insere numero 2\n";
//	roots.insertFront(2);
//	cout << "Tamanho " << roots.size() << endl << endl;
//
//	cout << "Elemento atual: " << roots.getCurrent()->getValue() << endl;
//	roots.move();
//	cout << "Elemento atual: " << roots.getFront()->getValue() << endl;
//
//
//	roots.deleteFront();
//	cout << "Tamanho " << roots.size() << endl << endl;
//	roots.deleteFront();
//
//
//
//	cout << "Insere numero 6\n";
//	roots.insertFront(6);
//	cout << "Tamanho " << roots.size() << endl << endl;
//	cout << "Elemento atual: " << roots.getCurrent()->getValue() << endl;
//
//
//	cout << "Insere numero 10\n";
//	roots.insertFront(10);
//	cout << "Tamanho " << roots.size() << endl << endl;
//	cout << "Elemento atual: " << roots.getCurrent()->getValue() << endl;
//
//
//	cout << "Insere numero 20\n";
//	roots.insertFront(20);
//	cout << "Tamanho " << roots.size() << endl << endl;
//
//
//
//	int i = 1;
//	for (roots.iterateStart(); !roots.iterateEnd(); roots.iterate()) {
//
//		cout << "Elemento " << i << ": " << roots.retrieve()->getValue() << endl;
//		i++;
//	}
//
//	cout << endl;
//	roots.deleteFront();
//
//	cout << roots.getCurrent()->getValue() << endl;
//	i = 1;
//	for (roots.iterateStart(); !roots.iterateEnd(); roots.iterate()) {
//
//		cout << "Elemento " << i << ": " << roots.retrieve()->getValue() << endl;
//		i++;
//	}


	FibHeap fh = FibHeap();

	fh.push(2);
	fh.push(4);
	fh.push(5);
	fh.push(5);
	fh.push(6);
	fh.push(3);
	fh.push(10);
	fh.push(8);
//	fh.push(11);

	cout << "Min: " << fh.top() << endl;
	fh.printRoots();

	fh.pop();

	cout << endl;
	cout << "Min: " << fh.top() << endl;
	fh.printRoots();
}
