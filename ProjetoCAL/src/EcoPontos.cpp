//============================================================================
// Name        : EcoPontos.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "Reader.h"
#include "GarbageCentral.h"

using namespace std;

int main() {

	Reader r;
	r.readFiles();

	GarbageCentral GC(r);
	//	GC.print();

	//	auto vec = GC.getPath(1110698299, 2213493593);
	//
	//	auto garbage_deposits = vec.first;
	//	auto roads = vec.second;
	//
	//	unsigned i;
	//	for(i = 0; i < garbage_deposits.size() - 1; i++) {
	//		cout << garbage_deposits[i].getID() << "  --->  ";
	//		cout << roads[i].getName() << "  --->  ";
	//	}
	//
	//	cout << garbage_deposits[i].getID() << endl;

	GC.aux();

	return 0;
}
