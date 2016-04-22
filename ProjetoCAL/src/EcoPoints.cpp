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
#include "Interface.h"

using namespace std;

int main() {

//	Reader r;
//	r.readFiles();
// 	GarbageCentral GC(r);

	GarbageCentral GC = GarbageCentral();

	mainMenu(GC);

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

	//GC.aux();

	pair < Route, vector< GarbageDeposit* > > data = GC.createPickingRoute(1);
	GC.pickGarbage(1);

	if (data.second.size() != 0)
		cout << data.second[0]->getID() << endl;

	return 0;
}
