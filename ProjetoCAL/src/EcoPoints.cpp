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
	srand(time(NULL));

//	Reader r;
//	r.readFiles();
// 	GarbageCentral GC(r);

	GarbageCentral GC = GarbageCentral();

	mainMenu(GC);
	return 0;
}
