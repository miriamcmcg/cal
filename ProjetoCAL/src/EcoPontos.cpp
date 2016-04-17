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
//	r.printInfo();

	GarbageCentral GC(r);
	GC.print();

	return 0;
}
